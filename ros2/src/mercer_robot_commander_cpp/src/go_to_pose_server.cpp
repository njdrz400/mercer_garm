#include <rclcpp/rclcpp.hpp>
#include <rclcpp_action/rclcpp_action.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_state/conversions.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <control_msgs/action/follow_joint_trajectory.hpp>
#include <trajectory_msgs/msg/joint_trajectory.hpp>
#include <trajectory_msgs/msg/joint_trajectory_point.hpp>
#include <tf2_eigen/tf2_eigen.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/buffer.h>
#include <chrono>
#include <cmath>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <future>
#include <algorithm>
#include <cstdlib>
#include <ctime>

#include "g_arm_msgs/action/go_to_pose.hpp"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using GoToPose = g_arm_msgs::action::GoToPose;
using FollowJointTrajectory = control_msgs::action::FollowJointTrajectory;
using namespace std::chrono_literals;

/**
 * Compute IK for a target pose
 */
bool computeIK(
    moveit::planning_interface::MoveGroupInterface& arm,
    const geometry_msgs::msg::PoseStamped& pose,
    std::vector<double>& joint_values,
    std::vector<std::string>& joint_names)
{
    const moveit::core::RobotModelConstPtr& robot_model = arm.getRobotModel();
    if (!robot_model) {
        return false;
    }
    
    const std::string& group_name = arm.getName();
    const moveit::core::JointModelGroup* joint_model_group = 
        robot_model->getJointModelGroup(group_name);
    
    if (!joint_model_group) {
        return false;
    }
    
    joint_names = arm.getJointNames();
    
    moveit::core::RobotState robot_state(robot_model);
    robot_state.setToDefaultValues();
    
    // Try to get current state as seed for IK
    bool using_current_state = false;
    try {
        moveit::core::RobotStatePtr current_state = arm.getCurrentState();
        if (current_state) {
            std::vector<double> seed_state;
            current_state->copyJointGroupPositions(joint_model_group, seed_state);
            if (!seed_state.empty()) {
                robot_state.setJointGroupPositions(joint_model_group, seed_state);
                robot_state.update();
                using_current_state = true;
            }
        }
    } catch (const std::exception& e) {
        // Current state unavailable - will use default values
    }
    
    if (!using_current_state) {
        robot_state.setToDefaultValues();
        robot_state.update();
    }
    
    std::string end_effector_link = arm.getEndEffectorLink();
    const moveit::core::LinkModel* link_model = robot_model->getLinkModel(end_effector_link);
    if (!link_model) {
        return false;
    }
    
    Eigen::Isometry3d target_pose_eigen;
    tf2::fromMsg(pose.pose, target_pose_eigen);
    // Use only position (x,y,z) for IK; ignore orientation so electromagnet pose is not constrained.
    // This avoids IK failure due to unreachable orientation and matches kinematics position_only_ik.
    target_pose_eigen.linear() = Eigen::Matrix3d::Identity();

    // Try IK with many attempts and diverse seeds (KDL is sensitive to seed; timeout is in kinematics.yaml)
    const int max_attempts = 100;
    bool found_ik = false;
    for (int attempt = 0; attempt < max_attempts && !found_ik; ++attempt) {
        if (attempt == 1 && using_current_state) {
            robot_state.setToDefaultValues();
            robot_state.update();
        } else if (attempt > 1) {
            std::vector<double> seed_state;
            robot_state.copyJointGroupPositions(joint_model_group, seed_state);
            double scale = (attempt <= 15) ? 0.05 : 0.2;  // broader spread for later attempts
            for (auto& val : seed_state) {
                val += (rand() % 200 - 100) * scale;
            }
            robot_state.setJointGroupPositions(joint_model_group, seed_state);
            robot_state.update();
        }
        found_ik = robot_state.setFromIK(
            joint_model_group,
            target_pose_eigen,
            end_effector_link
        );
    }

    // If still no solution, retry with tiny position nudges (±2 mm) to escape singularities / numerical edges
    const double nudge_m = 0.002;
    if (!found_ik) {
        double dx[] = {0, 1, -1, 0, 0, 0, 0, 0};
        double dy[] = {0, 0, 0, 1, -1, 0, 0, 0};
        double dz[] = {0, 0, 0, 0, 0, 1, -1, 0};
        for (int n = 0; n < 8 && !found_ik; ++n) {
            Eigen::Isometry3d nudged = target_pose_eigen;
            nudged.translation().x() += nudge_m * dx[n];
            nudged.translation().y() += nudge_m * dy[n];
            nudged.translation().z() += nudge_m * dz[n];
            robot_state.setToDefaultValues();
            robot_state.update();
            for (int k = 0; k < 15 && !found_ik; ++k) {
                if (k > 0) {
                    std::vector<double> seed_state;
                    robot_state.copyJointGroupPositions(joint_model_group, seed_state);
                    for (auto& val : seed_state)
                        val += (rand() % 200 - 100) * 0.1;
                    robot_state.setJointGroupPositions(joint_model_group, seed_state);
                    robot_state.update();
                }
                found_ik = robot_state.setFromIK(joint_model_group, nudged, end_effector_link);
            }
        }
    }

    if (!found_ik) {
        joint_values.clear();
        return false;
    }
    
    robot_state.copyJointGroupPositions(joint_model_group, joint_values);
    return true;
}

/**
 * Compute forward kinematics to get current end effector pose
 */
bool computeFK(
    moveit::planning_interface::MoveGroupInterface& arm,
    const std::vector<double>& joint_values,
    geometry_msgs::msg::PoseStamped& pose)
{
    const moveit::core::RobotModelConstPtr& robot_model = arm.getRobotModel();
    if (!robot_model) {
        return false;
    }
    
    const std::string& group_name = arm.getName();
    const moveit::core::JointModelGroup* joint_model_group = 
        robot_model->getJointModelGroup(group_name);
    
    if (!joint_model_group) {
        return false;
    }
    
    moveit::core::RobotState robot_state(robot_model);
    robot_state.setJointGroupPositions(joint_model_group, joint_values);
    robot_state.update();
    
    std::string end_effector_link = arm.getEndEffectorLink();
    const Eigen::Isometry3d& transform = robot_state.getGlobalLinkTransform(end_effector_link);
    
    pose.header.frame_id = arm.getPlanningFrame();
    pose.header.stamp = arm.getNode()->now();
    pose.pose = tf2::toMsg(transform);
    
    return true;
}

/**
 * Compute position error between two poses
 */
double computePositionError(
    const geometry_msgs::msg::Pose& pose1,
    const geometry_msgs::msg::Pose& pose2)
{
    double dx = pose1.position.x - pose2.position.x;
    double dy = pose1.position.y - pose2.position.y;
    double dz = pose1.position.z - pose2.position.z;
    return std::sqrt(dx*dx + dy*dy + dz*dz);
}

/**
 * Compute orientation error between two quaternions (angle in radians)
 * Accounts for quaternion double cover (q and -q represent the same rotation)
 */
double computeOrientationError(
    const geometry_msgs::msg::Quaternion& q1,
    const geometry_msgs::msg::Quaternion& q2)
{
    // Compute dot product to handle quaternion double cover
    // If dot product is negative, one quaternion is the negation of the other
    // (they represent the same rotation, so we should use the positive one)
    double dot = q1.w * q2.w + q1.x * q2.x + q1.y * q2.y + q1.z * q2.z;
    
    // Clamp to [-1, 1] to avoid numerical errors
    dot = std::max(-1.0, std::min(1.0, dot));
    
    // Take absolute value to handle double cover
    // angle = 2 * acos(|dot|) gives the angle between the rotations
    double angle = 2.0 * std::acos(std::abs(dot));
    
    // Ensure angle is in [0, π]
    return std::min(angle, M_PI);
}

class GoToPoseActionServer : public rclcpp::Node
{
public:
    GoToPoseActionServer()
        : Node("go_to_pose_server"),
          tf_buffer_(std::make_shared<rclcpp::Clock>()),
          tf_listener_(tf_buffer_),
          initialized_(false)
    {
        // Note: MoveGroupInterface will be initialized in initialize() method
        // after the node is fully constructed as a shared_ptr
        
        // Subscribe to joint states for feedback
        joint_state_sub_ = this->create_subscription<sensor_msgs::msg::JointState>(
            "/joint_states", 10,
            std::bind(&GoToPoseActionServer::jointStateCallback, this, std::placeholders::_1));
        
        // Create action client for FollowJointTrajectory (arm controller)
        trajectory_action_client_ = rclcpp_action::create_client<FollowJointTrajectory>(
            this, "/arm_controller/follow_joint_trajectory");
        
        // Create action client for tool controller (electromagnet)
        // Note: The controller might be named "tool_controller" or "magnet_controller"
        // Try tool_controller first, fallback to magnet_controller if needed
        tool_action_client_ = rclcpp_action::create_client<FollowJointTrajectory>(
            this, "/tool_controller/follow_joint_trajectory");
        
        // Also try magnet_controller as alternative
        magnet_action_client_ = rclcpp_action::create_client<FollowJointTrajectory>(
            this, "/magnet_controller/follow_joint_trajectory");
        
        // Create action server for GoToPose
        action_server_ = rclcpp_action::create_server<GoToPose>(
            this,
            "go_to_pose",
            std::bind(&GoToPoseActionServer::handleGoal, this, std::placeholders::_1, std::placeholders::_2),
            std::bind(&GoToPoseActionServer::handleCancel, this, std::placeholders::_1),
            std::bind(&GoToPoseActionServer::handleAccepted, this, std::placeholders::_1));
    }
    
    void initialize()
    {
        // Create move group interface (called after node is fully constructed)
        arm_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(
            shared_from_this(), "arm");
        arm_->setMaxVelocityScalingFactor(1.0);
        arm_->setMaxAccelerationScalingFactor(1.0);
        
        // Get all joint names from MoveIt (includes passive/mimic joints)
        auto all_joint_names = arm_->getJointNames();
        RCLCPP_INFO(this->get_logger(), "Arm group has %zu joints (including passive/mimic)", all_joint_names.size());
        
        // Filter to only active joints that the controller expects
        // The controller only accepts: joint1, joint2, joint3
        std::vector<std::string> controller_joints = {"joint1", "joint2", "joint3"};
        joint_names_.clear();
        for (const auto& name : controller_joints) {
            if (std::find(all_joint_names.begin(), all_joint_names.end(), name) != all_joint_names.end()) {
                joint_names_.push_back(name);
            }
        }
        
        RCLCPP_INFO(this->get_logger(), "Controller expects %zu active joints:", joint_names_.size());
        for (const auto& name : joint_names_) {
            RCLCPP_INFO(this->get_logger(), "  - %s", name.c_str());
        }
        
        // Wait for trajectory action client
        if (!trajectory_action_client_->wait_for_action_server(5s)) {
            RCLCPP_WARN(this->get_logger(), 
                "FollowJointTrajectory action server not available, but continuing...");
        }
        
        RCLCPP_INFO(this->get_logger(), "GoToPose action server ready");
        initialized_ = true;
    }

private:
    void jointStateCallback(const sensor_msgs::msg::JointState::SharedPtr msg)
    {
        std::lock_guard<std::mutex> lock(joint_state_mutex_);
        latest_joint_state_ = msg;
    }
    
    rclcpp_action::GoalResponse handleGoal(
        const rclcpp_action::GoalUUID& uuid,
        std::shared_ptr<const GoToPose::Goal> goal)
    {
        (void)uuid;
        
        // Validate goal
        if (goal->timeout_sec <= 0.0) {
            RCLCPP_WARN(this->get_logger(), "Rejected goal: invalid timeout");
            return rclcpp_action::GoalResponse::REJECT;
        }
        
        if (goal->pos_tolerance_m < 0.0 || goal->ang_tolerance_rad < 0.0) {
            RCLCPP_WARN(this->get_logger(), "Rejected goal: invalid tolerances");
            return rclcpp_action::GoalResponse::REJECT;
        }
        
        RCLCPP_INFO(this->get_logger(), "Accepted goal");
        return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }
    
    rclcpp_action::CancelResponse handleCancel(
        const std::shared_ptr<rclcpp_action::ServerGoalHandle<GoToPose>> goal_handle)
    {
        RCLCPP_INFO(this->get_logger(), "Cancel requested");
        (void)goal_handle;
        return rclcpp_action::CancelResponse::ACCEPT;
    }
    
    void handleAccepted(const std::shared_ptr<rclcpp_action::ServerGoalHandle<GoToPose>> goal_handle)
    {
        std::thread{std::bind(&GoToPoseActionServer::executeGoal, this, goal_handle)}.detach();
    }
    
    void executeGoal(const std::shared_ptr<rclcpp_action::ServerGoalHandle<GoToPose>> goal_handle)
    {
        // Ensure MoveGroupInterface is initialized
        if (!initialized_ || !arm_) {
            auto result = std::make_shared<GoToPose::Result>();
            result->success = false;
            result->error_code = 12;
            result->message = "Action server not fully initialized";
            goal_handle->abort(result);
            return;
        }
        
        const auto goal = goal_handle->get_goal();
        auto result = std::make_shared<GoToPose::Result>();
        auto feedback = std::make_shared<GoToPose::Feedback>();
        
        auto start_time = this->now();
        auto timeout = rclcpp::Duration::from_seconds(goal->timeout_sec);
        
        // Transform target pose to planning frame if needed
        geometry_msgs::msg::PoseStamped target_pose = goal->target;
        std::string planning_frame = arm_->getPlanningFrame();
        
        if (!goal->planner_frame.empty() && goal->planner_frame != target_pose.header.frame_id) {
            // Transform to planner_frame
            try {
                geometry_msgs::msg::TransformStamped transform = tf_buffer_.lookupTransform(
                    goal->planner_frame, target_pose.header.frame_id, tf2::TimePointZero);
                tf2::doTransform(target_pose, target_pose, transform);
            } catch (const tf2::TransformException& ex) {
                RCLCPP_ERROR(this->get_logger(), "Transform failed: %s", ex.what());
                result->success = false;
                result->error_code = 1;
                result->message = "Failed to transform target pose: " + std::string(ex.what());
                goal_handle->abort(result);
                return;
            }
        }
        
        // If target is not in planning frame, transform it
        if (target_pose.header.frame_id != planning_frame) {
            try {
                geometry_msgs::msg::TransformStamped transform = tf_buffer_.lookupTransform(
                    planning_frame, target_pose.header.frame_id, tf2::TimePointZero);
                tf2::doTransform(target_pose, target_pose, transform);
            } catch (const tf2::TransformException& ex) {
                RCLCPP_ERROR(this->get_logger(), "Transform to planning frame failed: %s", ex.what());
                result->success = false;
                result->error_code = 2;
                result->message = "Failed to transform to planning frame: " + std::string(ex.what());
                goal_handle->abort(result);
                return;
            }
        }
        
        // Phase 1: IK computation
        feedback->state = "IK";
        feedback->detail = "Computing inverse kinematics...";
        goal_handle->publish_feedback(feedback);
        
        std::vector<double> target_joint_values;
        std::vector<std::string> ik_joint_names;
        
        std::vector<double> all_target_joint_values;
        std::vector<std::string> all_ik_joint_names;
        
        bool ik_success = computeIK(*arm_, target_pose, all_target_joint_values, all_ik_joint_names);
        
        if (!ik_success) {
            // Detailed diagnostics for KDL IK failure
            RCLCPP_ERROR(this->get_logger(), "IK solution not found (KDL kinematics plugin)");
            RCLCPP_ERROR(this->get_logger(), "  Target pose (frame: %s): position x=%.4f y=%.4f z=%.4f",
                target_pose.header.frame_id.c_str(),
                target_pose.pose.position.x, target_pose.pose.position.y, target_pose.pose.position.z);
            RCLCPP_ERROR(this->get_logger(), "  Target orientation: w=%.4f x=%.4f y=%.4f z=%.4f",
                target_pose.pose.orientation.w, target_pose.pose.orientation.x,
                target_pose.pose.orientation.y, target_pose.pose.orientation.z);
            try {
                moveit::core::RobotStatePtr cur = arm_->getCurrentState();
                if (cur) {
                    std::vector<double> cur_joints;
                    const moveit::core::JointModelGroup* jmg = arm_->getRobotModel()->getJointModelGroup(arm_->getName());
                    if (jmg) {
                        cur->copyJointGroupPositions(jmg, cur_joints);
                        geometry_msgs::msg::PoseStamped current_pose;
                        if (computeFK(*arm_, cur_joints, current_pose)) {
                            double dx = target_pose.pose.position.x - current_pose.pose.position.x;
                            double dy = target_pose.pose.position.y - current_pose.pose.position.y;
                            double dz = target_pose.pose.position.z - current_pose.pose.position.z;
                            double dist = std::sqrt(dx*dx + dy*dy + dz*dz);
                            RCLCPP_ERROR(this->get_logger(), "  Current EE position: x=%.4f y=%.4f z=%.4f (distance to target: %.4f m)",
                                current_pose.pose.position.x, current_pose.pose.position.y, current_pose.pose.position.z, dist);
                        }
                    }
                }
            } catch (const std::exception& e) {
                RCLCPP_ERROR(this->get_logger(), "  (Could not get current state for diagnostics: %s)", e.what());
            }
            RCLCPP_ERROR(this->get_logger(), "  Possible causes: target outside workspace, near singularity, or joint limits. "
                "Tried 100 seeds plus position nudges. Try TRAC-IK (see g_arm_moveit2/TRAC_IK_SETUP.md) or adjust kinematics.yaml.");
            result->success = false;
            result->error_code = 3;
            result->message = "IK solution not found - pose may be unreachable (see log for target pose and diagnostics)";
            goal_handle->abort(result);
            return;
        }
        
        // Extract only the active joint values that the controller expects
        target_joint_values.clear();
        for (const auto& joint_name : joint_names_) {
            bool found = false;
            for (size_t i = 0; i < all_ik_joint_names.size(); ++i) {
                if (all_ik_joint_names[i] == joint_name) {
                    if (i < all_target_joint_values.size()) {
                        target_joint_values.push_back(all_target_joint_values[i]);
                        found = true;
                    }
                    break;
                }
            }
            if (!found) {
                RCLCPP_ERROR(this->get_logger(), "IK solution missing joint: %s", joint_name.c_str());
                result->success = false;
                result->error_code = 3;
                result->message = "IK solution incomplete - missing joint: " + joint_name;
                goal_handle->abort(result);
                return;
            }
        }
        
        // Validate joint limits for active joints only
        const moveit::core::RobotModelConstPtr& robot_model = arm_->getRobotModel();
        
        bool within_limits = true;
        for (size_t i = 0; i < target_joint_values.size() && i < joint_names_.size(); ++i) {
            const moveit::core::JointModel* joint_model = 
                robot_model->getJointModel(joint_names_[i]);
            if (joint_model && joint_model->getVariableCount() > 0) {
                const moveit::core::VariableBounds& bounds = 
                    joint_model->getVariableBounds()[0];
                if (target_joint_values[i] < bounds.min_position_ || 
                    target_joint_values[i] > bounds.max_position_) {
                    RCLCPP_WARN(this->get_logger(), 
                        "Joint %s value %.4f outside limits [%.4f, %.4f]",
                        joint_names_[i].c_str(), target_joint_values[i],
                        bounds.min_position_, bounds.max_position_);
                    within_limits = false;
                }
            }
        }
        
        if (!within_limits) {
            result->success = false;
            result->error_code = 4;
            result->message = "IK solution violates joint limits";
            goal_handle->abort(result);
            return;
        }
        
        // Verify IK solution achieves target orientation (if orientation is enforced)
        // allow_orientation: false = enforce orientation (orientation IS important)
        // allow_orientation: true = ignore orientation (orientation is NOT important)
        if (!goal->allow_orientation) {
            // Reconstruct full joint state for FK verification
            std::vector<double> all_ik_joint_values_for_fk;
            for (const auto& joint_name : all_ik_joint_names) {
                bool found = false;
                for (size_t i = 0; i < all_ik_joint_names.size(); ++i) {
                    if (all_ik_joint_names[i] == joint_name) {
                        if (i < all_target_joint_values.size()) {
                            all_ik_joint_values_for_fk.push_back(all_target_joint_values[i]);
                            found = true;
                        }
                        break;
                    }
                }
                if (!found) {
                    all_ik_joint_values_for_fk.push_back(0.0);
                }
            }
            
            if (all_ik_joint_values_for_fk.size() == all_ik_joint_names.size()) {
                geometry_msgs::msg::PoseStamped ik_pose;
                if (computeFK(*arm_, all_ik_joint_values_for_fk, ik_pose)) {
                    double ik_ang_error = computeOrientationError(
                        ik_pose.pose.orientation, target_pose.pose.orientation);
                    
                    RCLCPP_INFO(this->get_logger(), 
                        "IK solution orientation check: error=%.4f rad, tolerance=%.4f rad",
                        ik_ang_error, goal->ang_tolerance_rad);
                    RCLCPP_INFO(this->get_logger(), 
                        "Target orientation: w=%.4f, x=%.4f, y=%.4f, z=%.4f",
                        target_pose.pose.orientation.w, target_pose.pose.orientation.x,
                        target_pose.pose.orientation.y, target_pose.pose.orientation.z);
                    RCLCPP_INFO(this->get_logger(), 
                        "IK solution orientation: w=%.4f, x=%.4f, y=%.4f, z=%.4f",
                        ik_pose.pose.orientation.w, ik_pose.pose.orientation.x,
                        ik_pose.pose.orientation.y, ik_pose.pose.orientation.z);
                    
                    if (ik_ang_error > goal->ang_tolerance_rad) {
                        RCLCPP_WARN(this->get_logger(), 
                            "IK solution orientation error (%.4f rad) exceeds tolerance (%.4f rad)",
                            ik_ang_error, goal->ang_tolerance_rad);
                        result->success = false;
                        result->error_code = 13;
                        result->message = "IK solution cannot achieve target orientation within tolerance";
                        goal_handle->abort(result);
                        return;
                    }
                }
            }
        }
        
        RCLCPP_INFO(this->get_logger(), "IK solution found for %zu active joints", target_joint_values.size());
        
        // Phase 2: Create and send trajectory
        feedback->state = "SENDING_TRAJ";
        feedback->detail = "Sending trajectory to controller...";
        goal_handle->publish_feedback(feedback);
        
        // Get current joint state
        std::vector<double> start_joint_values;
        {
            std::lock_guard<std::mutex> lock(joint_state_mutex_);
            if (latest_joint_state_) {
                // Map joint states to our joint names
                for (const auto& joint_name : joint_names_) {
                    bool found = false;
                    for (size_t i = 0; i < latest_joint_state_->name.size(); ++i) {
                        if (latest_joint_state_->name[i] == joint_name) {
                            if (i < latest_joint_state_->position.size()) {
                                start_joint_values.push_back(latest_joint_state_->position[i]);
                                found = true;
                            }
                            break;
                        }
                    }
                    if (!found) {
                        RCLCPP_WARN(this->get_logger(), 
                            "Joint %s not found in joint_states, using 0.0", joint_name.c_str());
                        start_joint_values.push_back(0.0);
                    }
                }
            } else {
                RCLCPP_WARN(this->get_logger(), "No joint state available, using zeros");
                start_joint_values.resize(joint_names_.size(), 0.0);
            }
        }
        
        if (start_joint_values.size() != joint_names_.size()) {
            start_joint_values.resize(joint_names_.size(), 0.0);
        }
        
        // Create trajectory with two points: start and goal
        auto trajectory_msg = std::make_shared<trajectory_msgs::msg::JointTrajectory>();
        trajectory_msg->joint_names = joint_names_;
        
        // Compute trajectory duration (simple linear interpolation)
        double max_joint_vel = (goal->max_joint_vel > 0.0) ? goal->max_joint_vel : 1.0;
        double max_duration = 0.0;
        for (size_t i = 0; i < joint_names_.size() && i < start_joint_values.size() && 
             i < target_joint_values.size(); ++i) {
            double joint_diff = std::abs(target_joint_values[i] - start_joint_values[i]);
            double duration = joint_diff / max_joint_vel;
            if (duration > max_duration) {
                max_duration = duration;
            }
        }
        max_duration = std::max(max_duration, 1.0); // Minimum 1 second
        
        // Apply speed scale
        if (goal->speed_scale > 0.0 && goal->speed_scale <= 1.0) {
            max_duration /= goal->speed_scale;
        }
        
        // Start point
        trajectory_msgs::msg::JointTrajectoryPoint start_point;
        start_point.positions = start_joint_values;
        start_point.time_from_start = rclcpp::Duration::from_seconds(0.0);
        trajectory_msg->points.push_back(start_point);
        
        // Goal point
        trajectory_msgs::msg::JointTrajectoryPoint goal_point;
        goal_point.positions = target_joint_values;
        goal_point.time_from_start = rclcpp::Duration::from_seconds(max_duration);
        trajectory_msg->points.push_back(goal_point);
        
        // Send trajectory goal
        auto trajectory_goal = FollowJointTrajectory::Goal();
        trajectory_goal.trajectory = *trajectory_msg;
        
        if (!trajectory_action_client_->wait_for_action_server(2s)) {
            result->success = false;
            result->error_code = 5;
            result->message = "Trajectory action server not available";
            goal_handle->abort(result);
            return;
        }
        
        auto send_goal_options = rclcpp_action::Client<FollowJointTrajectory>::SendGoalOptions();
        send_goal_options.result_callback = 
            [this](const rclcpp_action::ClientGoalHandle<FollowJointTrajectory>::WrappedResult& result) {
                (void)result;
                // Result handled in main execution loop
            };
        
        auto trajectory_future = trajectory_action_client_->async_send_goal(trajectory_goal, send_goal_options);
        
        // Wait for goal to be sent (let main executor handle callbacks)
        auto wait_start = std::chrono::steady_clock::now();
        while (trajectory_future.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) {
            if (std::chrono::steady_clock::now() - wait_start > std::chrono::seconds(2)) {
                result->success = false;
                result->error_code = 6;
                result->message = "Failed to send trajectory goal (timeout)";
                goal_handle->abort(result);
                return;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        auto trajectory_goal_handle = trajectory_future.get();
        if (!trajectory_goal_handle) {
            result->success = false;
            result->error_code = 7;
            result->message = "Trajectory goal rejected";
            goal_handle->abort(result);
            return;
        }
        
        RCLCPP_INFO(this->get_logger(), "Trajectory goal accepted");
        
        // Phase 3: Monitor execution
        feedback->state = "EXECUTING";
        feedback->detail = "Executing trajectory...";
        
        auto result_future = trajectory_action_client_->async_get_result(trajectory_goal_handle);
        
        // Monitor loop
        rclcpp::Rate rate(10.0); // 10 Hz feedback rate
        bool trajectory_complete = false;
        bool trajectory_succeeded = false;
        
        while (rclcpp::ok() && !trajectory_complete) {
            // Check timeout
            if (this->now() - start_time > timeout) {
                RCLCPP_WARN(this->get_logger(), "Goal timeout exceeded");
                trajectory_action_client_->async_cancel_goal(trajectory_goal_handle);
                result->success = false;
                result->error_code = 8;
                result->message = "Timeout exceeded";
                goal_handle->abort(result);
                return;
            }
            
            // Check if goal was canceled
            if (goal_handle->is_canceling()) {
                RCLCPP_INFO(this->get_logger(), "Goal canceled");
                trajectory_action_client_->async_cancel_goal(trajectory_goal_handle);
                result->success = false;
                result->error_code = 9;
                result->message = "Goal canceled by user";
                goal_handle->canceled(result);
                return;
            }
            
            // Check trajectory result (let main executor handle callbacks)
            if (result_future.wait_for(std::chrono::milliseconds(0)) == std::future_status::ready) {
                trajectory_complete = true;
                auto trajectory_result = result_future.get();
                trajectory_succeeded = (trajectory_result.code == 
                    rclcpp_action::ResultCode::SUCCEEDED);
            }
            
            // Compute current pose error
            // For FK, we need ALL joint values (including passive/mimic joints)
            std::vector<double> all_current_joint_values;
            {
                std::lock_guard<std::mutex> lock(joint_state_mutex_);
                if (latest_joint_state_ && latest_joint_state_->name.size() == latest_joint_state_->position.size()) {
                    // Get all joint names from MoveIt (including passive joints)
                    auto all_joint_names = arm_->getJointNames();
                    
                    // Map joint_states to MoveIt joint order
                    for (const auto& joint_name : all_joint_names) {
                        bool found = false;
                        for (size_t i = 0; i < latest_joint_state_->name.size(); ++i) {
                            if (latest_joint_state_->name[i] == joint_name) {
                                if (i < latest_joint_state_->position.size()) {
                                    all_current_joint_values.push_back(latest_joint_state_->position[i]);
                                    found = true;
                                }
                                break;
                            }
                        }
                        if (!found) {
                            all_current_joint_values.push_back(0.0);
                        }
                    }
                }
            }
            
            if (all_current_joint_values.size() == arm_->getJointNames().size()) {
                geometry_msgs::msg::PoseStamped current_pose;
                if (computeFK(*arm_, all_current_joint_values, current_pose)) {
                    double pos_error = computePositionError(current_pose.pose, target_pose.pose);
                    double ang_error = 0.0;
                    
                    if (!goal->allow_orientation) {
                        ang_error = computeOrientationError(
                            current_pose.pose.orientation, target_pose.pose.orientation);
                    }
                    
                    feedback->pos_error_m = pos_error;
                    feedback->ang_error_rad = ang_error;
                    
                    // Compute progress (simple: based on joint space distance for active joints only)
                    // Get current active joint values for progress calculation
                    std::vector<double> current_active_joint_values;
                    {
                        std::lock_guard<std::mutex> lock(joint_state_mutex_);
                        if (latest_joint_state_) {
                            for (const auto& joint_name : joint_names_) {
                                for (size_t i = 0; i < latest_joint_state_->name.size(); ++i) {
                                    if (latest_joint_state_->name[i] == joint_name) {
                                        if (i < latest_joint_state_->position.size()) {
                                            current_active_joint_values.push_back(latest_joint_state_->position[i]);
                                        }
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    
                    double total_joint_diff = 0.0;
                    double current_joint_diff = 0.0;
                    for (size_t i = 0; i < joint_names_.size() && 
                         i < start_joint_values.size() && 
                         i < target_joint_values.size() && 
                         i < current_active_joint_values.size(); ++i) {
                        double total = std::abs(target_joint_values[i] - start_joint_values[i]);
                        double current = std::abs(target_joint_values[i] - current_active_joint_values[i]);
                        total_joint_diff += total;
                        current_joint_diff += current;
                    }
                    
                    if (total_joint_diff > 1e-6) {
                        feedback->progress = 1.0 - (current_joint_diff / total_joint_diff);
                        feedback->progress = std::max(0.0, std::min(1.0, feedback->progress));
                    } else {
                        feedback->progress = 1.0;
                    }
                    
                    goal_handle->publish_feedback(feedback);
                }
            }
            
            rate.sleep();
        }
        
        // Phase 4: Verify completion
        feedback->state = "VERIFYING";
        feedback->detail = "Verifying final pose...";
        goal_handle->publish_feedback(feedback);
        
        // Brief delay so /joint_states reflects settled position (avoids large spurious pos_error)
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        
        // Get final joint state
        std::vector<double> final_joint_values;
        {
            std::lock_guard<std::mutex> lock(joint_state_mutex_);
            if (latest_joint_state_) {
                for (const auto& joint_name : joint_names_) {
                    for (size_t i = 0; i < latest_joint_state_->name.size(); ++i) {
                        if (latest_joint_state_->name[i] == joint_name) {
                            if (i < latest_joint_state_->position.size()) {
                                final_joint_values.push_back(latest_joint_state_->position[i]);
                            }
                            break;
                        }
                    }
                }
            }
        }
        
        result->final_joint_positions = final_joint_values;
        
        // Compute final pose error
        // For FK, we need ALL joint values (including passive/mimic joints)
        // Get full joint state from latest_joint_state_
        geometry_msgs::msg::PoseStamped final_pose;
        bool fk_success = false;
        
        {
            std::lock_guard<std::mutex> lock(joint_state_mutex_);
            if (latest_joint_state_ && latest_joint_state_->name.size() == latest_joint_state_->position.size()) {
                // Get all joint names from MoveIt (including passive joints)
                auto all_joint_names = arm_->getJointNames();
                std::vector<double> all_final_joint_values;
                
                // Map joint_states to MoveIt joint order
                for (const auto& joint_name : all_joint_names) {
                    bool found = false;
                    for (size_t i = 0; i < latest_joint_state_->name.size(); ++i) {
                        if (latest_joint_state_->name[i] == joint_name) {
                            if (i < latest_joint_state_->position.size()) {
                                all_final_joint_values.push_back(latest_joint_state_->position[i]);
                                found = true;
                            }
                            break;
                        }
                    }
                    if (!found) {
                        // If joint not in joint_states, use 0.0 (shouldn't happen for active joints)
                        all_final_joint_values.push_back(0.0);
                    }
                }
                
                if (all_final_joint_values.size() == all_joint_names.size()) {
                    fk_success = computeFK(*arm_, all_final_joint_values, final_pose);
                }
            }
        }
        
        if (fk_success) {
            double final_pos_error = computePositionError(final_pose.pose, target_pose.pose);
            double final_ang_error = 0.0;
            
            // Always compute orientation error for reporting, but only enforce if allow_orientation is false
            final_ang_error = computeOrientationError(
                final_pose.pose.orientation, target_pose.pose.orientation);
            
            RCLCPP_INFO(this->get_logger(), 
                "Final pose check: pos_error=%.6f m, ang_error=%.6f rad (allow_orientation=%s)",
                final_pos_error, final_ang_error, goal->allow_orientation ? "true" : "false");
            RCLCPP_INFO(this->get_logger(), 
                "Target orientation: w=%.4f, x=%.4f, y=%.4f, z=%.4f",
                target_pose.pose.orientation.w, target_pose.pose.orientation.x,
                target_pose.pose.orientation.y, target_pose.pose.orientation.z);
            RCLCPP_INFO(this->get_logger(), 
                "Final orientation: w=%.4f, x=%.4f, y=%.4f, z=%.4f",
                final_pose.pose.orientation.w, final_pose.pose.orientation.x,
                final_pose.pose.orientation.y, final_pose.pose.orientation.z);
            
            result->final_pos_error_m = final_pos_error;
            result->final_ang_error_rad = final_ang_error;
            
            // Check if within tolerance
            // If allow_orientation is true, we ignore orientation (treat as always OK)
            // If allow_orientation is false, we enforce orientation tolerance
            bool pos_ok = (final_pos_error <= goal->pos_tolerance_m);
            bool ang_ok = goal->allow_orientation ? true : (final_ang_error <= goal->ang_tolerance_rad);
            
            result->success = (trajectory_succeeded && pos_ok && ang_ok);
            
            if (result->success) {
                // Control electromagnet if requested
                if (goal->electromagnet_on) {
                    RCLCPP_INFO(this->get_logger(), "Turning electromagnet ON");
                    controlElectromagnet(true);
                } else {
                    RCLCPP_INFO(this->get_logger(), "Turning electromagnet OFF");
                    controlElectromagnet(false);
                }
                
                result->error_code = 0;
                result->message = "Goal reached successfully";
                RCLCPP_INFO(this->get_logger(), "Goal succeeded: pos_error=%.4f, ang_error=%.4f",
                    final_pos_error, final_ang_error);
                goal_handle->succeed(result);
            } else {
                result->error_code = 10;
                if (!trajectory_succeeded) {
                    result->message = "Trajectory execution failed";
                } else if (!pos_ok) {
                    result->message = "Position tolerance not met";
                } else {
                    result->message = "Orientation tolerance not met";
                }
                RCLCPP_WARN(this->get_logger(), "Goal failed: %s (pos_error=%.4f, ang_error=%.4f)",
                    result->message.c_str(), final_pos_error, final_ang_error);
                goal_handle->abort(result);
            }
        } else {
            result->success = false;
            result->error_code = 11;
            result->message = "Failed to compute final pose";
            RCLCPP_ERROR(this->get_logger(), "Failed to compute final pose");
            goal_handle->abort(result);
        }
    }
    
    std::shared_ptr<moveit::planning_interface::MoveGroupInterface> arm_;
    std::vector<std::string> joint_names_;
    
    rclcpp::Subscription<sensor_msgs::msg::JointState>::SharedPtr joint_state_sub_;
    sensor_msgs::msg::JointState::SharedPtr latest_joint_state_;
    std::mutex joint_state_mutex_;
    
    rclcpp_action::Client<FollowJointTrajectory>::SharedPtr trajectory_action_client_;
    rclcpp_action::Client<FollowJointTrajectory>::SharedPtr tool_action_client_;
    rclcpp_action::Client<FollowJointTrajectory>::SharedPtr magnet_action_client_;
    rclcpp_action::Server<GoToPose>::SharedPtr action_server_;
    
    tf2_ros::Buffer tf_buffer_;
    tf2_ros::TransformListener tf_listener_;
    
    bool initialized_;
    
    // Control electromagnet (jointPWM: 0.0 = off, 1.0 = on)
    bool controlElectromagnet(bool turn_on)
    {
        // Try tool_controller first, then magnet_controller
        rclcpp_action::Client<FollowJointTrajectory>::SharedPtr action_client = nullptr;
        std::string controller_name = "";
        
        if (tool_action_client_ && tool_action_client_->wait_for_action_server(1s)) {
            action_client = tool_action_client_;
            controller_name = "tool_controller";
        } else if (magnet_action_client_ && magnet_action_client_->wait_for_action_server(1s)) {
            action_client = magnet_action_client_;
            controller_name = "magnet_controller";
        }
        
        if (!action_client) {
            RCLCPP_WARN(this->get_logger(), 
                "Neither tool_controller nor magnet_controller action server available");
            RCLCPP_WARN(this->get_logger(), 
                "Electromagnet control will be skipped. Make sure one of these controllers is started.");
            return false;
        }
        
        RCLCPP_INFO(this->get_logger(), "Using %s for electromagnet control", controller_name.c_str());
        
        // Create trajectory for electromagnet
        auto trajectory_msg = std::make_shared<trajectory_msgs::msg::JointTrajectory>();
        trajectory_msg->joint_names = {"jointPWM"};
        
        // Get current electromagnet state
        double current_pwm = 0.0;
        {
            std::lock_guard<std::mutex> lock(joint_state_mutex_);
            if (latest_joint_state_) {
                for (size_t i = 0; i < latest_joint_state_->name.size(); ++i) {
                    if (latest_joint_state_->name[i] == "jointPWM") {
                        if (i < latest_joint_state_->position.size()) {
                            current_pwm = latest_joint_state_->position[i];
                        }
                        break;
                    }
                }
            }
        }
        
        double target_pwm = turn_on ? 1.0 : 0.0;
        
        // If already in desired state, skip
        if (std::abs(current_pwm - target_pwm) < 0.01) {
            RCLCPP_INFO(this->get_logger(), "Electromagnet already %s (PWM=%.2f)", 
                       turn_on ? "ON" : "OFF", current_pwm);
            return true;
        }
        
        // Create trajectory with two points: current and target
        trajectory_msgs::msg::JointTrajectoryPoint start_point;
        start_point.positions = {current_pwm};
        start_point.time_from_start = rclcpp::Duration::from_seconds(0.0);
        trajectory_msg->points.push_back(start_point);
        
        trajectory_msgs::msg::JointTrajectoryPoint goal_point;
        goal_point.positions = {target_pwm};
        goal_point.time_from_start = rclcpp::Duration::from_seconds(0.5); // 0.5 second transition
        trajectory_msg->points.push_back(goal_point);
        
        // Send trajectory goal
        auto tool_goal = FollowJointTrajectory::Goal();
        tool_goal.trajectory = *trajectory_msg;
        
        auto send_goal_options = rclcpp_action::Client<FollowJointTrajectory>::SendGoalOptions();
        
        auto tool_future = action_client->async_send_goal(tool_goal, send_goal_options);
        
        // Wait for goal to be sent
        auto wait_start = std::chrono::steady_clock::now();
        while (tool_future.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) {
            if (std::chrono::steady_clock::now() - wait_start > std::chrono::seconds(2)) {
                RCLCPP_WARN(this->get_logger(), "Failed to send electromagnet command (timeout)");
                return false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        auto tool_goal_handle = tool_future.get();
        if (!tool_goal_handle) {
            RCLCPP_WARN(this->get_logger(), "Electromagnet goal rejected");
            return false;
        }
        
        // Wait for result
        auto result_future = action_client->async_get_result(tool_goal_handle);
        wait_start = std::chrono::steady_clock::now();
        while (result_future.wait_for(std::chrono::milliseconds(100)) != std::future_status::ready) {
            if (std::chrono::steady_clock::now() - wait_start > std::chrono::seconds(2)) {
                RCLCPP_WARN(this->get_logger(), "Electromagnet command timeout");
                return false;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
        
        auto tool_result = result_future.get();
        bool success = (tool_result.code == rclcpp_action::ResultCode::SUCCEEDED);
        
        if (success) {
            RCLCPP_INFO(this->get_logger(), "Electromagnet turned %s", turn_on ? "ON" : "OFF");
        } else {
            RCLCPP_WARN(this->get_logger(), "Electromagnet command failed");
        }
        
        return success;
    }
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    
    auto node = std::make_shared<GoToPoseActionServer>();
    
    // Initialize MoveGroupInterface after node is fully constructed
    node->initialize();
    
    RCLCPP_INFO(node->get_logger(), "GoToPose action server started");
    
    rclcpp::spin(node);
    
    rclcpp::shutdown();
    return 0;
}
