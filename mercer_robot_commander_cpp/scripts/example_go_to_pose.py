#!/usr/bin/env python3
"""
Example script demonstrating how to use the GoToPose action client
"""

import rclpy
import sys
import os

# Add the scripts directory to the path so we can import go_to_pose_client
script_dir = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, script_dir)

from go_to_pose_client import GoToPoseClient, create_pose_stamped


def example_basic_movement():
    """Example: Basic movement to a position"""
    rclpy.init()
    client = GoToPoseClient()
    
    if not client.wait_for_server():
        print("Action server not available")
        return
    
    # Move to position (0.25, 0.0, 0.20) with identity orientation
    target_pose = create_pose_stamped('base_link', 0.25, 0.0, 0.20)
    
    result = client.send_goal(
        target_pose,
        pos_tolerance_m=0.01,
        ang_tolerance_rad=0.2,
        timeout_sec=10.0,
        allow_orientation=True,  # Ignore orientation
        electromagnet_on=False
    )
    
    if result:
        client.wait_for_result()
    
    rclpy.shutdown()


def example_with_electromagnet():
    """Example: Move to position and turn on electromagnet"""
    rclpy.init()
    client = GoToPoseClient()
    
    if not client.wait_for_server():
        print("Action server not available")
        return
    
    # Move to position and turn electromagnet ON
    target_pose = create_pose_stamped('base_link', 0.25, 0.0, 0.15)
    
    result = client.send_goal(
        target_pose,
        pos_tolerance_m=0.01,
        ang_tolerance_rad=0.2,
        timeout_sec=10.0,
        allow_orientation=True,
        electromagnet_on=True  # Turn electromagnet ON
    )
    
    if result:
        result = client.wait_for_result()
        if result and result.success:
            print("Arm moved and electromagnet is now ON")
    
    rclpy.shutdown()


def example_sequence():
    """Example: Sequence of movements with electromagnet control"""
    rclpy.init()
    client = GoToPoseClient()
    
    if not client.wait_for_server():
        print("Action server not available")
        return
    
    # Sequence of positions
    positions = [
        (0.20, 0.0, 0.29, False),   # Position 1, electromagnet OFF
        (0.13, -0.17, 0.0025, True),     # Position 2, electromagnet ON
        (0.13, -0.17, 0.10, True),     # Position 3, electromagnet ON
        (0.225, 0.0, 0.02, False),  
       # Position 4, electromagnet OFF
        (0.18, -0.17, 0.02, False),
        (0.18, -0.17, 0.0025, True),
        (0.18, -0.17, 0.10, True),
        (0.275, 0.0, 0.025, False),
        

        (0.20, 0.0, 0.29, False), # Position 6, electromagnet OFF
             # Position 5, electromagnet ON
    ]
    
    for x, y, z, magnet_on in positions:
        print(f"\nMoving to ({x}, {y}, {z}) with electromagnet {'ON' if magnet_on else 'OFF'}")
        target_pose = create_pose_stamped('base_link', x, y, z)
        
        result = client.send_goal(
            target_pose,
            pos_tolerance_m=0.01,
            ang_tolerance_rad=0.2,
            timeout_sec=10.0,
            allow_orientation=True,
            electromagnet_on=magnet_on
        )
        
        if result:
            result = client.wait_for_result()
            if not result or not result.success:
                print(f"Failed to reach position ({x}, {y}, {z})")
                break
        else:
            print("Goal rejected")
            break
    
    rclpy.shutdown()


if __name__ == '__main__':
    import sys
    
    if len(sys.argv) > 1:
        if sys.argv[1] == 'basic':
            example_basic_movement()
        elif sys.argv[1] == 'magnet':
            example_with_electromagnet()
        elif sys.argv[1] == 'sequence':
            example_sequence()
        else:
            print("Usage: python3 example_go_to_pose.py [basic|magnet|sequence]")
    else:
        # Run basic example by default
        example_basic_movement()
