#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/planning_scene/planning_scene.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>
#include <moveit_msgs/msg/planning_scene.hpp>
#include <moveit/robot_model/robot_model.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/collision_detection/collision_common.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("pose_space_demo");
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);
    auto spinner = std::thread([&executor]() {executor.spin();});

    RCLCPP_INFO(node->get_logger(), "Starting Pose Space Demo for g_arm ..."); 
    
    RCLCPP_INFO(node->get_logger(), "Creating move group interface for arm ...");
    auto arm = moveit::planning_interface::MoveGroupInterface(node, "arm");
    arm.setMaxVelocityScalingFactor(1.0);
    arm.setMaxAccelerationScalingFactor(1.0);
    
    // Set planning timeout (in seconds) - increase if planning is taking too long
    // Default is usually 5 seconds, but can be increased for complex planning problems
    double planning_timeout = 10.0;  // seconds
    arm.setPlanningTime(planning_timeout);
    RCLCPP_INFO(node->get_logger(), "Planning timeout set to %.1f seconds", planning_timeout);
    
    // Get and display the current end effector link (automatically set from SRDF)
    std::string end_effector_link = arm.getEndEffectorLink();
    RCLCPP_INFO(node->get_logger(), "Current end effector link: %s", end_effector_link.c_str());
    
    // Optionally, you can explicitly set the end effector link if needed:
    // arm.setEndEffectorLink("end_effector_tip");
    // Note: According to your SRDF, the end effector link should be "end_effector_tip"
    
    // Disable collision detection for all links (but keep validation diagnostics)
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
        RCLCPP_INFO(node->get_logger(), "Current pose - Orientation: x=%.4f, y=%.4f, z=%.4f, w=%.4f",
                    current_pose.pose.orientation.x,
                    current_pose.pose.orientation.y,
                    current_pose.pose.orientation.z,
                    current_pose.pose.orientation.w);
    } catch (const std::exception& e) {
        RCLCPP_WARN(node->get_logger(), "Could not get current pose: %s", e.what());
    }
    
    // Move to Home position first (waypoint 0)
    RCLCPP_INFO(node->get_logger(), "Moving to Repose position (waypoint 0)...");
    arm.setStartStateToCurrentState();
    arm.setNamedTarget("Repose");
    moveit::planning_interface::MoveGroupInterface::Plan home_plan;
    bool home_success = (arm.plan(home_plan) == moveit::core::MoveItErrorCode::SUCCESS);
    if (home_success) {
        moveit::core::MoveItErrorCode execute_result = arm.execute(home_plan);
        if (execute_result == moveit::core::MoveItErrorCode::SUCCESS) {
            RCLCPP_INFO(node->get_logger(), "Successfully moved to Repose position");
        } else {
            RCLCPP_WARN(node->get_logger(), "Failed to execute Home position, error code: %d", execute_result.val);
        }
    } else {
        RCLCPP_WARN(node->get_logger(), "Failed to plan to Home position, proceeding anyway");
    }
    std::this_thread::sleep_for(std::chrono::seconds(1));
    
    // Define 7 waypoints: first and last are Home, middle 5 are custom poses
    // Each waypoint: {x, y, z, roll, pitch, yaw} in meters and radians
    struct Waypoint {
        double x, y, z;
        double roll, pitch, yaw;
        std::string description;
    };
    
    std::vector<Waypoint> waypoints = {
        // Waypoint 0: Home (already moved there)
        {0.22, 0.015, 0.29, 0.0, 0.0, 0.0, "Home"},
        // Waypoint 1
        {0.220, 0.05, 0.1, 0.0, 0.0, 0.0, "Forward"},
        // Waypoint 2
        {0.220, 0.015, 0.1, 0.0, 0.0, 0, "Right rotated"},
        // Waypoint 3
        {0.220, 0.015, 0.1, 0.0, 0.0, 0, "Left rotated"},
        // Waypoint 4
        {0.220, 0.015, 0.15, 0.0, 0.0, 0.0, "Extended forward"},
        // Waypoint 5
        {0.220, 0.015, 0.2, 0.0, 0.0, 0.0, "Upward"},
        // Waypoint 6: Home (return)
        {0.220, 0.015, 0.29, 0.0, 0.0, 0.0, "Home"}
    };
    
    RCLCPP_INFO(node->get_logger(), "Executing %zu pose waypoints...", waypoints.size());
    
    for (size_t i = 0; i < waypoints.size(); ++i) {
        // Skip waypoint 0 since we already moved to Home
        if (i == 0) {
            RCLCPP_INFO(node->get_logger(), "Waypoint %zu (%s): Already at Home position", i, waypoints[i].description.c_str());
            continue;
        }
        
        RCLCPP_INFO(node->get_logger(), "Moving to waypoint %zu (%s):", i, waypoints[i].description.c_str());
        RCLCPP_INFO(node->get_logger(), "  Position: x=%.4f, y=%.4f, z=%.4f", 
                   waypoints[i].x, waypoints[i].y, waypoints[i].z);
        RCLCPP_INFO(node->get_logger(), "  Orientation (RPY): roll=%.4f, pitch=%.4f, yaw=%.4f", 
                   waypoints[i].roll, waypoints[i].pitch, waypoints[i].yaw);
        
        // Convert RPY to quaternion
        tf2::Quaternion q;
        q.setRPY(waypoints[i].roll, waypoints[i].pitch, waypoints[i].yaw);
        q = q.normalize();
        
        // Create pose stamped message
        geometry_msgs::msg::PoseStamped target_pose;
        target_pose.header.frame_id = "base_link";
        target_pose.pose.position.x = waypoints[i].x;
        target_pose.pose.position.y = waypoints[i].y;
        target_pose.pose.position.z = waypoints[i].z;
        target_pose.pose.orientation.x = 0;//q.getX();
        target_pose.pose.orientation.y = 0;//q.getY();
        target_pose.pose.orientation.z = 0;//q.getZ();
        target_pose.pose.orientation.w = 1;//q.getW();
        
        RCLCPP_INFO(node->get_logger(), "  Orientation (quaternion): x=%.4f, y=%.4f, z=%.4f, w=%.4f",
                   target_pose.pose.orientation.x,
                   target_pose.pose.orientation.y,
                   target_pose.pose.orientation.z,
                   target_pose.pose.orientation.w);
        
        // Set start state to current state
        arm.setStartStateToCurrentState();
        
        // Set pose target
        arm.setPoseTarget(target_pose);
        
        // Debug: Validate goal state before planning
        RCLCPP_INFO(node->get_logger(), "=== Validating goal state for waypoint %zu (%s) ===", i, waypoints[i].description.c_str());
        
        // Check if pose is within reasonable workspace bounds
        double distance = std::sqrt(target_pose.pose.position.x * target_pose.pose.position.x +
                                   target_pose.pose.position.y * target_pose.pose.position.y +
                                   target_pose.pose.position.z * target_pose.pose.position.z);
        RCLCPP_INFO(node->get_logger(), "  Goal pose distance from origin: %.4f m", distance);
        
        // Check quaternion validity
        double q_norm = std::sqrt(
            target_pose.pose.orientation.x * target_pose.pose.orientation.x +
            target_pose.pose.orientation.y * target_pose.pose.orientation.y +
            target_pose.pose.orientation.z * target_pose.pose.orientation.z +
            target_pose.pose.orientation.w * target_pose.pose.orientation.w
        );
        if (std::abs(q_norm - 1.0) > 0.01) {
            RCLCPP_ERROR(node->get_logger(), "  ERROR: Quaternion is not normalized! Norm = %.4f (should be ~1.0)", q_norm);
            RCLCPP_ERROR(node->get_logger(), "    This will cause IK to fail!");
        } else {
            RCLCPP_INFO(node->get_logger(), "  Quaternion is valid (norm = %.4f)", q_norm);
        }
        
        // Check if IK can solve for this pose (get joint values for the goal)
        std::vector<double> goal_joint_values;
        arm.getJointValueTarget(goal_joint_values);  // Returns void, fills the vector
        std::vector<std::string> joint_names = arm.getJointNames();
        
        // Check if we got valid joint values (non-empty and same size as joint names)
        bool ik_found = (!goal_joint_values.empty() && 
                         goal_joint_values.size() == joint_names.size());
        
        if (ik_found) {
            RCLCPP_INFO(node->get_logger(), "  ✓ IK solution found for goal pose");
            for (size_t j = 0; j < goal_joint_values.size() && j < joint_names.size(); ++j) {
                RCLCPP_INFO(node->get_logger(), "    %s: %.4f rad (%.2f deg)", 
                           joint_names[j].c_str(), goal_joint_values[j],
                           goal_joint_values[j] * 180.0 / M_PI);
            }
        } else {
            RCLCPP_ERROR(node->get_logger(), "  ✗ IK FAILED: Could not solve for goal pose!");
            RCLCPP_ERROR(node->get_logger(), "    Possible reasons:");
            RCLCPP_ERROR(node->get_logger(), "      - Goal pose is outside robot workspace");
            RCLCPP_ERROR(node->get_logger(), "      - Goal pose is unreachable with current joint limits");
            RCLCPP_ERROR(node->get_logger(), "      - Invalid quaternion orientation");
            RCLCPP_ERROR(node->get_logger(), "    Goal joint values size: %zu, Expected: %zu", 
                       goal_joint_values.size(), joint_names.size());
        }
        
        // Get current joint values for comparison
        std::vector<double> current_joint_values = arm.getCurrentJointValues();
        RCLCPP_INFO(node->get_logger(), "  Current joint values:");
        for (size_t j = 0; j < current_joint_values.size() && j < joint_names.size(); ++j) {
            RCLCPP_INFO(node->get_logger(), "    %s: %.4f rad (%.2f deg)", 
                       joint_names[j].c_str(), current_joint_values[j],
                       current_joint_values[j] * 180.0 / M_PI);
        }
        
        // Validate goal state: Check joint limits and workspace bounds
        if (ik_found) {
            RCLCPP_INFO(node->get_logger(), "  Validating goal state (joint limits, workspace bounds)...");
            try {
                const moveit::core::RobotModelConstPtr& robot_model = arm.getRobotModel();
                if (robot_model) {
                    // Check if goal joint values are within limits
                    const moveit::core::JointModelGroup* joint_model_group = 
                        robot_model->getJointModelGroup("arm");
                    
                    if (joint_model_group) {
                        bool within_limits = true;
                        std::vector<std::string> violating_joints;
                        
                        for (size_t j = 0; j < goal_joint_values.size() && j < joint_names.size(); ++j) {
                            const moveit::core::JointModel* joint_model = 
                                joint_model_group->getJointModel(joint_names[j]);
                            
                            if (joint_model && joint_model->getVariableCount() > 0) {
                                double min_bound = joint_model->getVariableBounds()[0].min_position_;
                                double max_bound = joint_model->getVariableBounds()[0].max_position_;
                                double joint_value = goal_joint_values[j];
                                
                                if (joint_value < min_bound || joint_value > max_bound) {
                                    within_limits = false;
                                    violating_joints.push_back(joint_names[j]);
                                    RCLCPP_WARN(node->get_logger(), "    Joint %s: %.4f rad is OUT OF LIMITS [%.4f, %.4f]",
                                               joint_names[j].c_str(), joint_value, min_bound, max_bound);
                                }
                            }
                        }
                        
                        if (within_limits) {
                            RCLCPP_INFO(node->get_logger(), "  All goal joint values are within limits");
                        } else {
                            RCLCPP_WARN(node->get_logger(), "  Goal state violates joint limits for %zu joint(s)", 
                                       violating_joints.size());
                        }
                    }
                }
            } catch (const std::exception& e) {
                RCLCPP_WARN(node->get_logger(), "  Could not validate goal state: %s", e.what());
            }
        }
        
        // Plan
        moveit::planning_interface::MoveGroupInterface::Plan plan;
        moveit::core::MoveItErrorCode plan_result = arm.plan(plan);
        bool success = (plan_result == moveit::core::MoveItErrorCode::SUCCESS);
        
        if (success) {
            RCLCPP_INFO(node->get_logger(), "Planning successful for waypoint %zu", i);
            RCLCPP_INFO(node->get_logger(), "Trajectory has %zu points", 
                       plan.trajectory.joint_trajectory.points.size());
            
            // Execute
            moveit::core::MoveItErrorCode execute_result = arm.execute(plan);
            if (execute_result == moveit::core::MoveItErrorCode::SUCCESS) {
                RCLCPP_INFO(node->get_logger(), "Execution successful for waypoint %zu", i);
                
                // Get the actual pose after execution
                try {
                    geometry_msgs::msg::PoseStamped actual_pose = arm.getCurrentPose();
                    RCLCPP_INFO(node->get_logger(), "Actual pose after waypoint %zu:", i);
                    RCLCPP_INFO(node->get_logger(), "  Position: x=%.4f, y=%.4f, z=%.4f", 
                               actual_pose.pose.position.x,
                               actual_pose.pose.position.y,
                               actual_pose.pose.position.z);
                    
                    // Convert quaternion to RPY
                    tf2::Quaternion q_actual(
                        actual_pose.pose.orientation.x,
                        actual_pose.pose.orientation.y,
                        actual_pose.pose.orientation.z,
                        actual_pose.pose.orientation.w
                    );
                    tf2::Matrix3x3 m_actual(q_actual);
                    double roll_actual, pitch_actual, yaw_actual;
                    m_actual.getRPY(roll_actual, pitch_actual, yaw_actual);
                    RCLCPP_INFO(node->get_logger(), "  Orientation (RPY): roll=%.4f rad (%.2f deg), pitch=%.4f rad (%.2f deg), yaw=%.4f rad (%.2f deg)",
                               roll_actual, roll_actual * 180.0 / M_PI,
                               pitch_actual, pitch_actual * 180.0 / M_PI,
                               yaw_actual, yaw_actual * 180.0 / M_PI);
                } catch (const std::exception& e) {
                    RCLCPP_WARN(node->get_logger(), "Could not get actual pose for waypoint %zu: %s", i, e.what());
                }
            } else {
                RCLCPP_ERROR(node->get_logger(), "Execution failed for waypoint %zu with error code: %d", 
                           i, execute_result.val);
            }
        } else {
            RCLCPP_ERROR(node->get_logger(), "Planning failed for waypoint %zu", i);
            RCLCPP_ERROR(node->get_logger(), "  Error code: %d", plan_result.val);
            
            // Provide detailed error information
            switch (plan_result.val) {
                case moveit::core::MoveItErrorCode::INVALID_MOTION_PLAN:
                    RCLCPP_ERROR(node->get_logger(), "  Reason: INVALID_MOTION_PLAN - Goal state may be invalid or unreachable");
                    break;
                case moveit::core::MoveItErrorCode::PLANNING_FAILED:
                    RCLCPP_ERROR(node->get_logger(), "  Reason: PLANNING_FAILED - Planner could not find a solution");
                    break;
                case moveit::core::MoveItErrorCode::INVALID_GROUP_NAME:
                    RCLCPP_ERROR(node->get_logger(), "  Reason: INVALID_GROUP_NAME - Planning group name is invalid");
                    break;
                case moveit::core::MoveItErrorCode::INVALID_ROBOT_STATE:
                    RCLCPP_ERROR(node->get_logger(), "  Reason: INVALID_ROBOT_STATE - Robot state is invalid");
                    break;
                case moveit::core::MoveItErrorCode::NO_IK_SOLUTION:
                    RCLCPP_ERROR(node->get_logger(), "  Reason: NO_IK_SOLUTION - No IK solution found for goal pose");
                    break;
                case moveit::core::MoveItErrorCode::TIMED_OUT:
                    RCLCPP_ERROR(node->get_logger(), "  Reason: TIMED_OUT - Planning timeout exceeded (try increasing planning time)");
                    break;
                default:
                    RCLCPP_ERROR(node->get_logger(), "  Reason: Unknown error code");
                    break;
            }
            
            // Additional diagnostics
            RCLCPP_ERROR(node->get_logger(), "  Goal pose was:");
            RCLCPP_ERROR(node->get_logger(), "    Position: x=%.4f, y=%.4f, z=%.4f", 
                        target_pose.pose.position.x, target_pose.pose.position.y, target_pose.pose.position.z);
            RCLCPP_ERROR(node->get_logger(), "    Orientation: x=%.4f, y=%.4f, z=%.4f, w=%.4f",
                        target_pose.pose.orientation.x, target_pose.pose.orientation.y,
                        target_pose.pose.orientation.z, target_pose.pose.orientation.w);
            RCLCPP_ERROR(node->get_logger(), "    Frame: %s", target_pose.header.frame_id.c_str());
            
            // Check if quaternion is valid (should have norm ~1.0)
            double q_norm = std::sqrt(
                target_pose.pose.orientation.x * target_pose.pose.orientation.x +
                target_pose.pose.orientation.y * target_pose.pose.orientation.y +
                target_pose.pose.orientation.z * target_pose.pose.orientation.z +
                target_pose.pose.orientation.w * target_pose.pose.orientation.w
            );
            if (std::abs(q_norm - 1.0) > 0.1) {
                RCLCPP_ERROR(node->get_logger(), "  WARNING: Quaternion is not normalized! Norm = %.4f (should be ~1.0)", q_norm);
            }
        }
        
        // Wait a bit between waypoints
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    
    // Get final pose
    RCLCPP_INFO(node->get_logger(), "Final end effector pose:");
    try {
        geometry_msgs::msg::PoseStamped final_pose = arm.getCurrentPose();
        RCLCPP_INFO(node->get_logger(), "  Position: x=%.4f, y=%.4f, z=%.4f", 
                   final_pose.pose.position.x, 
                   final_pose.pose.position.y, 
                   final_pose.pose.position.z);
        
        tf2::Quaternion q_final(
            final_pose.pose.orientation.x,
            final_pose.pose.orientation.y,
            final_pose.pose.orientation.z,
            final_pose.pose.orientation.w
        );
        tf2::Matrix3x3 m_final(q_final);
        double roll_final, pitch_final, yaw_final;
        m_final.getRPY(roll_final, pitch_final, yaw_final);
        RCLCPP_INFO(node->get_logger(), "  Orientation (RPY): roll=%.4f rad (%.2f deg), pitch=%.4f rad (%.2f deg), yaw=%.4f rad (%.2f deg)",
                   roll_final, roll_final * 180.0 / M_PI,
                   pitch_final, pitch_final * 180.0 / M_PI,
                   yaw_final, yaw_final * 180.0 / M_PI);
    } catch (const std::exception& e) {
        RCLCPP_WARN(node->get_logger(), "Could not get final pose: %s", e.what());
    }
    
    RCLCPP_INFO(node->get_logger(), "Pose Space Demo completed!");
    
    rclcpp::shutdown();
    spinner.join();
    return 0;
}
