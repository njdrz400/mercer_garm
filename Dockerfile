# ROS 2 Jazzy desktop image: includes rqt, rviz2, and desktop tools
# Build from repo root: docker build -t mercer_garm:jazzy .
FROM ros:jazzy-desktop

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
    build-essential \
    python3-colcon-common-extensions \
    python3-rosdep \
    python3-vcstool \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /ros2_ws
COPY . /ros2_ws/src

RUN . /opt/ros/jazzy/setup.sh \
    && apt-get update \
    && rosdep update \
    && rosdep install --from-paths src --ignore-src -r -y || true \
    && rm -rf /var/lib/apt/lists/*

RUN . /opt/ros/jazzy/setup.sh \
    && colcon build --symlink-install --cmake-args -DCMAKE_BUILD_TYPE=Release

RUN echo "source /ros2_ws/install/setup.bash" >> /etc/bash.bashrc
ENV ROS_DOMAIN_ID=0

CMD ["bash"]
