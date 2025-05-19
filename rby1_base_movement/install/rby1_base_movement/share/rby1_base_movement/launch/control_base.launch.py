from ament_index_python.packages import get_package_share_directory 
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare

def generate_launch_description():
    
    # Construct the full path to the YAML config file
    config_path = PathJoinSubstitution([
        FindPackageShare('keyboard'),
        'config',
        'mapping_config.yaml'
    ])

    return LaunchDescription([
        Node(
            package='rby1_base_movement',      # Replace with your package name
            executable='rby1_base_movement_subscriber', # Replace with your node executable
            name='movement',                   # Optional: node name
            output='screen'                   # Optional: print node output to terminal
        ),
        # Add more Node() entries as needed
	Node(
	    package='keyboard',
	    executable='keyboard',
	    name='keyboard',
	    ),
    Node(
	    package='keyboard',
	    executable='keyboard_to_joy.py',
	    name='joy_node',
        parameters=[{'config_file_name': config_path}]	)
    ])
