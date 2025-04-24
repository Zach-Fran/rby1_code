#include <iomanip>
#include <iostream>
#include <thread>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "rby1-sdk/model.h"
#include "rby1-sdk/robot.h"
#include "rby1-sdk/robot_command_builder.h"

using namespace rb;
using namespace std::chrono_literals;

#define D2R 0.017453
#define R2D 57.296



const std::string kAll = ".*";
class RBY1_Movement : public rclcpp::Node{
public:
    RBY1_Movement(std::shared_ptr<rb::Robot<rb::y1_model::A>> robot_, std::unique_ptr<rb::RobotCommandStreamHandler<rb::y1_model::A>> stream) : 
        Node("rby1_movement_subscriber"),
        robot_(robot_),
        stream(std::move(stream)) {
        
    /*
        robot->StartStateUpdate(
            [](const auto& state, const auto& control_manager) {
              std::cout << "Timestamp: " << state.timestamp.tv_sec << ".";
              std::cout << std::setw(9) << std::setfill('0') << state.timestamp.tv_nsec << std::endl;
              std::cout << "  Position: " << state.position.transpose() << std::endl;
              std::cout << "Control Manager State: " << rb::to_string(control_manager.state) << std::endl;
              for(std::size_t i = 0; i < state.joint_states.size(); ++i) {
                  auto& js = state.joint_states[i];
                  std::cout << "Index: " << i << " Temperature: " << js.temperature << std::endl;
              }
              
            },
            100);
	*/
        joy_sub_ = this->create_subscription<sensor_msgs::msg::Joy> (
            "joy",
            10,
            std::bind(&RBY1_Movement::joy_callback, this, std::placeholders::_1)
        );
	std::cout << "here" << std::endl;
        //robot->PowerOn(".*")
    };
    /*
    ~RBY1_Movement(){
    	if (robot_thread_.joinable()){
	    robot_thread_.join();
	}
    }
    */
private:
    std::shared_ptr<rb::Robot<rb::y1_model::A>> robot_;
    std::unique_ptr<rb::RobotCommandStreamHandler<rb::y1_model::A>> stream;
    
    Eigen::Vector<double, 2> linear_velocity;
    Eigen::Vector<double, 2> linear_acceleration_limit;
    double angular_velocity = 0; 
    double angular_acceleration_limit = 1.;
    double control_hold_time = .5;
    void joy_callback(const sensor_msgs::msg::Joy::SharedPtr msg) {
        if (!msg->axes.empty()) {
            //std::cout << "here1" << std::endl;
            float axis_linear = msg->axes[1]; // Range: [-1.0, 1.0]
            float axis_angular = msg->axes[0];
            //std::cout << "Axes[0]: " << axis_value << std::endl;
    
            // Use Eigen vectors of size 2 (assuming 2 wheels)
            
            //linear_velocity << 0, 0; 
            if (axis_linear > 0.5) {
                //std::cout << "here 1" << std::endl;
                linear_velocity << .3, .3; // Forward
            } else if (axis_linear < -0.5) {
                //std::cout << "here 2" << std::endl;
                linear_velocity << -.3, -.3; // Backward
            } else {
                //std::cout << "here 3" << std::endl;
                linear_velocity << 0, 0; // Stop
            }

            if (axis_angular > 0.5) {
                //std::cout << "here 1" << std::endl;
                angular_velocity = .5; // Forward
            } else if (axis_angular < -0.5) {
                //std::cout << "here 2" << std::endl;
                angular_velocity = -.5; // Backward
            } else {
                //std::cout << "here 3" << std::endl;
                angular_velocity = 0; // Stop
            }
            //std::cout << "here2" << std::endl;
            linear_acceleration_limit << 1, 1;
            
            // Send command to robot

            //std::cout << "blocking test 1" << std::endl;
            /*
            auto rv = robot_
                ->SendCommand(RobotCommandBuilder().SetCommand(
                    ComponentBasedCommandBuilder().SetMobilityCommand(
                        MobilityCommandBuilder().SetCommand(
                            SE2VelocityCommandBuilder()
                                .SetVelocity(linear_velocity, angular_velocity)
                                .SetAccelerationLimit(linear_acceleration_limit, angular_acceleration_limit)
                                //.SetMinimumTime(.5)
                                .SetCommandHeader(CommandHeaderBuilder().SetControlHoldTime(control_hold_time))
                        )
                    )
                ))->Get();
            */
            //std::cout << "here3" << std::endl;
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
};
int main(int argc, char** argv) {
    MobilityCommandBuilder mobility_command;
    RobotCommandBuilder rb_command;
    std::shared_ptr<rb::Robot<rb::y1_model::A>> robot_;
    std::unique_ptr<rb::RobotCommandStreamHandler<rb::y1_model::A>> stream;
  
    robot_ = rb::Robot<rb::y1_model::A>::Create("192.168.30.1:50051");
    robot_->Connect();
    stream = robot_->CreateCommandStream();
    /*robot_thread_ = std::thread([this]() {
        robot_->Connect();
        std::cout << robot_->GetRobotInfo().robot_version << std::endl;
        std::cout << "test" << std::endl;
        }
    );
    */
    rclcpp::init(argc, argv);
    std::cout << "init" << std::endl;
    rclcpp::spin(std::make_shared<RBY1_Movement>(robot_, std::move(stream)));
    rclcpp::shutdown();

    return 0;
    }
