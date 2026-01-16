#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <example_interfaces/msg/bool.hpp>
#include <example_interfaces/msg/float64_multi_array.hpp>
#include <std_msgs/msg/string.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <moveit_msgs/msg/planning_scene.hpp>
#include <moveit/robot_model/robot_model.h>
#include <moveit/planning_scene/planning_scene.hpp>
#include <moveit/planning_scene_interface/planning_scene_interface.hpp>

using MoveGroupInterface = moveit::planning_interface::MoveGroupInterface;
using Bool = example_interfaces::msg::Bool;
using FloatArray = example_interfaces::msg::Float64MultiArray;
using PoseStamped = geometry_msgs::msg::PoseStamped;
using String = std_msgs::msg::String;

using namespace std::placeholders;

class Commander
{
public:
    Commander(std::shared_ptr<rclcpp::Node> node){
        node_ = node;
        arm_ = std::make_shared<MoveGroupInterface>(node_, "arm");
        arm_->setMaxVelocityScalingFactor(1.0);
        arm_->setMaxAccelerationScalingFactor(1.0);
        gripper_ = std::make_shared<MoveGroupInterface>(node_, "tool");

        open_gripper_sub_ = node_->create_subscription<Bool>(
            "electromagnet", 10, std::bind(&Commander::openGripperCallback, this, _1));

        joint_cmd_sub_ = node_->create_subscription<FloatArray>(
            "commander_joint_command", 10, std::bind(&Commander::jointCmdCallback, this, _1));

        pose_cmd_sub_ = node_->create_subscription<FloatArray>(
            "commander_pose_command", 10, std::bind(&Commander::poseCmdCallback, this, _1));
        
        named_pose_cmd_sub_ = node_->create_subscription<String>(
            "commander_named_pose_command", 10, std::bind(&Commander::namedPoseCmdCallback, this, _1));
    }

    void goToNamedTarget(const std::string &name){
        arm_->setStartStateToCurrentState();
        arm_->setNamedTarget(name);
        planAndExecute(arm_);
    }

    void goToJointTarget(const std::vector<double> &joints){
        // Get joint names to verify
        std::vector<std::string> joint_names = arm_->getJointNames();
        RCLCPP_DEBUG(node_->get_logger(), "MoveGroup has %zu joints: %s", 
                    joint_names.size(), 
                    joint_names.empty() ? "none" : joint_names[4].c_str());
        
        // Log the joint values being set
        RCLCPP_DEBUG(node_->get_logger(), "Setting joint target:");
        for (size_t i = 0; i < joints.size(); ++i) {
            std::string joint_name = (i < joint_names.size()) ? joint_names[i] : "unknown";
            RCLCPP_DEBUG(node_->get_logger(), "  %s[%zu] = %.4f", joint_name.c_str(), i, joints[i]);
        }
        

     

        auto names   = arm_->getJointNames();
        auto current = arm_->getCurrentJointValues();
        
        RCLCPP_DEBUG(node_->get_logger(), "Getting joint target:");
        std::vector<double> target;
        arm_->getJointValueTarget(target);

        for (size_t i = 0; i < names.size(); ++i) {
            RCLCPP_DEBUG(node_->get_logger(), "%s current=%.6f target=%.6f delta=%.6f",
                      names[i].c_str(), current[i], target[i], target[i] - current[i]);
        }


        arm_->setStartStateToCurrentState();
        arm_->setJointValueTarget(joints);
        MoveGroupInterface::Plan plan;
        bool success = (arm_->plan(plan) == moveit::core::MoveItErrorCode::SUCCESS);
        if (success) {
            const auto & traj = plan.trajectory.joint_trajectory;
            RCLCPP_DEBUG(node_->get_logger(), "Points: %zu", traj.points.size());
            if (!traj.points.empty()) {
              auto & p0 = traj.points.front();
              auto & pN = traj.points.back();
              RCLCPP_DEBUG(node_->get_logger(), "First pos[0]=%.6f last pos[0]=%.6f", p0.positions[0], pN.positions[0]);
            }

            arm_->execute(plan);
            RCLCPP_INFO(node_->get_logger(), "Planning and execution successful");
        } else {
            RCLCPP_ERROR(node_->get_logger(), "Planning and execution failed");
        }
     
    }

    void goToPoseTarget(double x, double y, double z, 
                        double roll, double pitch, double yaw, bool cartesian_path=false){
        tf2::Quaternion q;
        q.setRPY(roll, pitch, yaw);
        q = q.normalize();

        geometry_msgs::msg::PoseStamped target_pose;
        target_pose.header.frame_id = "base_link";
        target_pose.pose.position.x = x;
        target_pose.pose.position.y = y;
        target_pose.pose.position.z = z;
        target_pose.pose.orientation.x = q.getX();
        target_pose.pose.orientation.y = q.getY();
        target_pose.pose.orientation.z = q.getZ();
        target_pose.pose.orientation.w = q.getW();

        arm_->setStartStateToCurrentState();

        if (!cartesian_path) {
            arm_->setPoseTarget(target_pose);
            planAndExecute(arm_);
        }
        else {
            std::vector<geometry_msgs::msg::Pose> waypoints;
            waypoints.push_back(target_pose.pose);
            moveit_msgs::msg::RobotTrajectory trajectory;

            double fraction = arm_->computeCartesianPath(waypoints, 0.01, trajectory);

            if (fraction == 1) {
                arm_->execute(trajectory);
            }
        }
    }

    void openGripper(){
        gripper_->setStartStateToCurrentState();
        gripper_->setNamedTarget("gripper_open");
        planAndExecute(gripper_);
    }

    void closeGripper(){
        gripper_->setStartStateToCurrentState();
        gripper_->setNamedTarget("gripper_closed");
        planAndExecute(gripper_);
    }

    void disableCollisionDetection(){
        RCLCPP_INFO(node_->get_logger(), "Disabling collision detection for all links...");
        try {
            // Get the robot model to retrieve all link names
            const moveit::core::RobotModelConstPtr& robot_model = arm_->getRobotModel();
            if (!robot_model) {
                RCLCPP_WARN(node_->get_logger(), "Could not get robot model");
            } else {
                // Get all link names from the robot model
                std::vector<std::string> link_names = robot_model->getLinkModelNames();
                RCLCPP_INFO(node_->get_logger(), "Found %zu links in robot model", link_names.size());
                
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
                
                RCLCPP_INFO(node_->get_logger(), "ACM modified: collision detection disabled for all %zu links", link_names.size());
            }
        } catch (const std::exception& e) {
            RCLCPP_WARN(node_->get_logger(), "Could not modify ACM: %s", e.what());
            RCLCPP_WARN(node_->get_logger(), "Proceeding without ACM modification");
        }
    }
    

private:

    void planAndExecute(const std::shared_ptr<MoveGroupInterface> &interface)
    {
        MoveGroupInterface::Plan plan;
        bool success = (interface->plan(plan) == moveit::core::MoveItErrorCode::SUCCESS);

        if (success) {
            interface->execute(plan);
            RCLCPP_INFO(node_->get_logger(), "Planning and execution successful");
        } else {
            RCLCPP_ERROR(node_->get_logger(), "Planning and execution failed");
        }

    }

    void openGripperCallback(const Bool &msg)
    {
        if (msg.data) {
            openGripper();
        }
        else {
            closeGripper();
        }
    }

    void jointCmdCallback(const FloatArray &msg)
    {
        auto joints = msg.data;

        if (joints.size() == 3) {
            RCLCPP_INFO(node_->get_logger(), "Received joint command with %zu values", joints.size());
            goToJointTarget(joints);
        } else {
            RCLCPP_WARN(node_->get_logger(), "Joint command requires 3 values, got %zu", joints.size());
        }
    }
    void namedPoseCmdCallback(const String &msg)
    {
        goToNamedTarget(msg.data);
    }

    void poseCmdCallback(const FloatArray &msg)
    {
        // Expect 6 floats: x, y, z, roll, pitch, yaw
        if (msg.data.size() != 6) {
            RCLCPP_WARN(node_->get_logger(), "Pose command requires 6 floats (x, y, z, roll, pitch, yaw), got %zu", msg.data.size());
            return;
        }
        
        double x = msg.data[0];
        double y = msg.data[1];
        double z = msg.data[2];
        double roll = msg.data[3];
        double pitch = msg.data[4];
        double yaw = msg.data[5];
        
        goToPoseTarget(x, y, z, roll, pitch, yaw, false);
    }
 

    

    std::shared_ptr<rclcpp::Node> node_;
    std::shared_ptr<MoveGroupInterface> arm_;
    std::shared_ptr<MoveGroupInterface> gripper_;

    rclcpp::Subscription<Bool>::SharedPtr open_gripper_sub_;
    rclcpp::Subscription<FloatArray>::SharedPtr joint_cmd_sub_;
    rclcpp::Subscription<FloatArray>::SharedPtr pose_cmd_sub_;
    rclcpp::Subscription<String>::SharedPtr named_pose_cmd_sub_;
};


int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    // Use default node name - launch file will override with name="commander" if needed
    // This prevents conflicts when multiple instances are launched
    auto node = std::make_shared<rclcpp::Node>("commander");
    auto commander = Commander(node);
    commander.disableCollisionDetection();

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}