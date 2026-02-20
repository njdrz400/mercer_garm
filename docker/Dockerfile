# syntax=docker/dockerfile:1.4
FROM osrf/ros:jazzy-desktop

ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies (rosdep installed via pip below)
RUN apt-get update && apt-get install -y \
    git \
    openssh-client \
    python3-pip \
    python3-venv \
    python3-colcon-common-extensions \
    && rm -rf /var/lib/apt/lists/*

# Install rosdep via pip (not in apt in this image)
RUN PIP_BREAK_SYSTEM_PACKAGES=1 pip3 install -U rosdep && \
    rosdep init || true && \
    rosdep update

# Clone your repo
WORKDIR /opt
RUN --mount=type=ssh git clone https://github.com/njdrz400/mercer_garm.git

# Install ROS dependencies via rosdep (apt)
# apt-get update needed here because earlier layer cleared apt lists
# Skip keys that may be missing in rosdistro (e.g. custom or from other repos)
WORKDIR /opt/mercer_garm/ros2
RUN apt-get update && \
    rosdep update && \
    rosdep install --from-paths src --ignore-src -y --skip-keys "moveit_configs_utils warehouse_ros_mongo gazebo_plugins gazebo_ros_pkgs gazebo_ros moveit::ros_planning_interface ament_python rviz" && \
    rm -rf /var/lib/apt/lists/*

# Copy and install PyPI-only requirements (run from repo root: docker build -f docker/Dockerfile .)
COPY requirements-pip.txt /opt/mercer_garm/ros2/requirements-pip.txt
RUN python3 -m venv /opt/venv && \
    . /opt/venv/bin/activate && \
    pip install --upgrade pip && \
    pip install --no-cache-dir -r requirements-pip.txt

ENV PATH="/opt/venv/bin:$PATH"

# Build ROS2 workspace (use system Python so ament finds catkin_pkg from apt)
RUN . /opt/ros/jazzy/setup.sh && PATH="/usr/bin:$PATH" colcon build

# Auto-source on container start
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc && \
    echo "source /opt/mercer_garm/ros2/install/setup.bash" >> ~/.bashrc

CMD ["bash"]
