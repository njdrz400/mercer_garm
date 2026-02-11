# TRAC-IK kinematics solver setup

TRAC-IK is an alternative to KDL for inverse kinematics and often finds solutions when KDL fails (e.g. near joint limits or singularities).

## 1. Install the plugin (ROS 2 Jazzy)

```bash
sudo apt update
sudo apt install ros-jazzy-trac-ik-kinematics-plugin
```

## 2. Use TRAC-IK in MoveIt

Edit `config/kinematics.yaml` and set the solver to TRAC-IK:

```yaml
arm:
  kinematics_solver: trac_ik_kinematics_plugin/TRAC_IKKinematicsPlugin
  kinematics_solver_timeout: 60.0
  position_only_ik: True
  # Optional: solve_type can be Speed, Distance, Manipulation1, Manipulation2, Manipulation3
  solve_type: Speed
```

- **kinematics_solver_attempts** and **kinematics_solver_search_resolution** are not used by TRAC-IK (it restarts automatically).
- **solve_type**: `Speed` (default, fast), `Distance` (minimize distance from seed), `Manipulation1`/`2`/`3` (optimize manipulability).

## 3. Restart MoveIt and go_to_pose server

After changing `kinematics.yaml`, restart any node that uses MoveIt (e.g. move_group, go_to_pose_server):

```bash
# Restart your launch that starts move_group and go_to_pose_server
ros2 launch mercer_robot_commander_cpp go_to_pose_server.launch.py
```

## Switching back to KDL

To use KDL again, set in `config/kinematics.yaml`:

```yaml
arm:
  kinematics_solver: kdl_kinematics_plugin/KDLKinematicsPlugin
  kinematics_solver_search_resolution: 0.001
  kinematics_solver_timeout: 60.0
  kinematics_solver_attempts: 150000
  position_only_ik: True
```
