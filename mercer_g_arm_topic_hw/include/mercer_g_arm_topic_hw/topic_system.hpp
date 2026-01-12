#pragma once

#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "hardware_interface/system_interface.hpp"
#include "hardware_interface/types/hardware_interface_return_values.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"

namespace mercer_g_arm_topic_hw
{

class TopicSystem : public hardware_interface::SystemInterface
{
public:
  hardware_interface::CallbackReturn on_init(const hardware_interface::HardwareInfo & info) override;

  std::vector<hardware_interface::StateInterface> export_state_interfaces() override;
  std::vector<hardware_interface::CommandInterface> export_command_interfaces() override;

  hardware_interface::CallbackReturn on_configure(
    const rclcpp_lifecycle::State & /*previous_state*/) override;

  hardware_interface::CallbackReturn on_activate(
    const rclcpp_lifecycle::State & /*previous_state*/) override;

  hardware_interface::CallbackReturn on_deactivate(
    const rclcpp_lifecycle::State & /*previous_state*/) override;

  hardware_interface::return_type read(
    const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/) override;

  hardware_interface::return_type write(
    const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/) override;

private:
  void feedback_cb(const sensor_msgs::msg::JointState::SharedPtr msg);
  void start_executor_thread();
  void stop_executor_thread();

  // Parameters
  std::string command_topic_{"/joint_commands"};
  std::string feedback_topic_{"/joint_states_raw"};
  std::vector<std::string> joint_names_;

  // ros2 interfaces
  rclcpp::Node::SharedPtr node_;
  rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr cmd_pub_;
  rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr fb_sub_;

  rclcpp::executors::SingleThreadedExecutor executor_;
  std::thread executor_thread_;
  std::atomic<bool> executor_running_{false};

  // Data buffers
  std::vector<double> cmd_pos_;
  std::vector<double> state_pos_;

  // Feedback bookkeeping
  std::mutex fb_mutex_;
  std::vector<double> fb_latest_pos_;
  std::atomic<bool> fb_received_{false};

  // Throttle command publishing
  std::vector<double> last_sent_cmd_;
  double epsilon_{1e-6};
};

}  // namespace g_arm_topic_hw
