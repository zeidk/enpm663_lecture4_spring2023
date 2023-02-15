#pragma once

#include <rclcpp/rclcpp.hpp>
// #include <example_interfaces/msg/string.hpp>
#include "enpm663_interfaces/msg/weather_station.hpp"

using namespace std::chrono_literals;
// timer
class PublisherNode : public rclcpp::Node
{
public:
    PublisherNode(std::string node_name) : Node(node_name)
    {
        this->declare_parameter("publishing_interval", 1.0);

        rclcpp::Parameter pub_frequency = this->get_parameter("publishing_interval");
        // initialize the message
        msg_ = enpm663_interfaces::msg::WeatherStation();
        // timer callback
        timer_ = this->create_wall_timer(1s * pub_frequency.as_double(),
                                         std::bind(&PublisherNode::timer_callback, this));

        // publisher
        publisher_ = this->create_publisher<enpm663_interfaces::msg::WeatherStation>("weather_forecast", 10);
    }

private:
    // attributes
    enpm663_interfaces::msg::WeatherStation msg_;

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<enpm663_interfaces::msg::WeatherStation>::SharedPtr publisher_;

    // methods
    void timer_callback();
};