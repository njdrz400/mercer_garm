#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/planning_scene/planning_scene.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>
#include <moveit_msgs/msg/planning_scene.hpp>
#include <moveit/robot_model/robot_model.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <chrono>
#include <thread>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

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
    // Set the pose target
    arm.setPoseTarget(pose);
    
    // Get the joint values for this pose (IK solution)
    arm.getJointValueTarget(joint_values);
    
    // Get joint names if requested
    if (joint_names != nullptr) {
        *joint_names = arm.getJointNames();
    }
    
    // Check if we got a valid IK solution
    // Valid solution means non-empty vector with correct size
    std::vector<std::string> expected_joint_names = arm.getJointNames();
    bool ik_success = (!joint_values.empty() && 
                       joint_values.size() == expected_joint_names.size());
    
    return ik_success;
}

/**
 * Convert pose space (position and RPY orientation) to joint space
 * 
 * @param arm MoveGroupInterface for the robot arm
 * @param x, y, z Position coordinates in meters
 * @param roll, pitch, yaw Orientation in radians
 * @param frame_id Frame ID for the pose (default: "base_link")
 * @param joint_values Output vector to store the computed joint values
 * @param joint_names Output vector to store the joint names (optional, can be nullptr)
 * @param pose_out Output pose that was used for IK (optional, can be nullptr)
 * @return true if IK solution was found, false otherwise
 */
bool poseToJointSpace(
    moveit::planning_interface::MoveGroupInterface& arm,
    double x, double y, double z,
    double roll, double pitch, double yaw,
    std::vector<double>& joint_values,
    std::vector<std::string>* joint_names = nullptr,
    geometry_msgs::msg::PoseStamped* pose_out = nullptr,
    const std::string& frame_id = "base_link")
{
    // Convert RPY to quaternion
    tf2::Quaternion q;
    q.setRPY(roll, pitch, yaw);
    q = q.normalize();
    
    // Create pose stamped message
    geometry_msgs::msg::PoseStamped pose;
    pose.header.frame_id = frame_id;
    pose.pose.position.x = x;
    pose.pose.position.y = y;
    pose.pose.position.z = z;
    pose.pose.orientation.x = q.getX();
    pose.pose.orientation.y = q.getY();
    pose.pose.orientation.z = q.getZ();
    pose.pose.orientation.w = q.getW();
    
    // Return the pose if requested
    if (pose_out != nullptr) {
        *pose_out = pose;
    }
    
    // Call the main poseToJointSpace function
    return poseToJointSpace(arm, pose, joint_values, joint_names);
}

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("simple_pose_demo");
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);
    auto spinner = std::thread([&executor]() {executor.spin();});

    RCLCPP_INFO(node->get_logger(), "Starting Simple Pose Space Demo for g_arm ..."); 
    
    RCLCPP_INFO(node->get_logger(), "Creating move group interface for arm ...");
    auto arm = moveit::planning_interface::MoveGroupInterface(node, "arm");
    arm.setMaxVelocityScalingFactor(1.0);
    arm.setMaxAccelerationScalingFactor(1.0);
    
    // Set planning timeout
    double planning_timeout = 10.0;
    arm.setPlanningTime(planning_timeout);
    RCLCPP_INFO(node->get_logger(), "Planning timeout set to %.1f seconds", planning_timeout);
    
    // Get end effector link
    std::string end_effector_link = arm.getEndEffectorLink();
    RCLCPP_INFO(node->get_logger(), "End effector link: %s", end_effector_link.c_str());
    
    // Disable collision detection for all links
    RCLCPP_INFO(node->get_logger(), "Disabling collision detection for all links...");
    try {
        const moveit::core::RobotModelConstPtr& robot_model = arm.getRobotModel();
        if (!robot_model) {
            RCLCPP_WARN(node->get_logger(), "Could not get robot model");
        } else {
            std::vector<std::string> link_names = robot_model->getLinkModelNames();
            RCLCPP_INFO(node->get_logger(), "Found %zu links in robot model", link_names.size());
            
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
            
            RCLCPP_INFO(node->get_logger(), "ACM modified: collision detection disabled for all %zu links", link_names.size());
        }
    } catch (const std::exception& e) {
        RCLCPP_ERROR(node->get_logger(), "Could not modify ACM: %s", e.what());
        RCLCPP_WARN(node->get_logger(), "Proceeding without ACM modification");
    }
    
    // Get current pose
    RCLCPP_INFO(node->get_logger(), "Getting current end effector pose...");
    try {
        geometry_msgs::msg::PoseStamped current_pose = arm.getCurrentPose();
        RCLCPP_INFO(node->get_logger(), "Current pose - Position: x=%.4f, y=%.4f, z=%.4f", 
                    current_pose.pose.position.x, 
                    current_pose.pose.position.y, 
                    current_pose.pose.position.z);
    } catch (const std::exception& e) {
        RCLCPP_WARN(node->get_logger(), "Could not get current pose: %s", e.what());
    }
    
    // Move to Home position first
    RCLCPP_INFO(node->get_logger(), "Moving to Home position...");
    arm.setStartStateToCurrentState();
    arm.setNamedTarget("Home");
    moveit::planning_interface::MoveGroupInterface::Plan home_plan;
    bool home_success = (arm.plan(home_plan) == moveit::core::MoveItErrorCode::SUCCESS);
    if (home_success) {
        moveit::core::MoveItErrorCode execute_result = arm.execute(home_plan);
        if (execute_result == moveit::core::MoveItErrorCode::SUCCESS) {
            RCLCPP_INFO(node->get_logger(), "Successfully moved to Home position");
        } else {
            RCLCPP_WARN(node->get_logger(), "Failed to execute Home position, error code: %d", execute_result.val);
        }
    } else {
        RCLCPP_WARN(node->get_logger(), "Failed to plan to Home position, proceeding anyway");
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Define target pose (adjust these values for your robot)
    double target_x = 0.20;
    double target_y = 0.0;
    double target_z = 0.25;
    double target_roll = 0.0;
    double target_pitch = 0.0;
    double target_yaw = 0.0;
    
    RCLCPP_INFO(node->get_logger(), "Target pose: x=%.4f, y=%.4f, z=%.4f, roll=%.4f, pitch=%.4f, yaw=%.4f", 
                target_x, target_y, target_z, target_roll, target_pitch, target_yaw);
    
    // Convert pose space to joint space using the function
    RCLCPP_INFO(node->get_logger(), "Converting pose to joint space...");
    std::vector<double> target_joint_values;
    std::vector<std::string> joint_names;
    geometry_msgs::msg::PoseStamped target_pose;
    
    bool ik_success = poseToJointSpace(arm, target_x, target_y, target_z,
                                       target_roll, target_pitch, target_yaw,
                                       target_joint_values, &joint_names, &target_pose);
    
    if (ik_success) {
        RCLCPP_INFO(node->get_logger(), "IK solution found! Joint values:");
        for (size_t i = 0; i < target_joint_values.size() && i < joint_names.size(); ++i) {
            RCLCPP_INFO(node->get_logger(), "  %s: %.4f rad (%.2f deg)", 
                       joint_names[i].c_str(), target_joint_values[i],
                       target_joint_values[i] * 180.0 / M_PI);
        }
        RCLCPP_INFO(node->get_logger(), "Pose orientation (quaternion): x=%.4f, y=%.4f, z=%.4f, w=%.4f",
                    target_pose.pose.orientation.x,
                    target_pose.pose.orientation.y,
                    target_pose.pose.orientation.z,
                    target_pose.pose.orientation.w);
    } else {
        RCLCPP_ERROR(node->get_logger(), "IK solution NOT found!");
        RCLCPP_ERROR(node->get_logger(), "  Pose may be outside workspace or unreachable");
        RCLCPP_ERROR(node->get_logger(), "  Joint values size: %zu, Expected: %zu", 
                    target_joint_values.size(), joint_names.size());
    }
    
    // Set start state to current state
    arm.setStartStateToCurrentState();
    
    // Set pose target
    arm.setPoseTarget(target_pose);
    
    // Plan
    moveit::planning_interface::MoveGroupInterface::Plan plan;
    moveit::core::MoveItErrorCode plan_result = arm.plan(plan);
    bool success = (plan_result == moveit::core::MoveItErrorCode::SUCCESS);
    
    if (success) {
        RCLCPP_INFO(node->get_logger(), "Planning successful for target pose");
        RCLCPP_INFO(node->get_logger(), "Trajectory has %zu points", 
                   plan.trajectory.joint_trajectory.points.size());
        
        // Execute
        moveit::core::MoveItErrorCode execute_result = arm.execute(plan);
        if (execute_result == moveit::core::MoveItErrorCode::SUCCESS) {
            RCLCPP_INFO(node->get_logger(), "Execution successful - reached target pose");
            
            // Get the actual pose after execution
            try {
                geometry_msgs::msg::PoseStamped actual_pose = arm.getCurrentPose();
                RCLCPP_INFO(node->get_logger(), "Actual pose after execution:");
                RCLCPP_INFO(node->get_logger(), "  Position: x=%.4f, y=%.4f, z=%.4f", 
                           actual_pose.pose.position.x,
                           actual_pose.pose.position.y,
                           actual_pose.pose.position.z);
            } catch (const std::exception& e) {
                RCLCPP_WARN(node->get_logger(), "Could not get actual pose: %s", e.what());
            }
        } else {
            RCLCPP_ERROR(node->get_logger(), "Execution failed with error code: %d", execute_result.val);
        }
    } else {
        RCLCPP_ERROR(node->get_logger(), "Planning failed with error code: %d", plan_result.val);
        RCLCPP_ERROR(node->get_logger(), "Target pose may be unreachable or invalid");
    }
    
    std::this_thread::sleep_for(std::chrono::seconds(2));
    
    // Move back to Home
    RCLCPP_INFO(node->get_logger(), "Moving back to Home position...");
    arm.setStartStateToCurrentState();
    arm.setNamedTarget("Home");
    moveit::planning_interface::MoveGroupInterface::Plan return_plan;
    bool return_success = (arm.plan(return_plan) == moveit::core::MoveItErrorCode::SUCCESS);
    if (return_success) {
        moveit::core::MoveItErrorCode execute_result = arm.execute(return_plan);
        if (execute_result == moveit::core::MoveItErrorCode::SUCCESS) {
            RCLCPP_INFO(node->get_logger(), "Successfully returned to Home position");
        } else {
            RCLCPP_WARN(node->get_logger(), "Failed to execute return to Home, error code: %d", execute_result.val);
        }
    } else {
        RCLCPP_WARN(node->get_logger(), "Failed to plan return to Home position");
    }
    
    RCLCPP_INFO(node->get_logger(), "Simple Pose Space Demo completed!");
    
    rclcpp::shutdown();
    spinner.join();
    return 0;
}
