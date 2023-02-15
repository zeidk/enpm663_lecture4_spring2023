#include <rclcpp/rclcpp.hpp>
#include "enpm663_interfaces/srv/add_two_ints.hpp"
#include <string>
#include <cstdlib>

class AddTwoIntsServiceServer : public rclcpp::Node
{
public:
    AddTwoIntsServiceServer(std::string node_name) : Node(node_name)
    {

        m_service_server = this->create_service<enpm663_interfaces::srv::AddTwoInts>("add_two_ints", std::bind(&AddTwoIntsServiceServer::service_callback, this, std::placeholders::_1, std::placeholders::_2));
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");
    }

private:
    // attributes
    rclcpp::Service<enpm663_interfaces::srv::AddTwoInts>::SharedPtr m_service_server;

    // methods
    void service_callback(const std::shared_ptr<enpm663_interfaces::srv::AddTwoInts::Request> request,
                          std::shared_ptr<enpm663_interfaces::srv::AddTwoInts::Response> response);
};