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
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("joint_space_demo");
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);
    auto spinner = std::thread([&executor]() {executor.spin();});

    RCLCPP_INFO(node->get_logger(), "Starting Joint Space Demo for g_arm ..."); 
    
    RCLCPP_INFO(node->get_logger(), "Creating move group interface for arm ...");
    auto arm = moveit::planning_interface::MoveGroupInterface(node, "arm");
    arm.setMaxVelocityScalingFactor(1.0);
    arm.setMaxAccelerationScalingFactor(1.0);
    
    // Disable collision detection for all links
    RCLCPP_INFO(node->get_logger(), "Disabling collision detection for all links...");
    try {
        // Get the robot model to retrieve all link names
        const moveit::core::RobotModelConstPtr& robot_model = arm.getRobotModel();
        if (!robot_model) {
            RCLCPP_WARN(node->get_logger(), "Could not get robot model");
        } else {
            // Get all link names from the robot model
            std::vector<std::string> link_names = robot_model->getLinkModelNames();
            RCLCPP_INFO(node->get_logger(), "Found %zu links in robot model", link_names.size());
            
            // Get the current planning scene from the move group
            moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
            
            // Create a planning scene message to modify the ACM
            moveit_msgs::msg::PlanningScene planning_scene_msg;
            planning_scene_msg.is_diff = true;
            planning_scene_msg.robot_state.is_diff = true;
            
            // Create ACM message and set all collisions to allowed (true)
            // This effectively disables collision detection
            moveit_msgs::msg::AllowedCollisionMatrix acm_msg;
            
            // Add all link names to the ACM
            for (const auto& link_name : link_names) {
                acm_msg.entry_names.push_back(link_name);
            }
            
            // Create entry values - for each link, allow collisions with all other links
            // entry_values[i] corresponds to row i, and entry_values[i].enabled[j] is the value for column j
            for (size_t i = 0; i < link_names.size(); ++i) {
                moveit_msgs::msg::AllowedCollisionEntry entry;
                // Set all entries to true (allow all collisions)
                for (size_t j = 0; j < link_names.size(); ++j) {
                    entry.enabled.push_back(true);
                }
                acm_msg.entry_values.push_back(entry);
            }
            
            planning_scene_msg.allowed_collision_matrix = acm_msg;
            
            // Apply the modified planning scene
            planning_scene_interface.applyPlanningScene(planning_scene_msg);
            
            RCLCPP_INFO(node->get_logger(), "ACM modified: collision detection disabled for all %zu links", link_names.size());
        }
    } catch (const std::exception& e) {
        RCLCPP_WARN(node->get_logger(), "Could not modify ACM: %s", e.what());
        RCLCPP_WARN(node->get_logger(), "Proceeding without ACM modification");
    }
    
    // Get joint names
    std::vector<std::string> joint_names = arm.getJointNames();
    RCLCPP_INFO(node->get_logger(), "Planning group has %zu joints:", joint_names.size());
    for (const auto& name : joint_names) {
        RCLCPP_INFO(node->get_logger(), "  - %s", name.c_str());
    }
    
    // Get current joint values
    std::vector<double> current_joints = arm.getCurrentJointValues();
    RCLCPP_INFO(node->get_logger(), "Current joint values:");
    for (size_t i = 0; i < joint_names.size() && i < current_joints.size(); ++i) {
        RCLCPP_INFO(node->get_logger(), "  %s: %.4f rad (%.2f deg)", 
                    joint_names[i].c_str(), current_joints[i], 
                    current_joints[i] * 180.0 / M_PI);
    }
    
    // Move to Home position using named target before starting waypoints
    RCLCPP_INFO(node->get_logger(), "Moving to Home position using named pose command...");
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
    
    // Wait a bit after moving to home
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    RCLCPP_INFO(node->get_logger(), "Moving to Repose  position using named pose command...");
    arm.setStartStateToCurrentState();
    arm.setNamedTarget("Repose");

    home_success = (arm.plan(home_plan) == moveit::core::MoveItErrorCode::SUCCESS);
    if (home_success) {
        moveit::core::MoveItErrorCode execute_result = arm.execute(home_plan);
        if (execute_result == moveit::core::MoveItErrorCode::SUCCESS) {
            RCLCPP_INFO(node->get_logger(), "Successfully moved to Repose position");
        } else {
            RCLCPP_WARN(node->get_logger(), "Failed to execute Repose position, error code: %d", execute_result.val);
        }
    } else {
        RCLCPP_WARN(node->get_logger(), "Failed to plan to Repose position, proceeding anyway");
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    // Define a sequence of joint space waypoints by joint name
    // Each waypoint is a map of joint name to joint value (in radians)
    std::vector<std::map<std::string, double>> waypoints = {
        // Home position
        {{"joint1", 0.25}, {"joint2", 0.25}, {"joint3", 0.0}},
        // Position 1
        {{"joint1", 0.1}, {"joint2", 0.3}, {"joint3", -1.0}},
        // Position 2
        {{"joint1", -0.}, {"joint2", 0.1}, {"joint3", 1}},
        // Position 3
        {{"joint1", 0.0}, {"joint2", 0.2}, {"joint3", -0.7}},
        // Return to home
        {{"joint1", 0.0}, {"joint2", 0.0}, {"joint3", 0.0}}
    };
    
    RCLCPP_INFO(node->get_logger(), "Executing %zu joint space waypoints...", waypoints.size());
    
    for (size_t i = 0; i < waypoints.size(); ++i) {
        RCLCPP_INFO(node->get_logger(), "Moving to waypoint %zu:", i + 1);
        
        // Convert map to vector in the correct order
        std::vector<double> joint_values;
        for (const auto& joint_name : joint_names) {
            auto it = waypoints[i].find(joint_name);
            if (it != waypoints[i].end()) {
                joint_values.push_back(it->second);
                RCLCPP_INFO(node->get_logger(), "  %s: %.4f rad (%.2f deg)", 
                           joint_name.c_str(), it->second,
                           it->second * 180.0 / M_PI);
            } else {
                RCLCPP_WARN(node->get_logger(), "  %s: not specified in waypoint, using current value", 
                           joint_name.c_str());
                // Use current value if not specified
                std::vector<double> current = arm.getCurrentJointValues();
                size_t idx = std::distance(joint_names.begin(), 
                                          std::find(joint_names.begin(), joint_names.end(), joint_name));
                if (idx < current.size()) {
                    joint_values.push_back(current[idx]);
                } else {
                    joint_values.push_back(0.0);
                }
            }
        }
        
        if (joint_values.size() != joint_names.size()) {
            RCLCPP_ERROR(node->get_logger(), "Failed to create joint values vector. Skipping waypoint %zu.", i + 1);
            continue;
        }
        
        // Set start state to current state
        arm.setStartStateToCurrentState();
        
        // Set joint target using the vector
        arm.setJointValueTarget(joint_values);
        
        // Plan
        moveit::planning_interface::MoveGroupInterface::Plan plan;
        bool success = (arm.plan(plan) == moveit::core::MoveItErrorCode::SUCCESS);
        
        if (success) {
            RCLCPP_INFO(node->get_logger(), "Planning successful for waypoint %zu", i + 1);
            RCLCPP_INFO(node->get_logger(), "Trajectory has %zu points", 
                       plan.trajectory.joint_trajectory.points.size());
            
            // Execute
            moveit::core::MoveItErrorCode execute_result = arm.execute(plan);
            if (execute_result == moveit::core::MoveItErrorCode::SUCCESS) {
                RCLCPP_INFO(node->get_logger(), "Execution successful for waypoint %zu", i + 1);
                
                // Get the end effector pose after execution
                try {
                    geometry_msgs::msg::PoseStamped waypoint_pose = arm.getCurrentPose();
                    RCLCPP_INFO(node->get_logger(), "Waypoint %zu end effector pose:", i + 1);
                    RCLCPP_INFO(node->get_logger(), "  Position: x=%.4f, y=%.4f, z=%.4f", 
                               waypoint_pose.pose.position.x,
                               waypoint_pose.pose.position.y,
                               waypoint_pose.pose.position.z);
                    RCLCPP_INFO(node->get_logger(), "  Orientation (quaternion): x=%.4f, y=%.4f, z=%.4f, w=%.4f",
                               waypoint_pose.pose.orientation.x,
                               waypoint_pose.pose.orientation.y,
                               waypoint_pose.pose.orientation.z,
                               waypoint_pose.pose.orientation.w);
                    
                    // Convert quaternion to roll, pitch, yaw
                    tf2::Quaternion q(
                        waypoint_pose.pose.orientation.x,
                        waypoint_pose.pose.orientation.y,
                        waypoint_pose.pose.orientation.z,
                        waypoint_pose.pose.orientation.w
                    );
                    tf2::Matrix3x3 m(q);
                    double roll, pitch, yaw;
                    m.getRPY(roll, pitch, yaw);
                    RCLCPP_INFO(node->get_logger(), "  Orientation (RPY): roll=%.4f rad (%.2f deg), pitch=%.4f rad (%.2f deg), yaw=%.4f rad (%.2f deg)",
                               roll, roll * 180.0 / M_PI,
                               pitch, pitch * 180.0 / M_PI,
                               yaw, yaw * 180.0 / M_PI);
                    RCLCPP_INFO(node->get_logger(), "  Frame: %s", waypoint_pose.header.frame_id.c_str());
                } catch (const std::exception& e) {
                    RCLCPP_WARN(node->get_logger(), "Could not get pose for waypoint %zu: %s", i + 1, e.what());
                }
            } else {
                RCLCPP_ERROR(node->get_logger(), "Execution failed for waypoint %zu with error code: %d", 
                           i + 1, execute_result.val);
            }
        } else {
            RCLCPP_ERROR(node->get_logger(), "Planning failed for waypoint %zu", i + 1);
        }
        
        // Wait a bit between waypoints
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    // Get final joint values
    std::vector<double> final_joints = arm.getCurrentJointValues();
    RCLCPP_INFO(node->get_logger(), "Final joint values:");
    for (size_t i = 0; i < joint_names.size() && i < final_joints.size(); ++i) {
        RCLCPP_INFO(node->get_logger(), "  %s: %.4f rad (%.2f deg)", 
                    joint_names[i].c_str(), final_joints[i], 
                    final_joints[i] * 180.0 / M_PI);
    }
    
    RCLCPP_INFO(node->get_logger(), "Joint Space Demo completed!");
    
    rclcpp::shutdown();
    spinner.join();
    return 0;
}
