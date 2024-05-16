import launch
from launch_ros.actions import Node
from launch.actions import ExecuteProcess
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution


def generate_launch_description():
    # path to workspace
    workspace_dir = 'modelado_ws/src'

    package_name = 'robot_description'
    rosbag_dir = PathJoinSubstitution(
        [workspace_dir, package_name, "rosbags", "rosbag_sand"]
    )
    return launch.LaunchDescription([
        Node(
            package='robot_description',
            executable='speed_controller_node',
            name='speed_controller',
            output='screen'
        ),
        ExecuteProcess(
            cmd=['timeout', '15s', 'ros2', 'bag', 'record', '-o', rosbag_dir, '/robot_base_control/odom', '/joint_states'],
            output='screen'
        )
    ])