#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <moveit/planning_scene/planning_scene.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>
#include <moveit_msgs/msg/planning_scene.hpp>
#include <moveit/robot_model/robot_model.h>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <chrono>
#include <thread>
#include <vector>
#include <string>

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<rclcpp::Node>("test_moveit_commander");
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);
    auto spinner = std::thread([&executor]() {executor.spin();});


    RCLCPP_INFO(node->get_logger(), "Starting MoveIt node called test_moveit ..."); 
    
    RCLCPP_INFO(node->get_logger(), "Creating move group interface for arm ...");
    RCLCPP_DEBUG(node->get_logger(), "About to construct MoveGroupInterface...");
    auto arm = moveit::planning_interface::MoveGroupInterface(node, "arm");
    RCLCPP_DEBUG(node->get_logger(), "MoveGroupInterface constructed successfully");
    RCLCPP_DEBUG(node->get_logger(), "Setting velocity and acceleration scaling factors...");
    arm.setMaxVelocityScalingFactor(1.0);
    arm.setMaxAccelerationScalingFactor(1.0);
    RCLCPP_DEBUG(node->get_logger(), "Velocity and acceleration scaling factors set");
    
    // Modify the Allowed Collision Matrix (ACM) to disable collision detection for all links
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
    
    // Set the goal target first

    
    // Get the current end effector pose
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
        RCLCPP_INFO(node->get_logger(), "Current pose frame: %s", current_pose.header.frame_id.c_str());
    } catch (const std::exception& e) {
        RCLCPP_WARN(node->get_logger(), "Could not get current pose: %s", e.what());
    }
    
    // Try to set start state to current state
    // Note: This may block if joint states aren't available or if MoveIt can't get current state
    RCLCPP_INFO(node->get_logger(), "Setting start state to current state...");
    try {
        arm.setStartStateToCurrentState();
        RCLCPP_INFO(node->get_logger(), "Start state set successfully");
    } catch (const std::exception& e) {
        RCLCPP_WARN(node->get_logger(), "Could not set start state to current: %s", e.what());
        RCLCPP_WARN(node->get_logger(), "Proceeding with default start state");
    }
   
    RCLCPP_INFO(node->get_logger(), "Setting goal to 'Repose'...");
    arm.setNamedTarget("Repose");


    // Get the current end effector pose
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
        RCLCPP_INFO(node->get_logger(), "Current pose frame: %s", current_pose.header.frame_id.c_str());
    } catch (const std::exception& e) {
        RCLCPP_WARN(node->get_logger(), "Could not get current pose: %s", e.what());
    }



    moveit::planning_interface::MoveGroupInterface::Plan plan1;
    bool success = (arm.plan(plan1) == moveit::core::MoveItErrorCode::SUCCESS);
    if (success) {
        RCLCPP_INFO(node->get_logger(), "Planning successful");
        arm.execute(plan1);
    } else {
        RCLCPP_ERROR(node->get_logger(), "Planning failed");
    }


// create next goal using pose goal function        
    RCLCPP_INFO(node->get_logger(), "Setting goal to 'Pose Goal'...");
    
    tf2::Quaternion q;
    q.setRPY(3.14, 0.0, 0.0);
    q=q.normalize();

    geometry_msgs::msg::PoseStamped target_goal;
    target_goal.header.frame_id = "base_link";
    target_goal.pose.position.x = 0.0;
    target_goal.pose.position.y = 0.0;
    target_goal.pose.position.z = 0.0;
    target_goal.pose.orientation.x = 1.0;
    target_goal.pose.orientation.y = 0;
    target_goal.pose.orientation.z = 0;      
    target_goal.pose.orientation.w = 0;

    arm.setStartStateToCurrentState();
    arm.setPoseTarget(target_goal);

    moveit::planning_interface::MoveGroupInterface::Plan plan2;
    bool success2 = (arm.plan(plan2) == moveit::core::MoveItErrorCode::SUCCESS);
    if (success2) {
        RCLCPP_INFO(node->get_logger(), "Planning successful");
        arm.execute(plan2);
    } else {
        RCLCPP_ERROR(node->get_logger(), "Planning failed");
    }


    // goto home position
    RCLCPP_INFO(node->get_logger(), "Setting goal to 'Home'...");
    arm.setStartStateToCurrentState();
    arm.setNamedTarget("Home");
    moveit::planning_interface::MoveGroupInterface::Plan plan3;
    bool success3 = (arm.plan(plan3) == moveit::core::MoveItErrorCode::SUCCESS);
    if (success3) {
        RCLCPP_INFO(node->get_logger(), "Planning successful");
        arm.execute(plan3);
    } else {
// shutdown the node
        RCLCPP_ERROR(node->get_logger(), "Planning failed");
    }

    RCLCPP_INFO(node->get_logger(), "Shutting down MoveIt node called test_moveit ...");
    rclcpp::shutdown();
    spinner.join();
    
    return 0;
}

 