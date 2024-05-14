#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

class SpeedController : public rclcpp::Node
{
public:
    SpeedController() : Node("speed_controller")
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/robot_base_control/cmd_vel_unstamped", 10);
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&SpeedController::timer_callback, this));
    }

private:
    void timer_callback()
    {
        auto msg = std::make_shared<geometry_msgs::msg::Twist>();
        msg->linear.x = 800;
        msg->angular.z = 0.0;
        publisher_->publish(*msg);
        RCLCPP_INFO(this->get_logger(), "Publicando velocidad: %f", msg->linear.x);
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SpeedController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
