#include <rclcpp/rclcpp.hpp>
#include "enpm663_interfaces/srv/add_two_ints.hpp"
#include <string>
#include <cstdlib>

// timer
class AddTwoIntServiceClient : public rclcpp::Node
{
public:
    AddTwoIntServiceClient(std::string node_name) : Node(node_name)
    {

        m_service_client = this->create_client<enpm663_interfaces::srv::AddTwoInts>("add_two_ints");
        while(!m_service_client->wait_for_service(std::chrono::seconds(1))){
            RCLCPP_INFO(this->get_logger(), "Waiting for service to be available...");
        }

        // callAddTwoIntService(1, 2);
        m_thread = std::thread(std::bind(&AddTwoIntServiceClient::callAddTwoIntService, this, 1, 2));
    }

private:
    // attributes
    rclcpp::Client<enpm663_interfaces::srv::AddTwoInts>::SharedPtr m_service_client;
    void callAddTwoIntService(int a, int b);
    std::thread m_thread;

};