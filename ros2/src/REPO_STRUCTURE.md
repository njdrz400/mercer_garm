# Mercer G-Arm project layout

Project root: **`mercer_garm`** (renamed from `mercer_garm_ws`).

## Directory structure

```
mercer_garm/              ← project & Git repo root
├── .git/
├── .gitignore
├── ros2/                  ← ROS2 workspace (colcon build, source here)
│   ├── src/               ← ROS2 packages (current repo content)
│   ├── build/
│   ├── install/
│   └── log/
├── docs/                  ← Documentation
├── 3d_prints/             ← 3D print files (STL, etc.)
└── esp32/                 ← ESP32 firmware
```

- **`ros2/`** – Full ROS2 workspace. `src/` holds all packages; build/install/log stay under `ros2/`.
- **`docs/`** – Project docs (setup, wiring, API).
- **`3d_prints/`** – 3D print assets.
- **`esp32/`** – ESP32 code (Arduino, ESP-IDF, PlatformIO).

---

## How to create this layout

### 1. Rename workspace and create structure

```bash
# From parent of current workspace (e.g. /home/scott)
cd /home/scott
mv mercer_garm_ws mercer_garm
cd mercer_garm

# Create new top-level folders
mkdir -p docs 3d_prints esp32

# Move current ROS2 workspace contents into ros2/
mkdir -p ros2
mv src ros2/
mv build install log ros2/  2>/dev/null || true
# Move Docker files into ros2 if you want them with the ROS2 workspace
# mv Dockerfile docker-compose.yml .dockerignore ros2/  2>/dev/null || true
```

### 2. Git repo at `mercer_garm/`

- **If the repo is currently inside `src/`:** move `.git` up to `mercer_garm/` and put all tracked content under `ros2/src/`:

```bash
cd /home/scott/mercer_garm
mv ros2/src/.git .
# All tracked files were in src; they’re now in ros2/src. Tell git:
git add -A
git status   # should show ros2/src/..., docs/, 3d_prints/, esp32/
git add docs/ 3d_prints/ esp32/
# If docs/3d_prints/esp32 are empty, add .gitkeep so folders are tracked:
touch docs/.gitkeep 3d_prints/.gitkeep esp32/.gitkeep
git add docs/.gitkeep 3d_prints/.gitkeep esp32/.gitkeep
git commit -m "Restructure: ros2/, docs/, 3d_prints/, esp32/"
```

- **If you prefer a fresh repo** (no history from old `src/`):

```bash
cd /home/scott/mercer_garm
rm -rf ros2/src/.git
git init
echo "ros2/build/\nros2/install/\nros2/log/" > .gitignore
touch docs/.gitkeep 3d_prints/.gitkeep esp32/.gitkeep
git add .gitignore ros2/src docs 3d_prints esp32
git commit -m "Mercer G-Arm: ros2 workspace, docs, 3d_prints, esp32"
```

### 3. Top-level `.gitignore` (at `mercer_garm/`)

```
ros2/build/
ros2/install/
ros2/log/
```

---

## Using the ROS2 workspace

- **Build and source from `ros2/`:**

```bash
cd /home/scott/mercer_garm/ros2
colcon build --symlink-install
source install/setup.bash
```

- **Launch files** that use paths like `get_package_share_directory(...)` need no change; they resolve from the sourced workspace (`ros2/install`).

- **Hardcoded paths** (e.g. `/home/rosuser/mercer_garm_ws/...`) should be updated to `mercer_garm/ros2/...` or, better, to package-relative or share paths.

### Paths to update after moving to `mercer_garm/ros2/`

Replace `mercer_garm_ws` (or `/home/rosuser/mercer_garm_ws`, `/home/scott/mercer_garm_ws`) with `mercer_garm/ros2` where appropriate:

| File | Change |
|------|--------|
| `mercer_g_arm_desktop_bringup/launch/garm_sim_start_up.launch.py` | `file_path` → use `FindPackageShare('g_arm_moveit2')` or `mercer_garm/ros2/src/...` |
| `mercer_g_arm_rpi_bringup/launch/garm_start_up.launch.py` | Same for `file_path` |
| `mercer_robot_commander_cpp/launch/pose_list_commander.launch.py` | Default waypoints path → `mercer_garm/ros2/src/mercer_robot_commander_cpp/config/waypoints_example.yaml` or use `get_package_share_directory` |
| `mercer_robot_commander_cpp/scripts/README.md` | Example `cd` path → `mercer_garm/ros2` |

Prefer `get_package_share_directory('package_name')` + relative path so it works on any machine.

---

## Summary

| Path | Purpose |
|------|--------|
| `mercer_garm/` | Project root, Git repo root |
| `mercer_garm/ros2/` | ROS2 workspace (run colcon here, source `ros2/install/setup.bash`) |
| `mercer_garm/ros2/src/` | ROS2 packages (current code) |
| `mercer_garm/docs/` | Documentation |
| `mercer_garm/3d_prints/` | 3D print files |
| `mercer_garm/esp32/` | ESP32 code |
