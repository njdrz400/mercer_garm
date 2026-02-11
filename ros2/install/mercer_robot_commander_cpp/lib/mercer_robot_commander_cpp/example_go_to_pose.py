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


def example_home():
    """Example: Move to Home position and wait 10 seconds"""
    rclpy.init()
    client = GoToPoseClient()
    
    if not client.wait_for_server():
        print("Action server not available")
        return
    
    # Home position from SRDF: joint1=0, joint2=0, joint3=0
    # We need to compute the pose for these joint values
    # Based on typical robot kinematics, Home is usually around:
    # x=0.22, y=0.0, z=0.29 (approximate - depends on your robot's link lengths)
    # For exact pose, you'd need to compute FK, but this is a reasonable approximation
    # You can also query the current pose after moving to Home using MoveIt
    
    # Approximate Home pose (you may need to adjust based on your robot)
    # To get exact: move to Home using MoveIt, then query getCurrentPose()
    target_pose = create_pose_stamped('base_link', 0.22, 0.0, 0.29, qw=1.0)
    
    print("Moving to Home position (approximate pose)...")
    result = client.send_goal(
        target_pose,
        pos_tolerance_m=0.01,
        ang_tolerance_rad=0.2,
        timeout_sec=10.0,
        allow_orientation=True,  # Ignore orientation
        electromagnet_on=False
    )
    
    if result:
        result = client.wait_for_result()
        if result and result.success:
            print("Successfully moved to Home position")
            print(f"Final position: x={result.final_pos_error_m:.4f}m error")
            print("\nWaiting 10 seconds...")
            import time
            for i in range(10, 0, -1):
                print(f"  {i}...", end='', flush=True)
                time.sleep(1.0)
            print("\nDone waiting.")
        else:
            print("Failed to reach Home position")
    else:
        print("Goal rejected")
    
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
        (0.22, 0.0, 0.29, False),   # Position 1, electromagnet OFF
        (0.175, -0.175, 0.05, False),     # Position 2, electromagnet ON
        #(0.175, -0.175, 0.10, True),     # Position 3, electromagnet ON
        #(0.225, 0.0, 0.02, False),  
       # Position 4, electromagnet OFF
        #(0.225, -0.175, 0.02, False),
        #(0.225, -0.175, 0.005, True), # Position 4, electromagnet ON
        #(0.225, -0.175, 0.005, True), # Position 5, electromagnet ON
        #(0.225, -0.175, 0.10, True),
        #(0.27, 0.0, 0.025, False),
        

        #(0.20, 0.0, 0.29, False), # Position 6, electromagnet OFF
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
        if sys.argv[1] == 'home':
            example_home()
        elif sys.argv[1] == 'magnet':
            example_with_electromagnet()
        elif sys.argv[1] == 'sequence':
            example_sequence()
        else:
            print("Usage: python3 example_go_to_pose.py [home|magnet|sequence]")
    else:
        # Run basic example by default
        example_home()
