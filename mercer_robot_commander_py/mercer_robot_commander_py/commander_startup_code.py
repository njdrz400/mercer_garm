#!/usr/bin/env python3
from moveit_configs_utils import MoveItConfigsBuilder
import rclpy
from moveit.planning import MoveItPy
from moveit.planning import PlanningComponent



ROBOT_CONFIG = MoveItConfigsBuilder(robot_name="g_arm", package_name="g_arm_moveit2")\
                                    .robot_description_semantic("config/g_arm.srdf", {"name": "g_arm"})\
                                    .to_dict()

ROBOT_CONFIG = { 
    **ROBOT_CONFIG,
    "planning_scene_monitor": {
            "name": "planning_scene_monitor",
            "robot_description": "robot_description",
            "joint_state_topic": "/joint_states",
            "attached_collision_object_topic": "/moveit_cpp/planning_scene_monitor",
            "publish_planning_scene_topic": "/moveit_cpp/publish_planning_scene",
            "monitored_planning_scene_topic": "/moveit_cpp/monitored_planning_scene",
            "wait_for_initial_state_timeout": 10.0,
        },
        "planning_pipelines": {
            "pipeline_names": ["ompl"]
        },
        "plan_request_params": {
            "planning_attempts": 1,
            "planning_pipeline": "ompl",
            "max_velocity_scaling_factor": 1.0,
            "max_acceleration_scaling_factor": 1.0
        },
        "ompl": {
            "planning_plugins": ["ompl_interface/OMPLPlanner"],
            "request_adapters": ["default_planning_request_adapters/ResolveConstraintFrames",
                            "default_planning_request_adapters/ValidateWorkspaceBounds",
                            "default_planning_request_adapters/CheckStartStateBounds",
                            "default_planning_request_adapters/CheckStartStateCollision"],
            "response_adapters": ["default_planning_response_adapters/AddTimeOptimalParameterization",
                             "default_planning_response_adapters/ValidateSolution",
                             "default_planning_response_adapters/DisplayMotionPath"],
            "start_state_max_bounds_error": 0.1
        }
}

def main(args=None):
    rclpy.init(args=args)
    moveit = MoveItPy(node_name="mercer_robot_commander_py",config_dict=ROBOT_CONFIG)
    arm = moveit.get_planning_component("arm")
    arm.set_start_state_to_current_state()
  
    arm.set_goal_state(configuration_name="Repose")
    plan_result = arm.plan()
    if not plan_result:
        print("Planning failed")
        return
    moveit.execute(plan_result.trajectory)
    rclpy.shutdown()