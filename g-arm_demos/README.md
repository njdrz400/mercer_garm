# G-Arm Demos Package

This package contains Jupyter notebooks and Python demo scripts for the G-Arm robot.

## Structure

```
g-arm_demos/
├── notebooks/          # Jupyter notebooks for demonstrations
├── demos/              # Python demo scripts
├── package.xml         # ROS2 package definition
├── setup.py            # Python package setup
├── CMakeLists.txt      # CMake build configuration
└── README.md           # This file
```

## Dependencies

- ROS2 Jazzy
- Python 3
- Jupyter Notebook
- NumPy
- Matplotlib
- MoveIt2 (for motion planning demos)

## Building

```bash
cd ~/ros2_ws
colcon build --packages-select g-arm_demos
source install/setup.bash
```

## Usage

### Jupyter Notebooks

Start Jupyter:
```bash
cd ~/ros2_ws
source install/setup.bash
jupyter notebook
```

Then navigate to the notebooks directory.

### Demo Scripts

Run a demo script:
```bash
cd ~/ros2_ws
source install/setup.bash
python3 install/g-arm_demos/share/g-arm_demos/demos/<script_name>.py
```

## License

Apache-2.0

