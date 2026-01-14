#include <rclcpp/rclcpp.hpp>
#include <moveit/move_group_interface/move_group_interface.hpp>
#include <chrono>
#include <thread>

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);

    auto node = rclcpp::Node::make_shared("test_moveit");
    RCLCPP_INFO(node->get_logger(), "Starting MoveIt node..."); 
    
    rclcpp::executors::SingleThreadedExecutor executor;
    executor.add_node(node);
    
    auto spinner = std::thread([&]() {executor.spin();});

    //logger.info("Starting MoveIt node...");
    RCLCPP_INFO(node->get_logger(), "Creating move group interface..."); 

    auto arm = moveit::planning_interface::MoveGroupInterface(node, "arm");
    arm.setMaxVelocityScalingFactor(1.0);
    arm.setMaxAccelerationScalingFactor(1.0);
    
    // Set the goal target first
    RCLCPP_INFO(node->get_logger(), "Setting goal to 'Repose'...");
    arm.setNamedTarget("Repose");
    
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

    moveit::planning_interface::MoveGroupInterface::Plan plan1;
    bool success = (arm.plan(plan1) == moveit::core::MoveItErrorCode::SUCCESS);
    if (success) {
        RCLCPP_INFO(node->get_logger(), "Planning successful");
        arm.execute(plan1);
    } else {
        RCLCPP_ERROR(node->get_logger(), "Planning failed");
    }

    rclcpp::shutdown();
    spinner.join();
    return 0;
}

 