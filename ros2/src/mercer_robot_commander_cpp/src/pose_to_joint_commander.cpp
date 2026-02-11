#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/planning_scene/planning_scene.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>
#include <moveit_msgs/msg/planning_scene.hpp>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_state/conversions.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <example_interfaces/msg/float64_multi_array.hpp>
#include <std_msgs/msg/bool.hpp>
#include <tf2_eigen/tf2_eigen.hpp>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <chrono>
#include <thread>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using FloatArray = example_interfaces::msg::Float64MultiArray;
using Bool = std_msgs::msg::Bool;
using namespace std::placeholders;

/**
 * Convert pose space (position and orientation) to joint space (joint angles)
 * 
 * @param arm MoveGroupInterface for the robot arm
 * @param pose The target pose (position x, y, z and orientation quaternion)
 * @param joint_values Output vector to store the computed joint values
 * @param joint_names Output vector to store the joint names (optional, can be nullptr)
 * @return true if IK solution was found, false otherwise
 */
bool poseToJointSpace(
    moveit::planning_interface::MoveGroupInterface& arm,
    const geometry_msgs::msg::PoseStamped& pose,
    std::vector<double>& joint_values,
    std::vector<std::string>* joint_names = nullptr)
{
    // Get the robot model and planning group
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
    
    // Get joint names
    std::vector<std::string> joint_names_vec = arm.getJointNames();
    if (joint_names != nullptr) {
        *joint_names = joint_names_vec;
    }
    
    // Create a robot state with current joint values as seed
    moveit::core::RobotState robot_state(robot_model);
    robot_state.setToDefaultValues();
    
    // Try to get current state as seed for IK (helps find better solutions)
    // Note: This may fail if joint_state_broadcaster is not running, but IK can still work
    bool using_current_state = false;
    try {
        moveit::core::RobotStatePtr current_state = arm.getCurrentState();
        if (current_state) {
            // Copy current joint values as seed for IK
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
    
    // If we couldn't get current state, use default values as seed
    if (!using_current_state) {
        // Set to default values for the joint group
        robot_state.setToDefaultValues();
        robot_state.update();
    }
    
    // Get the end effector link
    std::string end_effector_link = arm.getEndEffectorLink();
    
    // Set the target pose in the robot state
    const moveit::core::LinkModel* link_model = robot_model->getLinkModel(end_effector_link);
    if (!link_model) {
        return false;
    }
    
    // Convert pose to Eigen
    Eigen::Isometry3d target_pose_eigen;
    tf2::fromMsg(pose.pose, target_pose_eigen);
    
    // Try to set the pose and compute IK
    // Note: setFromIK may need the pose in the planning frame (base_link)
    // The pose should already be in base_link frame based on how we create it
    bool found_ik = robot_state.setFromIK(
        joint_model_group,
        target_pose_eigen,
        end_effector_link
    );
    
    if (!found_ik) {
        joint_values.clear();
        return false;
    }
    
    // Extract joint values from the robot state
    robot_state.copyJointGroupPositions(joint_model_group, joint_values);
    
    return true;
}

class PoseToJointCommander
{
public:
    PoseToJointCommander(std::shared_ptr<rclcpp::Node> node)
        : node_(node)
    {
        // Create move group interface
        arm_ = std::make_shared<moveit::planning_interface::MoveGroupInterface>(node_, "arm");
        arm_->setMaxVelocityScalingFactor(1.0);
        arm_->setMaxAccelerationScalingFactor(1.0);
        
        // Disable collision detection for all links
        RCLCPP_INFO(node_->get_logger(), "Disabling collision detection for all links...");
        try {
            const moveit::core::RobotModelConstPtr& robot_model = arm_->getRobotModel();
            if (!robot_model) {
                RCLCPP_WARN(node_->get_logger(), "Could not get robot model");
            } else {
                std::vector<std::string> link_names = robot_model->getLinkModelNames();
                RCLCPP_INFO(node_->get_logger(), "Found %zu links in robot model", link_names.size());
                
                moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
                moveit_msgs::msg::PlanningScene planning_scene_msg;
                planning_scene_msg.is_diff = true;
                planning_scene_msg.robot_state.is_diff = true;
                
                moveit_msgs::msg::AllowedCollisionMatrix acm_msg;
                for (const auto& link_name : link_names) {
                    acm_msg.entry_names.push_back(link_name);
                }
                
                for (size_t i = 0; i < link_names.size(); ++i) {
                    moveit_msgs::msg::AllowedCollisionEntry entry;
                    for (size_t j = 0; j < link_names.size(); ++j) {
                        entry.enabled.push_back(true);
                    }
                    acm_msg.entry_values.push_back(entry);
                }
                
                planning_scene_msg.allowed_collision_matrix = acm_msg;
                planning_scene_interface.applyPlanningScene(planning_scene_msg);
                
                RCLCPP_INFO(node_->get_logger(), "ACM modified: collision detection disabled for all %zu links", link_names.size());
            }
        } catch (const std::exception& e) {
            RCLCPP_ERROR(node_->get_logger(), "Could not modify ACM: %s", e.what());
        }
        
        // Subscribe to pose commands (expects 3 values: x, y, z)
        pose_cmd_sub_ = node_->create_subscription<FloatArray>(
            "pose_to_joint_command", 10, 
            std::bind(&PoseToJointCommander::poseCommandCallback, this, _1));
        
        // Subscribe to home command (any message on this topic will trigger home)
        home_cmd_sub_ = node_->create_subscription<Bool>(
            "home_command", 10, 
            std::bind(&PoseToJointCommander::homeCommandCallback, this, _1));
        
        RCLCPP_INFO(node_->get_logger(), "PoseToJointCommander initialized");
        RCLCPP_INFO(node_->get_logger(), "Listening on topics:");
        RCLCPP_INFO(node_->get_logger(), "  - pose_to_joint_command: [x, y, z] (orientation ignored, set to identity)");
        RCLCPP_INFO(node_->get_logger(), "  - home_command: any message triggers move to Home position");
    }

private:
    void poseCommandCallback(const FloatArray::SharedPtr msg)
    {
        if (msg->data.empty()) {
            RCLCPP_WARN(node_->get_logger(), "Received empty pose command");
            return;
        }
        
        // Log all received values
        RCLCPP_INFO(node_->get_logger(), "=== Received pose command ===");
        RCLCPP_INFO(node_->get_logger(), "Number of values received: %zu", msg->data.size());
        RCLCPP_INFO(node_->get_logger(), "Raw values:");
        for (size_t i = 0; i < msg->data.size(); ++i) {
            RCLCPP_INFO(node_->get_logger(), "  [%zu] = %.6f", i, msg->data[i]);
        }
        
        // Parse command: expect 3 values (x, y, z)
        if (msg->data.size() != 3) {
            RCLCPP_ERROR(node_->get_logger(), "Invalid pose command size: %zu (expected 3 values: x, y, z)", msg->data.size());
            return;
        }
        
        double x = msg->data[0];
        double y = msg->data[1];
        double z = msg->data[2];
        
        RCLCPP_INFO(node_->get_logger(), "Parsed values:");
        RCLCPP_INFO(node_->get_logger(), "  x = %.6f m", x);
        RCLCPP_INFO(node_->get_logger(), "  y = %.6f m", y);
        RCLCPP_INFO(node_->get_logger(), "  z = %.6f m", z);
        RCLCPP_INFO(node_->get_logger(), "  orientation: identity quaternion (0, 0, 0, 1)");
        
        // Create pose with identity orientation (w=1, no rotation)
        geometry_msgs::msg::PoseStamped pose;
        pose.header.frame_id = "base_link";
        pose.pose.position.x = x;
        pose.pose.position.y = y;
        pose.pose.position.z = z;
        pose.pose.orientation.x = 0.0;
        pose.pose.orientation.y = 0.0;
        pose.pose.orientation.z = 0.0;
        pose.pose.orientation.w = 1.0;
        
        // Convert pose to joint space
        RCLCPP_INFO(node_->get_logger(), "Converting pose to joint space...");
        std::vector<double> joint_values;
        std::vector<std::string> joint_names;
        
        bool ik_success = poseToJointSpace(*arm_, pose, joint_values, &joint_names);
        
        if (!ik_success) {
            RCLCPP_ERROR(node_->get_logger(), "IK solution NOT found! Pose may be unreachable.");
            return;
        }
        
        RCLCPP_INFO(node_->get_logger(), "IK solution found! Joint values:");
        for (size_t i = 0; i < joint_values.size() && i < joint_names.size(); ++i) {
            RCLCPP_INFO(node_->get_logger(), "  %s: %.4f rad (%.2f deg)", 
                       joint_names[i].c_str(), joint_values[i],
                       joint_values[i] * 180.0 / M_PI);
        }
        
        // Move robot directly to joint target (using move() which plans and executes in one call)
        RCLCPP_INFO(node_->get_logger(), "Moving robot to joint target...");
        arm_->setStartStateToCurrentState();
        arm_->setJointValueTarget(joint_values);
        
        // Move directly (plans and executes in one call, no explicit planning step needed)
        moveit::core::MoveItErrorCode result = arm_->move();
        
        if (result == moveit::core::MoveItErrorCode::SUCCESS) {
            RCLCPP_INFO(node_->get_logger(), "Robot movement completed successfully");
        } else {
            RCLCPP_ERROR(node_->get_logger(), "Failed to move robot, error code: %d", result.val);
        }
    }
    
    void homeCommandCallback(const Bool::SharedPtr msg)
    {
        RCLCPP_INFO(node_->get_logger(), "=== Received home command ===");
        RCLCPP_INFO(node_->get_logger(), "Moving robot to Home position...");
        
        // Set start state to current state
        arm_->setStartStateToCurrentState();
        
        // Set named target to "Home"
        arm_->setNamedTarget("Home");
        
        // Move to home (plans and executes in one call)
        moveit::core::MoveItErrorCode result = arm_->move();
        
        if (result == moveit::core::MoveItErrorCode::SUCCESS) {
            RCLCPP_INFO(node_->get_logger(), "Successfully moved to Home position");
            
            // Get current joint values after homing
            try {
                std::vector<double> current_joints = arm_->getCurrentJointValues();
                std::vector<std::string> joint_names = arm_->getJointNames();
                RCLCPP_INFO(node_->get_logger(), "Current joint values at Home:");
                for (size_t i = 0; i < current_joints.size() && i < joint_names.size(); ++i) {
                    RCLCPP_INFO(node_->get_logger(), "  %s: %.4f rad (%.2f deg)", 
                               joint_names[i].c_str(), current_joints[i],
                               current_joints[i] * 180.0 / M_PI);
                }
            } catch (const std::exception& e) {
                RCLCPP_WARN(node_->get_logger(), "Could not get current joint values: %s", e.what());
            }
        } else {
            RCLCPP_ERROR(node_->get_logger(), "Failed to move to Home position, error code: %d", result.val);
        }
    }
    
    std::shared_ptr<rclcpp::Node> node_;
    std::shared_ptr<moveit::planning_interface::MoveGroupInterface> arm_;
    rclcpp::Subscription<FloatArray>::SharedPtr pose_cmd_sub_;
    rclcpp::Subscription<Bool>::SharedPtr home_cmd_sub_;
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    
    auto node = std::make_shared<rclcpp::Node>("pose_to_joint_commander");
    
    RCLCPP_INFO(node->get_logger(), "Starting PoseToJointCommander node...");
    
    PoseToJointCommander commander(node);
    
    RCLCPP_INFO(node->get_logger(), "PoseToJointCommander node ready. Waiting for commands...");
    
    rclcpp::spin(node);
    
    rclcpp::shutdown();
    return 0;
}
