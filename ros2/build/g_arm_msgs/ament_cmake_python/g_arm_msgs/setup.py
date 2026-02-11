from setuptools import find_packages
from setuptools import setup

setup(
    name='g_arm_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('g_arm_msgs', 'g_arm_msgs.*')),
)
