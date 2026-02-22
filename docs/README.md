Powershell usb setup for wsl
usbipd list
usbipd bind -b 1-2
usbipd attach --wsl --busid 1-2

FYI - ros2 launch mercer_robot_commander_cpp go_to_pose_server.launch.py



ros2 launch mercer_g_arm_desktop_bringup mercer_garm_bringup.launch.py use_mock_hardware:=false
ros2 launch mercer_robot_commander_cpp pose_list_commander.launch.py waypoints_file:=~/mercer_garm/ros2/src/mercer_robot_commander_cpp/config/waypoints_example.yaml 
