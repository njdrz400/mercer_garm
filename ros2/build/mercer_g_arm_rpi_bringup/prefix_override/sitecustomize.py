import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/scott/mercer_garm/ros2/install/mercer_g_arm_rpi_bringup'
