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

## Notes

- The electromagnet is controlled after the arm successfully reaches the target pose
- If `allow_orientation=True`, orientation constraints are ignored
- The action server will automatically try both `tool_controller` and `magnet_controller` for electromagnet control
- Make sure the action server is running: `ros2 launch mercer_robot_commander_cpp go_to_pose_server.launch.py`
- For jog GUI, ensure MoveIt Servo is running: `ros2 launch g_arm_moveit2 servo.launch.py`