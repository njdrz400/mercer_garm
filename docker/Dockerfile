# ROS 2 Jazzy desktop image: includes rqt, rviz2, and desktop tools
# Source is cloned from the repo (reproducible builds). Override with build-args.
FROM ros:jazzy-desktop

# Build args: repo and ref to clone (defaults for this project)
ARG REPO_URL=https://github.com/njdrz400/mercer_garm.git
ARG GIT_REF=main

# Avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive

# Install build deps and git
RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    git \
    python3-colcon-common-extensions \
    python3-rosdep \
    python3-vcstool \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /ros2_ws

# Clone repo into src (shallow to keep image smaller)
RUN git clone --depth 1 --branch "${GIT_REF}" "${REPO_URL}" src

# Install package dependencies (ignore missing keys for custom packages)
RUN . /opt/ros/jazzy/setup.sh \
    && apt-get update \
    && rosdep update \
    && rosdep install --from-paths src --ignore-src -r -y || true \
    && rm -rf /var/lib/apt/lists/*

# Build the workspace
RUN . /opt/ros/jazzy/setup.sh \
    && colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release

# Source workspace in new shells
RUN echo "source /ros2_ws/install/setup.bash" >> /etc/bash.bashrc
ENV ROS_DOMAIN_ID=0

CMD ["bash"]
