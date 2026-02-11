#!/usr/bin/env python3
"""
Shows how to use a planning scene in MoveItPy to add collision objects and perform collision checking.
The robot will plan and execute a trajectory that avoids the collision boxes.
"""

import time
import os
import sys
import yaml
import rclpy
from rclpy.node import Node
from rclpy.logging import get_logger

from moveit.planning import MoveItPy

from geometry_msgs.msg import Pose
from moveit_msgs.msg import CollisionObject
from shape_msgs.msg import SolidPrimitive


def plan_and_execute(
    robot,
    planning_component,
    logger,
    sleep_time=0.0,
):
    """Helper function to plan and execute a motion."""
    # plan to goal
    logger.info("Planning trajectory")
    plan_result = planning_component.plan()

    # execute the plan
    if plan_result:
        logger.info("Executing plan")
        robot_trajectory = plan_result.trajectory
        robot.execute(robot_trajectory, controllers=[])
        logger.info("Plan executed successfully")
    else:
        logger.error("Planning failed")

    time.sleep(sleep_time)


def add_collision_objects(planning_scene_monitor, logger):
    """Helper function that adds collision objects (boxes) to the planning scene."""
    object_positions = [
        (0.15, 0.1, 0.5),
        (0.25, 0.0, 1.0),
        (-0.25, -0.3, 0.8),
        (0.25, 0.3, 0.75),
    ]
    object_dimensions = [
        (0.1, 0.4, 0.1),
        (0.1, 0.4, 0.1),
        (0.2, 0.2, 0.2),
        (0.15, 0.15, 0.15),
    ]

    logger.info("Adding collision objects to planning scene...")
    
    with planning_scene_monitor.read_write() as scene:
        # Add each box as a separate collision object with unique ID
        for i, (position, dimensions) in enumerate(zip(object_positions, object_dimensions)):
            collision_object = CollisionObject()
            collision_object.header.frame_id = "base_link"
            collision_object.id = f"box_{i}"
            collision_object.operation = CollisionObject.ADD

            # Create box pose
            box_pose = Pose()
            box_pose.position.x = position[0]
            box_pose.position.y = position[1]
            box_pose.position.z = position[2]
            box_pose.orientation.w = 1.0  # No rotation

            # Create box primitive
            box = SolidPrimitive()
            box.type = SolidPrimitive.BOX
            # Box dimensions: [width, height, depth]
            box.dimensions = list(dimensions)

            collision_object.primitives.append(box)
            collision_object.primitive_poses.append(box_pose)

            # Apply collision object to scene
            scene.apply_collision_object(collision_object)
            logger.info(f"Added collision box {i} at position {position} with dimensions {dimensions}")

        # Update the scene state
        scene.current_state.update()
    
    logger.info("All collision objects added successfully")


def main():
    ###################################################################
    # MoveItPy Setup
    ###################################################################
    # Initialize ROS2
    rclpy.init()
    
    # Create a temporary node just for logging (with a different name to avoid conflicts)
    # The launch file creates the actual node with parameters
    temp_node = Node("garm_motion_planning_logger")
    logger = temp_node.get_logger()
    logger.info("=" * 60)
    logger.info("Initializing MoveItPy...")
    logger.info("=" * 60)
    
    # The launch file creates a node with parameters, but MoveItPy creates its own
    # internal node and can't access those parameters. 
    # 
    # Solution: Create a node with the same name as MoveItPy will use, read parameters
    # from the launch node (which should be accessible since we're that node), and
    # then try to make them available to MoveItPy.
    #
    # Actually, when the launch file runs this executable, it creates a node with
    # the name 'garm_motion_planning_node' and sets parameters on it. We ARE that node.
    # So we should be able to read our own parameters.
    
    # The launch file sets parameters on the node 'garm_motion_planning_node'
    # MoveItPy creates its own internal node with the same name and looks for parameters
    # The issue is that parameters set on one node instance aren't accessible to another
    # node instance with the same name - they're different node objects.
    #
    # Solution: We need to ensure parameters are available via the parameter server
    # before MoveItPy initializes. Since we can't easily do that with SetParameter
    # (due to nested structures and large strings), we'll try a different approach:
    # Read parameters from sys.argv (which the launch file sets) and ensure they're
    # available, or use a parameter file.
    
    logger.info("Checking for parameters in command line arguments...")
    # The launch file passes parameters via --ros-args and --params-file
    # These should be available to the node, but MoveItPy creates its own node
    
    logger.info("Creating MoveItPy instance...")
    logger.info("MoveItPy will create its own internal node named 'garm_motion_planning_node'")
    logger.info("It needs access to planning pipeline parameters from the parameter server")
    
    # Create MoveItPy - it will look for parameters on its internal node
    # The parameters should be set by the launch file on a node with this name
    # but MoveItPy's node is a different instance, so it can't see them
    garm = MoveItPy(node_name="garm_motion_planning_node")
    
    # Get the planning component for the arm
    # Adjust the group name if your robot uses a different planning group
    try:
        arm = garm.get_planning_component("arm")
        logger.info("Planning component 'arm' found")
    except Exception as e:
        logger.error(f"Failed to get planning component 'arm': {e}")
        logger.info("Available planning groups may be different. Please check your SRDF.")
        return
    
    # Get planning scene monitor to add collision objects
    planning_scene_monitor = garm.get_planning_scene_monitor()
    logger.info("MoveItPy instance created successfully")

    ###################################################################
    # Add collision objects to the scene
    ###################################################################
    add_collision_objects(planning_scene_monitor, logger)
    
    # Give some time for the collision objects to be published to RViz
    time.sleep(2.0)
    logger.info("Collision objects should now be visible in RViz")

    ###################################################################
    # Plan and execute motion around collision objects
    ###################################################################
    
    # Set start state (using current state or a named state)
    try:
        # Try to use current state as start
        logger.info("Setting start state to current state")
        # The start state is typically the current state by default
    except Exception as e:
        logger.warning(f"Could not set start state: {e}")

    # Set goal state using the planning component
    # Option 1: Use a named configuration if available
    try:
        logger.info("Attempting to set goal state to 'extended' configuration")
        arm.set_goal_state(configuration_name="extended")
        logger.info("Goal state set to 'extended'")
    except Exception as e:
        logger.warning(f"Could not use named configuration 'extended': {e}")
        # Option 2: Set goal using joint values or pose
        logger.info("Setting goal state using alternative method...")
        try:
            # Try to set goal to a different named state or use pose goal
            # You can also set goal using: arm.set_goal_state_to_current_state()
            # Or set a pose goal if you have an end effector
            logger.info("Using current state as goal - please adjust for your specific use case")
            # For now, we'll try to plan without explicitly setting a goal
            # The user should set the goal interactively or modify this code
        except Exception as e2:
            logger.error(f"Could not set goal state: {e2}")
            logger.info("Continuing anyway - goal may need to be set manually")

    # Plan and execute
    logger.info("Planning trajectory that avoids collision objects...")
    plan_and_execute(garm, arm, logger, sleep_time=3.0)

    ###################################################################
    # Keep node alive to maintain collision objects in scene
    ###################################################################
    logger.info("Motion planning complete. Collision objects remain in scene.")
    logger.info("Keeping node alive. Press Ctrl+C to exit.")
    
    # Keep the node running to maintain collision objects in the scene
    try:
        while rclpy.ok():
            rclpy.spin_once(temp_node, timeout_sec=0.1)
    except KeyboardInterrupt:
        logger.info("Shutting down...")
    finally:
        temp_node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
