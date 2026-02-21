from setuptools import find_packages, setup
import os
from glob import glob

package_name = 'mercer_g_arm_sim'

setup(
    name=package_name,
    version='1.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
        # Install launch files
        (os.path.join('share', package_name, 'launch'),
            glob('launch/*.launch.py')),
        # Install URDF files (include both .urdf.xacro and .xacro files)
        (os.path.join('share', package_name, 'urdf'),
            glob('urdf/*.urdf.xacro') + glob('urdf/*.xacro')),
        # Install config files
        (os.path.join('share', package_name, 'config'),
            glob('config/*.yaml')),
        # Install world files
        (os.path.join('share', package_name, 'worlds'),
            glob('worlds/*.world')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='scott',
    maintainer_email='scott@todo.todo',
    description='Digital twin simulation package for G-Arm robot using Gazebo',
    license='Apache-2.0',
    extras_require={
        'test': [
            'pytest',
        ],
    },
    entry_points={
        'console_scripts': [
            'add_world_to_planning_scene = mercer_g_arm_sim.add_world_to_planning_scene:main',
            'add_grid_to_planning_scene = mercer_g_arm_sim.add_grid_to_planning_scene:main',
        ],
    },
)
