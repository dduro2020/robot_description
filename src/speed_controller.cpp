#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"

class SpeedController : public rclcpp::Node
{
public:
    SpeedController() : Node("speed_controller"), duration_(15.0), max_speed_(1.5), axis_time_(5.0), acceleration_(0.3)
    {
        publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/robot_base_control/cmd_vel_unstamped", 10);
    
        timer_ = this->create_wall_timer(std::chrono::milliseconds(50), std::bind(&SpeedController::timer_callback, this));
        start_time_ = this->get_clock()->now();
    }

private:
    void timer_callback()
    {
        auto current_time = this->get_clock()->now();
        double elapsed_time = (current_time - start_time_).seconds();
        double speed = 0.0;
        
        if (elapsed_time < axis_time_)
        {
            speed = elapsed_time*acceleration_;
        } else if (elapsed_time > (axis_time_*2))
        {
            speed = max_speed_-(elapsed_time-(axis_time_*2))*acceleration_;
        } else {
            speed = max_speed_;
        }

        auto msg = std::make_shared<geometry_msgs::msg::Twist>();
        msg->linear.x = speed;
        msg->angular.z = 0.0;
        publisher_->publish(*msg);
        RCLCPP_INFO(this->get_logger(), "Publicando velocidad: %f", msg->linear.x);

        if (elapsed_time >= duration_)
        {
            RCLCPP_INFO(this->get_logger(), "Tiempo máximo alcanzado. Deteniendo el nodo.");
            rclcpp::shutdown();
        }
    }

    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Time start_time_;
    double duration_;
    double max_speed_;
    double axis_time_;
    double acceleration_;
    
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SpeedController>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
