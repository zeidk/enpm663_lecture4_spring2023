#include <rclcpp/rclcpp.hpp>
#include "publisher_cpp.hpp"
#include "enpm663_interfaces/msg/weather_station.hpp"
#include <ctime>

void PublisherNode::timer_callback()
{
    std::time_t t = std::time(0);

    msg_.weather = enpm663_interfaces::msg::WeatherStation::SUNNY;
    msg_.day = enpm663_interfaces::msg::WeatherStation::WEDNESDAY;
    msg_.time = t;
    
    RCLCPP_INFO_STREAM(this->get_logger(), "Publishing weather forecast");
    publisher_->publish(msg_);
}

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto publisher_cpp = std::make_shared<PublisherNode>("publisher_cpp");
    rclcpp::spin(publisher_cpp);
    rclcpp::shutdown();
}