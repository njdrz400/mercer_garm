#!/usr/bin/env python3

"""
Node to add world objects to MoveIt2's planning scene for RViz visualization.
"""

import rclpy
from rclpy.node import Node
from moveit_msgs.msg import PlanningScene, CollisionObject
from shape_msgs.msg import SolidPrimitive
from geometry_msgs.msg import Pose
import time


class WorldToPlanningScene(Node):
    """Publishes world objects as collision objects to MoveIt2's planning scene."""
    
    def __init__(self):
        super().__init__('mercer_g_arm_sim_add_world_to_planning_scene')
        self.scene_publisher = self.create_publisher(PlanningScene, '/planning_scene', 10)
        
        # Wait a bit for subscribers to connect
        time.sleep(2.0)
        
        # Add world objects to planning scene
        self.add_world_objects()
    
    def add_world_objects(self):
        """Add world objects (tiny_wall) to the planning scene."""
        scene = PlanningScene()
        scene.is_diff = True
        scene.robot_state.is_diff = True
        
        # Add tiny_wall as a collision object
        wall_object = CollisionObject()
        wall_object.id = "tiny_wall"
        # Use the robot's base frame (typically base_link or the planning frame)
        # This will be resolved by MoveIt2's planning scene monitor
        wall_object.header.frame_id = "base_link"
        wall_object.operation = CollisionObject.ADD
        
        # Define wall as a box
        wall_primitive = SolidPrimitive()
        wall_primitive.type = SolidPrimitive.BOX
        wall_primitive.dimensions = [0.03, 0.01, 0.02]  # length, width, height
        
        wall_pose = Pose()
        wall_pose.position.x = 0.25
        wall_pose.position.y = 0.25
        wall_pose.position.z = 0.01  # Half height (0.02/2)
        wall_pose.orientation.w = 1.0
        
        wall_object.primitives.append(wall_primitive)
        wall_object.primitive_poses.append(wall_pose)
        
        scene.world.collision_objects.append(wall_object)
        
        # Publish the scene
        self.scene_publisher.publish(scene)
        self.get_logger().info('Published world objects to planning scene')


def main(args=None):
    rclpy.init(args=args)
    node = WorldToPlanningScene()
    
    # Keep node alive briefly to ensure message is published
    time.sleep(1.0)
    rclpy.shutdown()


if __name__ == '__main__':
    main()

