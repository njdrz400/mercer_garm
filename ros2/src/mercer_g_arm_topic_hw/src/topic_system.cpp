#include "mercer_g_arm_topic_hw/topic_system.hpp"

#include <algorithm>
#include <chrono>
#include <unordered_map>

#include "hardware_interface/types/hardware_interface_type_values.hpp"
#include "pluginlib/class_list_macros.hpp"

namespace mercer_g_arm_topic_hw
{

hardware_interface::CallbackReturn TopicSystem::on_init(const hardware_interface::HardwareInfo & info)
{
  if (hardware_interface::SystemInterface::on_init(info) != hardware_interface::CallbackReturn::SUCCESS) {
    return hardware_interface::CallbackReturn::ERROR;
  }

  // Expect 4 joints: joint1, joint2, joint3, jointPWM
  joint_names_.clear();
  for (const auto & j : info_.joints) {
    joint_names_.push_back(j.name);
  }

  // Basic validation: must have position command/state for each joint
  for (const auto & j : info_.joints) {
    bool has_pos_cmd = false;
    bool has_pos_state = false;

    for (const auto & ci : j.command_interfaces) {
      if (ci.name == hardware_interface::HW_IF_POSITION) has_pos_cmd = true;
    }
    for (const auto & si : j.state_interfaces) {
      if (si.name == hardware_interface::HW_IF_POSITION) has_pos_state = true;
    }

    if (!has_pos_cmd || !has_pos_state) {
      RCLCPP_ERROR(
        rclcpp::get_logger("TopicSystem"),
        "Joint '%s' must define position command + position state interfaces in URDF <ros2_control>.",
        j.name.c_str());
      return hardware_interface::CallbackReturn::ERROR;
    }
  }

  has_velocity_state_ = false;
  for (const auto & j : info_.joints) {
    for (const auto & si : j.state_interfaces) {
      if (si.name == hardware_interface::HW_IF_VELOCITY) {
        has_velocity_state_ = true;
        break;
      }
    }
    if (has_velocity_state_) break;
  }

  // Optional params from URDF <param ...>
  auto it_cmd = info_.hardware_parameters.find("command_topic");
  if (it_cmd != info_.hardware_parameters.end()) {
    command_topic_ = it_cmd->second;
  }
  auto it_fb = info_.hardware_parameters.find("feedback_topic");
  if (it_fb != info_.hardware_parameters.end()) {
    feedback_topic_ = it_fb->second;
  }
  auto it_eps = info_.hardware_parameters.find("epsilon");
  if (it_eps != info_.hardware_parameters.end()) {
    epsilon_ = std::stod(it_eps->second);
  }

  const auto n = joint_names_.size();
  cmd_pos_.assign(n, 0.0);
  state_pos_.assign(n, 0.0);
  state_vel_.assign(n, 0.0);
  fb_latest_pos_.assign(n, 0.0);
  fb_latest_vel_.assign(n, 0.0);
  last_sent_cmd_.assign(n, std::numeric_limits<double>::quiet_NaN());

  return hardware_interface::CallbackReturn::SUCCESS;
}

std::vector<hardware_interface::StateInterface> TopicSystem::export_state_interfaces()
{
  std::vector<hardware_interface::StateInterface> out;
  for (size_t i = 0; i < info_.joints.size(); ++i) {
    out.emplace_back(info_.joints[i].name, hardware_interface::HW_IF_POSITION, &state_pos_[i]);
    if (has_velocity_state_) {
      out.emplace_back(info_.joints[i].name, hardware_interface::HW_IF_VELOCITY, &state_vel_[i]);
    }
  }
  return out;
}

std::vector<hardware_interface::CommandInterface> TopicSystem::export_command_interfaces()
{
  std::vector<hardware_interface::CommandInterface> out;
  out.reserve(joint_names_.size());

  for (size_t i = 0; i < joint_names_.size(); ++i) {
    out.emplace_back(joint_names_[i], hardware_interface::HW_IF_POSITION, &cmd_pos_[i]);
  }
  return out;
}

hardware_interface::CallbackReturn TopicSystem::on_configure(const rclcpp_lifecycle::State &)
{
  // Create a dedicated node for pub/sub
  if (!rclcpp::ok()) {
    // controller_manager typically initializes rclcpp; this is defensive
    RCLCPP_ERROR(rclcpp::get_logger("TopicSystem"), "rclcpp is not initialized.");
    return hardware_interface::CallbackReturn::ERROR;
  }

  node_ = std::make_shared<rclcpp::Node>("mercer_g_arm_topic_hw");

  cmd_pub_ = node_->create_publisher<sensor_msgs::msg::JointState>(command_topic_, 10);

  fb_sub_ = node_->create_subscription<sensor_msgs::msg::JointState>(
    feedback_topic_, 10,
    std::bind(&TopicSystem::feedback_cb, this, std::placeholders::_1));

  // Initialize state to 0, wait for feedback at activate
  fb_received_.store(false);

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn TopicSystem::on_activate(const rclcpp_lifecycle::State &)
{
  start_executor_thread();

  // Optional: wait briefly for first feedback so /joint_states starts “real”
  const auto start = std::chrono::steady_clock::now();
  while (!fb_received_.load()) {
    if (std::chrono::steady_clock::now() - start > std::chrono::seconds(2)) {
      RCLCPP_WARN(node_->get_logger(),
        "No feedback received on %s after 2s; continuing open-loop.",
        feedback_topic_.c_str());
      break;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }

  // Set command = current state to avoid jumps at activation
  {
    std::lock_guard<std::mutex> lk(fb_mutex_);
    state_pos_ = fb_latest_pos_;
  }
  cmd_pos_ = state_pos_;

  return hardware_interface::CallbackReturn::SUCCESS;
}

hardware_interface::CallbackReturn TopicSystem::on_deactivate(const rclcpp_lifecycle::State &)
{
  stop_executor_thread();
  return hardware_interface::CallbackReturn::SUCCESS;
}

void TopicSystem::feedback_cb(const sensor_msgs::msg::JointState::SharedPtr msg)
{
  if (!msg) return;

  std::unordered_map<std::string, double> pos_map;
  std::unordered_map<std::string, double> vel_map;
  for (size_t i = 0; i < msg->name.size(); ++i) {
    if (i < msg->position.size()) {
      pos_map[msg->name[i]] = msg->position[i];
    }
    if (has_velocity_state_ && i < msg->velocity.size()) {
      vel_map[msg->name[i]] = msg->velocity[i];
    }
  }

  std::lock_guard<std::mutex> lk(fb_mutex_);
  for (size_t i = 0; i < joint_names_.size(); ++i) {
    auto it = pos_map.find(joint_names_[i]);
    if (it != pos_map.end()) {
      fb_latest_pos_[i] = it->second;
    }
    if (has_velocity_state_) {
      auto vit = vel_map.find(joint_names_[i]);
      fb_latest_vel_[i] = (vit != vel_map.end()) ? vit->second : 0.0;
    }
  }
  fb_received_.store(true);
}

hardware_interface::return_type TopicSystem::read(const rclcpp::Time &, const rclcpp::Duration &)
{
  if (fb_received_.load()) {
    std::lock_guard<std::mutex> lk(fb_mutex_);
    state_pos_ = fb_latest_pos_;
    if (has_velocity_state_) {
      state_vel_ = fb_latest_vel_;
    }
  } else {
    state_pos_ = cmd_pos_;
    if (has_velocity_state_) {
      std::fill(state_vel_.begin(), state_vel_.end(), 0.0);
    }
  }
  return hardware_interface::return_type::OK;
}

hardware_interface::return_type TopicSystem::write(const rclcpp::Time &, const rclcpp::Duration &)
{
  if (!cmd_pub_) return hardware_interface::return_type::ERROR;

  // Throttle: publish only when something changed beyond epsilon
  bool changed = false;
  for (size_t i = 0; i < cmd_pos_.size(); ++i) {
    const double last = last_sent_cmd_[i];
    if (std::isnan(last) || std::abs(cmd_pos_[i] - last) > epsilon_) {
      changed = true;
      break;
    }
  }
  if (!changed) {
    return hardware_interface::return_type::OK;
  }

  sensor_msgs::msg::JointState js;
  js.header.stamp = node_->get_clock()->now();
  js.name = joint_names_;
  js.position = cmd_pos_;

  cmd_pub_->publish(js);

  last_sent_cmd_ = cmd_pos_;
  return hardware_interface::return_type::OK;
}

void TopicSystem::start_executor_thread()
{
  if (executor_running_.exchange(true)) return;

  executor_.add_node(node_);
  executor_thread_ = std::thread([this]() {
    while (executor_running_.load()) {
      executor_.spin_some();
      std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }
    executor_.remove_node(node_);
  });
}

void TopicSystem::stop_executor_thread()
{
  if (!executor_running_.exchange(false)) return;
  if (executor_thread_.joinable()) executor_thread_.join();
}

}  // namespace g_arm_topic_hw

PLUGINLIB_EXPORT_CLASS(mercer_g_arm_topic_hw::TopicSystem, hardware_interface::SystemInterface)
