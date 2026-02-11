import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/scott/mercer_garm/ros2/install/g_arm_trajectory_bridge'
