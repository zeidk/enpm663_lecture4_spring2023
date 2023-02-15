#include "rclcpp/rclcpp.hpp"
#include "enpm663_interfaces/srv/add_two_ints.hpp"
#include "service_cpp.hpp"

#include <memory>

void AddTwoIntsServiceServer::service_callback(const std::shared_ptr<enpm663_interfaces::srv::AddTwoInts::Request> request,
                                              std::shared_ptr<enpm663_interfaces::srv::AddTwoInts::Response> response)
{
    auto a = request->a;
    auto b = request->b;
    RCLCPP_INFO_STREAM(this->get_logger(), "Received request: " << request->a << " " << request->b);
    response->sum = a + b;
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto service_add_two_ints = std::make_shared<AddTwoIntsServiceServer>("service_add_two_int");
    rclcpp::spin(service_add_two_ints);
    rclcpp::shutdown();
}