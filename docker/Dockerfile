# syntax=docker/dockerfile:1.4
FROM osrf/ros:jazzy-desktop


ENV DEBIAN_FRONTEND=noninteractive

# Install additional ROS packages
RUN apt-get update && apt-get install -y \
    python3-colcon-common-extensions \
    python3-vcstool \
    python3-pip \
    python3-venv \
    nano \
    python3-serial \
    ros-jazzy-ros2-control \
    ros-jazzy-ros2-controllers \
    ros-jazzy-moveit \
    ros-jazzy-joint-state-publisher \
    ros-jazzy-joint-state-publisher-gui \
    ros-jazzy-xacro \
    python3-termcolor \
    && rm -rf /var/lib/apt/lists/*

# Create venv and install pip requirements into it
COPY requirements-pip.txt /tmp/requirements-pip.txt
RUN python3 -m venv /opt/venv \
    && /opt/venv/bin/pip install --upgrade pip \
    && /opt/venv/bin/pip install --no-cache-dir -r /tmp/requirements-pip.txt \
    && rm /tmp/requirements-pip.txt

ENV PATH="/opt/venv/bin:$PATH"

# Create workspace folder
RUN mkdir -p /ros2_ws/

WORKDIR /ros2_ws

# Auto-source ROS and venv (venv after ROS so ROS scripts take precedence where needed)
RUN echo "source /opt/ros/jazzy/setup.bash" >> /root/.bashrc \
    && echo "source /opt/venv/bin/activate" >> /root/.bashrc \
    && echo "source /ros2_ws/install/setup.bash" >> /root/.bashrc