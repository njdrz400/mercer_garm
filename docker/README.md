# Docker build and run (WSL, Linux, Mac)

This image is based on `osrf/ros:jazzy-desktop` and adds colcon, pip dependencies, and ROS 2 Jazzy packages used by the G-Arm stack (MoveIt2, ros2_control, etc.).
## 0. Prep

git clone https://github.com/njdrz400/mercer_garm.git

For windows 
install Xlauncher https://x.cygwin.com/docs/xlaunch/
Install Docker Desktop
Install WSL/Ubuntu 24.04

---

## 1. Build the image

Build context must be the `docker/` directory so `requirements-pip.txt` is found.

### All platforms (WSL, Linux, Mac)

From the **repository root**:

```bash
docker build -f docker/Dockerfile -t mercer_garm:jazzy docker/
```

Or from inside `docker/`:

```bash
cd docker
docker build -t mercer_garm:jazzy .
```

### Platform-specific (optional)

- **Apple Silicon (M1/M2/M3):** Use the same command; if the base image has no arm64 variant, use:
  ```bash
  docker build -f docker/Dockerfile --platform linux/amd64 -t mercer_garm:jazzy docker/
  ```
- **WSL:** No extra flags; use the standard build command above.
- **Linux:** No extra flags.

---

## 2. Run the container

The image only provides the environment. You need to mount your workspace (or copy it in) and build/source it inside the container.

### WSL2 (Windows)

GUI (RViz) works with WSLg. From repo root:

docker run -it --rm   -v "$(pwd)/mercer_garm/ros2:/ros2_ws/src" -v /tmp/.X11-unix:/tmp/.X11-unix  -e DISPLAY="$DISPLAY"   -e QT_X11_NO_MITSHM=1   mercer_garm:jazzy   bash

Then inside the container:

```bash
source /opt/ros/jazzy/setup.bash
cd /ros2_ws && colcon build --symlink-install
source install/setup.bash
# Then run a launch file (see Sim mode below)
```

### Linux (native)

Same as WSL2; if X11 is used and you see permission errors, add:

```bash
docker run -it --rm \
  -v "$(pwd)/ros2:/ros2_ws/src" \
  -e DISPLAY="$DISPLAY" \
  -v /tmp/.X11-unix:/tmp/.X11-unix:rw \
  -e QT_X11_NO_MITSHM=1 \
  mercer_garm:jazzy \
  bash
```

On the host once per session: `xhost +local:docker` (or a more restrictive rule) if RViz cannot open a window.

### Mac (Docker Desktop)

Docker runs a Linux VM. For RViz you typically need an X server on the host (e.g. XQuartz) and to pass `DISPLAY` from the host into the container, or use VNC. Example with host network and XQuartz:

```bash
# On Mac: start XQuartz, then in XQuartz prefs enable "Allow connections from network clients"
# Get your Mac's IP (e.g. 192.168.1.2)
docker run -it --rm \
  -v "$(pwd)/ros2:/ros2_ws/src" \
  -e DISPLAY=host.docker.internal:0 \
  mercer_garm:jazzy \
  bash
```

Then inside the container: build and source as in the WSL section, then run your launch file.

---

## 3. Sim mode: launch files and parameters

Sim mode runs **without real hardware**: mock ros2_control is used, and the physical G-Arm driver is not started.

### Option A: Desktop bringup with mock hardware (recommended)

**Launch file:** `mercer_garm_bringup.launch.py`  
**Package:** `mercer_g_arm_desktop_bringup`

**Required parameter:**

| Parameter            | Value   | Description                                                     |
|----------------------|---------|-----------------------------------------------------------------|
| `use_mock_hardware`  | `true`  | Use mock_components; do not start the real robot driver or USB. |



**Example (inside container after sourcing workspace):**

```bash
ros2 launch mercer_g_arm_desktop_bringup mercer_garm_bringup.launch.py use_mock_hardware:=true
```



No `usb_port` or `x_zero_real_angle` is needed in sim; they only apply when `use_mock_hardware:=false`.

---



## 4. Quick reference



## 5. One-shot sim (WSL/Linux) from repo root

```bash
docker run -it --rm \
  -v "$(pwd)/ros2:/ros2_ws/src" \
  -e DISPLAY="$DISPLAY" \
  -e QT_X11_NO_MITSHM=1 \
  mercer_garm:jazzy \
  bash -c "source /opt/ros/jazzy/setup.bash && cd /ros2_ws && colcon build --symlink-install && source install/setup.bash && ros2 launch mercer_g_arm_desktop_bringup mercer_garm_bringup.launch.py use_mock_hardware:=true"
```

(On Linux you may need `-v /tmp/.X11-unix:/tmp/.X11-unix:rw` and `xhost +local:docker`.)
