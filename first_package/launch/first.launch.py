# pull in some Python launch modules.
from launch import LaunchDescription
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory


from launch.substitutions import PathJoinSubstitution
from launch_ros.substitutions import FindPackageShare


# this function is needed
def generate_launch_description():
    ld = LaunchDescription()            # instantiate a Launchdescription object
    
    # publisher_config = os.path.join(
    #     get_package_share_directory('first_package'),
    #     'config',
    #     'publisher.yaml'
    # )
    
    publisher_config = PathJoinSubstitution(
        [FindPackageShare("first_package"), "config", "publisher.yaml"]
    )
    
    publisher_node = Node(              # declare your Node
        package="first_package",        # package name
        executable="publisher_cpp",    
        parameters=[publisher_config],
    )
    
    service_node = Node(      
        package="first_package",
        executable="service_add_two_ints"
    )
    
    subscriber_node = Node(
        package="first_package",
        executable="subscriber_cpp",
    )
    ld.add_action(publisher_node)       # add each Node to the LaunchDescription object
    # ld.add_action(subscriber_node)      # add each Node to the LaunchDescription object
    ld.add_action(service_node)
    return ld                           # return the LaunchDescription object
