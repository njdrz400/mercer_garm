#!/usr/bin/env python3

"""
Node that adds a planar grid as collision objects to MoveIt2's planning scene.
The robot can plan around the grid. Default: 300 mm x 300 mm, 50 mm spacing, 5 mm thickness.
"""

import rclpy
from rclpy.node import Node
from moveit_msgs.msg import PlanningScene, CollisionObject, ObjectColor
from shape_msgs.msg import SolidPrimitive
from geometry_msgs.msg import Pose
from std_msgs.msg import ColorRGBA
import time

# White color for grid visualization in RViz
WHITE = ColorRGBA(r=1.0, g=1.0, b=1.0, a=1.0)
# Black color for squares on top of grid
BLACK = ColorRGBA(r=0.0, g=0.0, b=0.0, a=1.0)

# Default square-on-grid thickness in meters (2 mm)
SQUARE_THICKNESS_DEFAULT = 0.002
# Thickness of the 4 lines that form each square (5 mm)
SQUARE_LINE_THICKNESS = 0.005


def _to_color(color):
    """Convert ColorRGBA or (r, g, b, a) sequence to ColorRGBA."""
    if isinstance(color, ColorRGBA):
        return color
    r, g, b = float(color[0]), float(color[1]), float(color[2])
    a = float(color[3]) if len(color) > 3 else 1.0
    return ColorRGBA(r=r, g=g, b=b, a=a)

# Default dimensions in meters (300 mm, 50 mm, 5 mm)
DEFAULT_SIZE_X = 0.6
DEFAULT_SIZE_Y = 0.9
DEFAULT_SPACING = 0.05
DEFAULT_THICKNESS = 0.005


class GridToPlanningScene(Node):
    """Publishes a grid of collision boxes to MoveIt2's planning scene."""

    def __init__(self):
        super().__init__('add_grid_to_planning_scene')

        self.declare_parameter('size_x', DEFAULT_SIZE_X)
        self.declare_parameter('size_y', DEFAULT_SIZE_Y)
        self.declare_parameter('spacing', DEFAULT_SPACING)
        self.declare_parameter('thickness', DEFAULT_THICKNESS)
        self.declare_parameter('frame_id', 'base_link')
        self.declare_parameter('center_x', 0.15)
        self.declare_parameter('center_y', 0.15)
        self.declare_parameter('center_z', 0.0)
        # List of [x, y] or [x, y, z] (meters) defining center of each colored square on the grid
        self.declare_parameter('black_square_centers', [])
        # Color for those squares as [r, g, b, a] in 0–1 (default black)
        self.declare_parameter('square_color', [0.0, 0.0, 0.0, 1.0])

        self.size_x = self.get_parameter('size_x').value
        self.size_y = self.get_parameter('size_y').value
        self.spacing = self.get_parameter('spacing').value
        self.thickness = self.get_parameter('thickness').value
        self.frame_id = self.get_parameter('frame_id').value
        self.center_x = self.get_parameter('center_x').value
        self.center_y = self.get_parameter('center_y').value
        self.center_z = self.get_parameter('center_z').value

        self.scene_publisher = self.create_publisher(
            PlanningScene, '/planning_scene', 10
        )

        # Wait for subscribers
        time.sleep(2.0)

        self.clear_planning_scene()
        self.add_grid_objects()

    def clear_planning_scene(self):
        """Clear the planning scene (remove previous collision objects) before adding new ones."""
        scene = PlanningScene()
        scene.is_diff = False  # replace entire scene
        scene.robot_state.is_diff = True  # do not replace robot state
        scene.world.collision_objects.clear()
        self.scene_publisher.publish(scene)
        self.get_logger().info('Cleared planning scene')
        time.sleep(0.5)  # allow the clear to be applied before we add new objects

    def add_grid_objects(self):
        """Build grid from thin boxes and publish to planning scene."""
        scene = PlanningScene()
        scene.is_diff = True
        scene.robot_state.is_diff = True

        # Half thickness for z center (grid lies in XY, thickness in Z)
        half_t = self.thickness / 2.0
        z_center = self.center_z + half_t

        # Horizontal lines (along X): length = size_x, width = thickness
        num_h = int(round(self.size_y / self.spacing)) + 1
        for i in range(num_h):
            y_local = i * self.spacing
            y_world = self.center_y - self.size_y / 2.0 + y_local

            obj = CollisionObject()
            obj.id = f"grid_h_{i}"
            obj.header.frame_id = self.frame_id
            obj.operation = CollisionObject.ADD

            prim = SolidPrimitive()
            prim.type = SolidPrimitive.BOX
            prim.dimensions = [self.size_x, self.thickness, self.thickness]

            pose = Pose()
            pose.position.x = self.center_x
            pose.position.y = y_world
            pose.position.z = z_center
            pose.orientation.w = 1.0

            obj.primitives.append(prim)
            obj.primitive_poses.append(pose)
            scene.world.collision_objects.append(obj)
            oc = ObjectColor(id=obj.id, color=WHITE)
            scene.object_colors.append(oc)

        # Vertical lines (along Y): width = thickness, length = size_y
        num_v = int(round(self.size_x / self.spacing)) + 1
        for j in range(num_v):
            x_local = j * self.spacing
            x_world = self.center_x - self.size_x / 2.0 + x_local

            obj = CollisionObject()
            obj.id = f"grid_v_{j}"
            obj.header.frame_id = self.frame_id
            obj.operation = CollisionObject.ADD

            prim = SolidPrimitive()
            prim.type = SolidPrimitive.BOX
            prim.dimensions = [self.thickness, self.size_y, self.thickness]

            pose = Pose()
            pose.position.x = x_world
            pose.position.y = self.center_y
            pose.position.z = z_center
            pose.orientation.w = 1.0

            obj.primitives.append(prim)
            obj.primitive_poses.append(pose)
            scene.world.collision_objects.append(obj)
            oc = ObjectColor(id=obj.id, color=WHITE)
            scene.object_colors.append(oc)

        # Add colored squares on top of grid if centers are provided
        square_centers = self._get_black_square_centers_param()
        if not square_centers:
            square_centers = [
                (0.075, 0.275),
                (0.125, 0.275),
                (0.175, 0.275),
                (0.225, 0.275),
                (0.275, 0.275),

                (0.075, -0.225),
                (0.125, -0.225),        
                (0.175, -0.225),
                (0.225, -0.225),
                (0.275, -0.225),
             
                (0.225, 0.025),
                (0.275, 0.025),
                (0.325, 0.025),
                (0.225, -0.025),
                (0.275, -0.025),
                (0.325, -0.025),
                (0.225, 0.075),
                (0.275, 0.075),
                (0.325, 0.075),

            ]
        square_color = _to_color(self.get_parameter('square_color').value)
        self.add_squares_on_grid(scene, square_centers, color=square_color)

        self.scene_publisher.publish(scene)
        self.get_logger().info(
            f'Published grid to planning scene: {num_h} horizontal + {num_v} vertical '
            f'lines ({self.size_x*1000:.0f}x{self.size_y*1000:.0f} mm, '
            f'spacing {self.spacing*1000:.0f} mm, thickness {self.thickness*1000:.0f} mm)'
        )

    def _get_black_square_centers_param(self):
        """Read black_square_centers from parameter (list of [x,y] or [x,y,z] in meters)."""
        param = self.get_parameter('black_square_centers')
        value = param.value
        if not isinstance(value, list):
            return []
        out = []
        for item in value:
            try:
                if isinstance(item, (list, tuple)) and len(item) >= 2:
                    z = float(item[2]) if len(item) > 2 else None
                    out.append((float(item[0]), float(item[1]), z))
            except (TypeError, ValueError, IndexError):
                continue
        return out

    def add_squares_on_grid(
        self,
        scene,
        center_points,
        color=None,
        square_thickness_m=SQUARE_THICKNESS_DEFAULT,
    ):
        """
        Add colored square outlines on the grid: 4 lines only, not solid.

        Each square is drawn with 4 lines (top, bottom, left, right). Each line has
        a thickness of 5 mm. The interior of the square is empty (no geometry).

        Args:
            scene: MoveIt PlanningScene message to append to (modified in place).
            center_points: List of (x, y) or (x, y, z) in meters. (x, y) is the center in the
                grid plane; if z is omitted, the square is placed in the grid plane.
            color: ColorRGBA or (r, g, b, a) in [0, 1]. Default black.
            square_thickness_m: Unused; line thickness is 5 mm.
        """
        if not center_points:
            return
        color = _to_color(color) if color is not None else BLACK
        z_center = self.center_z + self.thickness   # same Z as grid lines
        side = self.spacing
        half = side / 2.0
        # Each of the 4 lines has thickness 5 mm (in-plane width and Z height)
        line_thickness = SQUARE_LINE_THICKNESS  # 5 mm

        for i, pt in enumerate(center_points):
            x, y = float(pt[0]), float(pt[1])
            z = float(pt[2]) if len(pt) > 2 and pt[2] is not None else z_center

            # Four lines (not solid): top, bottom, left, right. Each line is 5 mm thick.
            edges = [
                ("top", side, line_thickness, x, y + half),
                ("bottom", side, line_thickness, x, y - half),
                ("left", line_thickness, side, x - half, y),
                ("right", line_thickness, side, x + half, y),
            ]
            for edge_name, dim_x, dim_y, px, py in edges:
                obj = CollisionObject()
                obj.id = f"square_{i}_{edge_name}"
                obj.header.frame_id = self.frame_id
                obj.operation = CollisionObject.ADD

                prim = SolidPrimitive()
                prim.type = SolidPrimitive.BOX
                prim.dimensions = [dim_x, dim_y, line_thickness]

                pose = Pose()
                pose.position.x = px
                pose.position.y = py
                pose.position.z = z
                pose.orientation.w = 1.0

                obj.primitives.append(prim)
                obj.primitive_poses.append(pose)
                scene.world.collision_objects.append(obj)
                scene.object_colors.append(ObjectColor(id=obj.id, color=color))

        self.get_logger().info(
            f'Added {len(center_points)} square(s) on grid (4 lines, 5 mm thick, not solid)'
        )


def main(args=None):
    rclpy.init(args=args)
    node = GridToPlanningScene()
    time.sleep(1.0)
    rclpy.shutdown()


if __name__ == '__main__':
    main()
