# GoToPose Action Client Scripts

Python scripts for controlling the robot arm and electromagnet via the GoToPose action server.

## Installation

After building the workspace:
```bash
cd /home/scott/mercer_garm_ws
colcon build
source install/setup.bash
```

## Usage

### Command Line Client (`go_to_pose_client.py`)

Basic usage:
```bash
ros2 run mercer_robot_commander_cpp go_to_pose_client.py --x 0.25 --y 0.0 --z 0.20 --electromagnet-on
```

**Common Options:**
- `--x`, `--y`, `--z`: Target position in meters (default: 0.25, 0.0, 0.20)
- `--qw`, `--qx`, `--qy`, `--qz`: Target orientation quaternion (default: w=1.0, identity)
- `--frame`: Target frame ID (default: 'base_link')
- `--pos-tol`: Position tolerance in meters (default: 0.01)
- `--ang-tol`: Orientation tolerance in radians (default: 0.2)
- `--timeout`: Maximum time to complete goal in seconds (default: 10.0)
- `--allow-orientation`: Ignore orientation constraints
- `--electromagnet-on`: Turn electromagnet ON after reaching pose
- `--electromagnet-off`: Turn electromagnet OFF after reaching pose
- `--speed-scale`: Speed scaling factor 0.0-1.0 (0.0 = use default)
- `--cancel`: Cancel current goal

**Examples:**

1. Move to position with electromagnet ON:
```bash
ros2 run mercer_robot_commander_cpp go_to_pose_client.py \
  --x 0.25 --y 0.0 --z 0.20 \
  --electromagnet-on
```

2. Move to position ignoring orientation:
```bash
ros2 run mercer_robot_commander_cpp go_to_pose_client.py \
  --x 0.30 --y 0.05 --z 0.15 \
  --allow-orientation
```

3. Move with custom orientation:
```bash
ros2 run mercer_robot_commander_cpp go_to_pose_client.py \
  --x 0.25 --y 0.0 --z 0.20 \
  --qw 0.707 --qx 0.0 --qy 0.707 --qz 0.0
```

### Programmatic Usage

You can also use the client in your own Python scripts:

```python
import rclpy
from go_to_pose_client import GoToPoseClient, create_pose_stamped

rclpy.init()
client = GoToPoseClient()

if client.wait_for_server():
    # Create target pose
    target_pose = create_pose_stamped('base_link', 0.25, 0.0, 0.20)
    
    # Send goal with electromagnet ON
    if client.send_goal(
        target_pose,
        pos_tolerance_m=0.01,
        ang_tolerance_rad=0.2,
        timeout_sec=10.0,
        allow_orientation=False,
        electromagnet_on=True
    ):
        result = client.wait_for_result()
        if result and result.success:
            print("Success!")
            print(f"Final position error: {result.final_pos_error_m} m")
            print(f"Final orientation error: {result.final_ang_error_rad} rad")

rclpy.shutdown()
```

### Example Scripts (`example_go_to_pose.py`)

Run example sequences:
```bash
# Basic movement
ros2 run mercer_robot_commander_cpp example_go_to_pose.py basic

# Movement with electromagnet
ros2 run mercer_robot_commander_cpp example_go_to_pose.py magnet

# Sequence of movements
ros2 run mercer_robot_commander_cpp example_go_to_pose.py sequence
```

## API Reference

### `GoToPoseClient` Class

#### Methods:

- **`wait_for_server(timeout_sec=10.0)`**: Wait for action server to become available
- **`send_goal(...)`**: Send a goal to the action server
  - Returns: `True` if goal accepted, `False` otherwise
- **`wait_for_result(timeout_sec=None)`**: Wait for goal completion
  - Returns: `GoToPose.Result` object
- **`cancel_goal()`**: Cancel the current goal
- **`feedback_callback(feedback_msg)`**: Called automatically with feedback updates

### Helper Functions:

- **`create_pose_stamped(frame_id, x, y, z, qx=0.0, qy=0.0, qz=0.0, qw=1.0)`**: 
  Create a PoseStamped message with the specified position and orientation

### Jog GUI (`g_arm_jog_gui.py`)

Interactive GUI for jogging the robot and controlling the electromagnet and LEDs.

**Launch the GUI:**
```bash
ros2 launch mercer_robot_commander_cpp g_arm_jog_gui.launch.py
```

Or run directly:
```bash
ros2 run mercer_robot_commander_cpp g_arm_jog_gui.py
```

**Features:**
- **XYZ Jogging**: Use +/- buttons to jog the robot in X, Y, or Z directions
- **Jog Step Size**: Adjustable step size (default: 0.01m) for fine or coarse movements
- **Electromagnet Control**: Toggle button to turn electromagnet ON/OFF
- **LED Control**: Toggle buttons for each LED (GPIO pins 17, 18, 27)
- **Status Display**: Real-time status messages showing current operations

**Requirements:**
- MoveIt Servo must be running for jogging to work (publishes to `/delta_twist_cmds`)
- Tool controller or magnet controller must be available for electromagnet control
- GPIO action server (`/pi_gpio_server`) must be running for LED control

**Usage Tips:**
- Click and hold the +/- buttons for continuous jogging
- Press the STOP button or release keys to stop jogging immediately
- Adjust the jog step size for finer or coarser movements
- Status messages indicate the current operation and any errors

### Pose List Commander (`pose_list_commander_node.py` + `pose_list_commander_interface.py`)

Moves the g-arm through a list of coordinates: **start pose → waypoints → back to start**. An interface lets you start the sequence, monitor which position the robot is on, and notifies when the robot is back at the start.

**Launch (node + GUI):**
```bash
# Requires go_to_pose_server and move_group to be running
ros2 launch mercer_robot_commander_cpp pose_list_commander.launch.py
```

**Launch without GUI (interface=false):**
```bash
ros2 launch mercer_robot_commander_cpp pose_list_commander.launch.py interface:=false
```

**Waypoints file:** Set via parameter `waypoints_file` (default: package `config/waypoints_example.yaml`). YAML has two parts: **waypoints** (name -> x,y,z coordinates) and **path** (order of waypoints with per-step led_color and electromagnet_on). Example:
```yaml
led_color: g   # default (g, y, r)

waypoints:
  Home:   { x: 0.22, y: 0.0, z: 0.29 }
  Pick:   { x: 0.3,  y: 0.0, z: 0.02 }
  X00:    { x: 0.025, y: 0.225, z: 0.01 }
  Finish: { x: 0.3,  y: 0.0, z: 0.02 }

path:
  - { wp: Home,   led: y, em_on: false }
  - { wp: Pick,   led: g,  em_on: false, pause_sec: 0.5 }
  - { wp: X00,    led: y, em_on: false }
  - { wp: Finish, led: g,  em_on: false }
```
Path: one line per step. Keys: **wp** (waypoint name), **led** (g/y/r), **em_on** (electromagnet on/off), **pause_sec** (optional). Long names (waypoint, led_color, electromagnet_on) and led values (green, yellow, red) also work.
Path steps reference waypoints by name; each step can set **led**, **em_on**, and **pause_sec**. The same waypoint can appear multiple times in the path with different settings.

**Topics:** The node publishes status for monitoring:
- `pose_list_commander/state` (std_msgs/String): `idle`, `moving`, `pausing`, `returning`, `back_at_start`, `cancelled`, `error`
- `pose_list_commander/pause_duration_sec` (std_msgs/Float64): Published when entering a pause (duration in seconds)
- `pose_list_commander/current_index` (std_msgs/Int32): current position index in the sequence
- `pose_list_commander/current_waypoint_name` (std_msgs/String): name of the current waypoint (from config)
- `pose_list_commander/led_color` (std_msgs/String): LED color for current waypoint (g, y, or r), updated as the sequence runs
- `pose_list_commander/total_count` (std_msgs/Int32): total steps (waypoints + 1 for return)
- `pose_list_commander/back_at_start` (std_msgs/Bool): `true` when robot has returned to start

**Services:** Start or cancel the sequence:
- `pose_list_commander/start` (std_srvs/Trigger): start from current pose through waypoints then back to start
- `pose_list_commander/cancel` (std_srvs/Trigger): cancel the current run

**Interface:** The GUI shows status, progress (e.g. "Position 3 of 5"), the **current waypoint name**, an **LED indicator** (per-waypoint color), and **Pausing (X.Xs)** when the robot is paused between waypoints. A clear **"Robot is back at start position."** is shown when the sequence finishes.

## Notes

- The electromagnet is controlled after the arm successfully reaches the target pose
- If `allow_orientation=True`, orientation constraints are ignored
- The action server will automatically try both `tool_controller` and `magnet_controller` for electromagnet control
- Make sure the action server is running: `ros2 launch mercer_robot_commander_cpp go_to_pose_server.launch.py`
- For jog GUI, ensure MoveIt Servo is running: `ros2 launch g_arm_moveit2 servo.launch.py`