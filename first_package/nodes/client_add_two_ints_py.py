#!/usr/bin/env python3

import rclpy
from first_package.first_package import ClientAddTwoInts


def main(args=None):
    rclpy.init(args=args)
    node = ClientAddTwoInts('client_py_add_two_int')
    a = 1
    b = 2
    response = node.send_request(a, b)
    node.get_logger().info(
        'Result of add_two_ints: for %d + %d = %d' %
        (a, b, response.sum))
    rclpy.shutdown()


if __name__ == '__main__':
    main()
