#!/usr/bin/env python3
# garm_example_moveitpy.py
from geometry_msgs.msg import PoseStamped
from moveit.planning import MoveItPy

def main():
    # Node spins internally
    moveit = MoveItPy(node_name="garm_example_moveitpy")

    # TODO: use your planning group name from SRDF
    arm = moveit.get_planning_component("arm")

    # Plan to a pose
    pose_goal = PoseStamped()
    pose_goal.header.frame_id = "base_link"     # your base frame
    pose_goal.pose.position.x = 0.25
    pose_goal.pose.position.y = 0.00
    pose_goal.pose.position.z = 0.15
    pose_goal.pose.orientation.w = 1.0

    arm.set_start_state_to_current_state()
    # TODO: set your end-effector link
    arm.set_goal_state(pose_stamped_msg=pose_goal, pose_link="tool0")

    plan_result = arm.plan()
    if not plan_result:
        print("Planning failed")
        return

    # Execute planned trajectory
    moveit.execute(plan_result.trajectory)

if __name__ == "__main__":
    main()

