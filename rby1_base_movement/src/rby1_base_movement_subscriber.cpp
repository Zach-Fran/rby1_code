#include <iomanip>
#include <iostream>
#include <algorithm>
#include <thread>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "rby1-sdk/model.h"
#include "rby1-sdk/robot.h"
#include "rby1-sdk/robot_command_builder.h"
//#include "rby1_movement/srv/speed_control.hpp"

using namespace rb;
using namespace std::chrono_literals;

#define D2R 0.017453
#define R2D 57.296


const std::string kAll = ".*";
class RBY1_Movement : public rclcpp::Node{
public:
    RBY1_Movement(std::shared_ptr<rb::Robot<rb::y1_model::A>> robot_, 
        std::unique_ptr<rb::RobotCommandStreamHandler<rb::y1_model::A>> stream) : 
        Node("rby1_movement_subscriber"),
        robot_(robot_),
        stream(std::move(stream)),
        current_speed_(0.5) {

/*
        speed_service_ = this->create_service<rby1_movement::srv::SpeedControl>(
            "speed_control",
            std::bind(&RBY1_Movement::speed_control_callback, this,
                      std::placeholders::_1, std::placeholders::_2)
        );
*/
        joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy> (
            "joy",
            10,
            std::bind(&RBY1_Movement::joy_callback, this, std::placeholders::_1)
        );

	std::cout << "here" << std::endl;
        //robot->PowerOn(".*")
    };

private:
    std::shared_ptr<rb::Robot<rb::y1_model::A>> robot_;
    std::unique_ptr<rb::RobotCommandStreamHandler<rb::y1_model::A>> stream;
    
    Eigen::Vector<double, 2> linear_velocity;
    Eigen::Vector<double, 2> linear_acceleration_limit;
    double angular_velocity = 0; 
    double angular_acceleration_limit = 1.;
    double control_hold_time = 1;
    int speed_control;
    double current_height = 1.0;
    
    /*
    void speed_control_callback(const std::shared_ptr<rby1_movement::srv::SpeedControl::Request> request,
                                std::shared_ptr<rby1_movement::srv::SpeedControl::Response> response) {
        current_speed_ = request->speed_input;
        response->success = true;
        RCLCPP_INFO(get_logger(), "Updated speed to: %.2f", current_speed_.load());
                                }
    */
    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg) {
        if (!msg->axes.empty()) {
            // Sending base control commands
            //std::cout << "here1" << std::endl;
            float axis_linear = msg->axes[1]; // Range: [-1.0, 1.0]
            float axis_angular = msg->axes[0];
            //float speed = current_speed_.load();
            double current_speed = 0.5;
            std::cout << msg->buttons[0] << std::endl;
            /*
            int button =  msg->buttons;
            int size = sizeof(button) / sizeof(button[0]);
            int target = 1;
            speed_control = std::find(button, button + size, target);
            std::cout << speed_control << std::endl;
            // Use Eigen vectors of size 2 (assuming 2 wheels)
*/
            //linear_velocity << 0, 0; 
            if (axis_linear > 0.5) {
                //std::cout << "here 1" << std::endl;
                linear_velocity << current_speed, current_speed; // Forward
            } else if (axis_linear <  -0.5) {
                //std::cout << "here 2" << std::endl;
                linear_velocity << -current_speed, -current_speed; // Backward
            } else {
                //std::cout << "here 3" << std::endl;
                linear_velocity << 0, 0; // Stop
            }

            if (axis_angular > 0.5) {
                //std::cout << "here 1" << std::endl;
                angular_velocity = 1; // Forward
            } else if (axis_angular < -0.5) {
                //std::cout << "here 2" << std::endl;
                angular_velocity = -1; // Backward
            } else {
                //std::cout << "here 3" << std::endl;
                angular_velocity = 0; // Stop
            }
            //std::cout << "here2" << std::endl;
            linear_acceleration_limit << 1, 1;
            

            MobilityCommandBuilder mobility_command;
            mobility_command.SetCommand(SE2VelocityCommandBuilder()
                                      .SetVelocity(linear_velocity, angular_velocity)
                                      .SetAccelerationLimit(linear_acceleration_limit, angular_acceleration_limit)
                                      .SetMinimumTime(0.5)
                                      );
                                      
            //std::cout << "here4" << std::endl;
            RobotCommandBuilder rb_command;
            rb_command.SetCommand(ComponentBasedCommandBuilder().SetMobilityCommand(mobility_command));
            //std::cout << "here5" << std::endl;
            stream->SendCommand(rb_command);
        }
    }

    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr joy_sub_;
    //rclcpp::Service<rby1_movement::srv::SpeedControl>::SharedPtr speed_service_;
    std::atomic<float> current_speed_;
};
int main(int argc, char** argv) {
    MobilityCommandBuilder mobility_command;
    RobotCommandBuilder rb_command;
    std::shared_ptr<rb::Robot<rb::y1_model::A>> robot_;
    std::unique_ptr<rb::RobotCommandStreamHandler<rb::y1_model::A>> stream;
    robot_ = rb::Robot<rb::y1_model::A>::Create("192.168.30.1:50051");
    //robot_ = rb::Robot<rb::y1_model::A>::Create("172.17.0.1:50051");
    int speed_control;
    robot_->Connect();
    if (!robot_->IsPowerOn(kAll)){
        robot_->PowerOn(kAll);
        robot_->ServoOn(kAll);
        
    }

    robot_->EnableControlManager();

    stream = robot_->CreateCommandStream();
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<RBY1_Movement>(robot_, std::move(stream)));
    rclcpp::shutdown();

    return 0;
    }
