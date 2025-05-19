from ament_index_python.packages import get_package_share_directory 
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
    
    # Construct the full path to the YAML config file
    keyboard_pkg_path = get_package_share_directory('keyboard')
    config_file = f"{keyboard_pkg_path}/config/example_config.yaml"
    return LaunchDescription([
        DeclareLaunchArgument(
            'config',
            default_value='',
            description='key_mapping'
        ),
        Node(
            package='rby1_movement',      # Replace with your package name
            executable='rby1_movement_subscriber', # Replace with your node executable
            name='movement',                   # Optional: node name
            output='screen'                   # Optional: print node output to terminal
        ),
        # Add more Node() entries as needed
	Node(
	    package='keyboard_joy',
	    executable='joy_node',
	    name='keyboard',
        parameters=[{'config': LaunchConfiguration('config')}]
	    )
    ])
