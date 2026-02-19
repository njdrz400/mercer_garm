# syntax=docker/dockerfile:1.4
FROM osrf/ros:jazzy-desktop

ENV DEBIAN_FRONTEND=noninteractive

# Install system dependencies and rosdep for ROS package deps
RUN apt-get update && apt-get install -y \
    git \
    openssh-client \
    python3-pip \
    python3-venv \
    python3-rosdep2 \
    python3-colcon-common-extensions \
    && rm -rf /var/lib/apt/lists/*

# Clone your repo
WORKDIR /opt
RUN --mount=type=ssh git clone https://github.com/njdrz400/mercer_garm.git

# Install ROS dependencies via rosdep (apt)
WORKDIR /opt/mercer_garm/ros2
RUN rosdep update && \
    rosdep install --from-paths src --ignore-src -y

# Copy and install PyPI-only requirements (run from repo root: docker build -f docker/Dockerfile .)
COPY docker/requirements-pip.txt /opt/mercer_garm/ros2/requirements-pip.txt
RUN python3 -m venv /opt/venv && \
    . /opt/venv/bin/activate && \
    pip install --upgrade pip && \
    pip install --no-cache-dir -r requirements-pip.txt

ENV PATH="/opt/venv/bin:$PATH"

# Build ROS2 workspace
RUN . /opt/ros/jazzy/setup.sh && colcon build

# Auto-source on container start
RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc && \
    echo "source /opt/mercer_garm/ros2/install/setup.bash" >> ~/.bashrc

CMD ["bash"]
