# syntax=docker/dockerfile:1.4
FROM osrf/ros:jazzy-desktop


ENV DEBIAN_FRONTEND=noninteractive

# Install additional ROS packages
RUN apt-get update && apt-get install -y \
    python3-colcon-common-extensions \
    python3-vcstool \
    python3-pip \
    ros-jazzy-ros2-control \
    ros-jazzy-ros2-controllers \
    ros-jazzy-moveit \
    ros-jazzy-joint-state-publisher \
    ros-jazzy-joint-state-publisher-gui \
    ros-jazzy-xacro \
    && rm -rf /var/lib/apt/lists/*

# Install pip requirements
COPY requirements-pip.txt /tmp/requirements-pip.txt
RUN python3 -m pip install --break-system-packages --no-cache-dir -r /tmp/requirements-pip.txt \
    && rm /tmp/requirements-pip.txt

# Create workspace folder
RUN mkdir -p /ros2_ws/

WORKDIR /ros2_ws

# Auto-source ROS
RUN echo "source /opt/ros/jazzy/setup.bash" >> /root/.bashrc
RUN echo "source /ros2_ws/install/setup.bash" >> /root/.bashrc