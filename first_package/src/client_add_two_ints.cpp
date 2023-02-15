#include "rclcpp/rclcpp.hpp"
#include "enpm663_interfaces/srv/add_two_ints.hpp"
#include "client_cpp.hpp"

#include <memory>

void AddTwoIntServiceClient::callAddTwoIntService(int a, int b)
{
    auto request = std::make_shared<enpm663_interfaces::srv::AddTwoInts::Request>();
    request->a = a;
    request->b = b;

    auto result = m_service_client->async_send_request(request);

    try{
        auto response = result.get();
        RCLCPP_INFO_STREAM(this->get_logger(), "Result: " << a << " + " << b << " = " << response->sum);
        }
    catch(std::exception &e){
        RCLCPP_ERROR(this->get_logger(), "Service call failed: %s", e.what());
    }
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto service_client_cpp = std::make_shared<AddTwoIntServiceClient>("client_cpp_add_two_int");
    rclcpp::spin(service_client_cpp);
    rclcpp::shutdown();
}