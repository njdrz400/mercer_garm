# G-Arm Digital Twin Simulation Package

This package provides a digital twin simulation for the G-Arm robot using Gazebo and ROS2 Jazzy.

## Overview

The `mercer_g_arm_sim` package creates a virtual replica of the G-Arm robot that can be used for:
- Testing and development without physical hardware
- Motion planning and trajectory execution
- Integration with MoveIt2 for advanced manipulation
- Safe experimentation with different control strategies

## Features

- **Gazebo Physics Simulation**: Full physics-based simulation of the G-Arm robot
- **ROS2 Control Integration**: Compatible with ros2_control for joint control
- **MoveIt2 Integration**: Ready for motion planning and manipulation
- **Realistic Dynamics**: Proper inertial properties and joint limits

## Package Structure

```
mercer_g_arm_sim/
├── launch/              # Launch files
│   ├── gazebo.launch.py           # Basic Gazebo simulation
│   └── gazebo_moveit.launch.py     # Gazebo + MoveIt2 integration
├── urdf/                # Gazebo-compatible URDF files
│   ├── g_arm_gazebo.urdf.xacro           # Main Gazebo URDF
│   ├── g_arm_gazebo_plugins.xacro        # Gazebo physics plugins
│   └── g_arm_gazebo_ros2_control.xacro  # ROS2 control configuration
├── config/              # Configuration files
│   ├── initial_positions.yaml           # Initial joint positions
│   ├── gazebo_ros2_control.yaml         # Gazebo control config
│   └── ros2_controllers.yaml            # Controller configuration
└── worlds/              # Gazebo world files
    └── empty.world                      # Empty simulation world
```

## Dependencies

- ROS2 Jazzy
- Gazebo (Humble or later)
- `g_arm_description` - Robot description package
- `g_arm_moveit2` - MoveIt2 configuration
- `ros2_control` - Control framework
- `gazebo_ros` - Gazebo ROS integration

## Building

```bash
cd ~/ros2_ws
colcon build --packages-select mercer_g_arm_sim
source install/setup.bash
```

## Usage

### Basic Gazebo Simulation

Launch the robot in Gazebo with basic controllers:

```bash
ros2 launch mercer_g_arm_sim gazebo.launch.py
```

### Gazebo + MoveIt2

Launch the robot in Gazebo with MoveIt2 integration:

```bash
ros2 launch mercer_g_arm_sim gazebo_moveit.launch.py
```

This will:
1. Start Gazebo with an empty world
2. Spawn the G-Arm robot
3. Load ROS2 controllers
4. Launch MoveIt2 with RViz

### Controlling the Robot

Once launched, you can control the robot using:

- **MoveIt2 RViz Plugin**: Interactive motion planning through RViz
- **ROS2 Topics**: Publish joint commands to `/g_arm_controller/joint_trajectory`
- **Python API**: Use the `g_arm_python_examples` package for programmatic control

## Configuration

### Initial Joint Positions

Edit `config/initial_positions.yaml` to set the starting pose of the robot.

### Controller Parameters

Modify `config/ros2_controllers.yaml` to adjust controller settings like update rates and gains.

### World Environment

Replace `worlds/empty.world` with custom worlds for different simulation scenarios.

## Troubleshooting

### Robot doesn't spawn

- Ensure all dependencies are installed
- Check that `g_arm_description` package is built and sourced
- Verify Gazebo is properly installed

### Controllers not loading

- Check that `ros2_control` is installed
- Verify the controller configuration files are correct
- Check the terminal output for error messages

### Physics issues

- Adjust inertial properties in `g_arm_gazebo_plugins.xacro`
- Modify joint damping and friction parameters
- Check Gazebo physics settings in the world file

## Contributing

When adding new features:
1. Update the URDF files for any robot model changes
2. Test with both basic Gazebo and MoveIt2 launches
3. Update this README with new features

## License

Apache-2.0

