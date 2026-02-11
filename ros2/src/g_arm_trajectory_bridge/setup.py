from setuptools import setup

package_name = 'g_arm_trajectory_bridge'

setup(
    name=package_name,
    version='0.1.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages', ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        # 👇 this line installs your launch file into share/<pkg>/launch
        ('share/' + package_name + '/launch', ['launch/g_arm_trajectory_bridge.launch.py']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='you',
    maintainer_email='you@example.com',
    description='FollowJointTrajectory bridge publishing /joint1 /joint2 /joint3 and /electromagnet',
    license='Apache-2.0',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            # executable name  =  module:function
            'bridge = g_arm_trajectory_bridge.bridge_node:main',
        ],
    },
)

