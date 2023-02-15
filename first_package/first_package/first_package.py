import rclpy
from rclpy.node import Node
from enpm663_interfaces.msg import WeatherStation
from enpm663_interfaces.srv import AddTwoInts
from functools import partial
import time 

class ClientAddTwoInts(Node):
    def __init__(self, node_name):
        super().__init__(node_name)
        self._client = self.create_client(AddTwoInts, 'add_two_ints')
        while not self._client.wait_for_service(timeout_sec=1.0):
            self.get_logger().info('service not available, waiting again...')
        self._request = AddTwoInts.Request()
        
    def send_request(self, a, b):
        self._request.a = a
        self._request.b = b
        self.future = self._client.call_async(self._request)
        rclpy.spin_until_future_complete(self, self.future)
        return self.future.result()
    

class PublisherNode(Node):
    
    ''' PublisherNode This class is a node that publishes a string message.

    Arguments:
        Node -- Node class from rclpy
    '''
    def __init__(self, node_name):
        super().__init__(node_name)
        self.declare_parameter('publishing_interval', 1.0)
        
        self._pub_frequency = self.get_parameter('publishing_interval').value
        # self._publisher = self.create_publisher(String, 'chatter663', 10)
        self._publisher = self.create_publisher(WeatherStation, 'weather_forecast', 10)
        self._timer = self.create_timer(self._pub_frequency, self.timer_callback)
        self.get_logger().info(f'{node_name} node running')
        self._msg = WeatherStation()
        

    def timer_callback(self):
        self._msg.weather=WeatherStation.SUNNY
        self._msg.day=WeatherStation.MONDAY
        self._msg.time = time.time()
        self._publisher.publish(self._msg)
        self.get_logger().info('Publishing weather forecast')
        # self._msg.data = 'Help me Obi-Wan Kenobi, you are my only hope.'
        # self._publisher.publish(self._msg)
        # self.get_logger().info('Publishing: "%s"' % self._msg.data)


class SubscriberNode(Node):
    '''SubscriberNode This class is a node that subscribes to a string message and publishes the first word of the message.

    Arguments:
        Node -- Node class from rclpy
    '''
    def __init__(self, node_name):
        super().__init__(node_name)
        self._subscriber = self.create_subscription(String, 'chatter663', self.subscriber_callback, 10)
        # self._publisher = self.create_publisher(String, 'chatter2', 10)
        self.get_logger().info(f'{node_name} node running')

    def subscriber_callback(self, msg):
        self.get_logger().info('Receiving: "%s"' % msg.data)
        # first_word = str(msg.data).split()[0]
        # new_msg = String()
        # new_msg.data = first_word
        # self._publisher.publish(new_msg)
