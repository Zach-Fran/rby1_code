#include <iomanip>
#include <iostream>
#include <algorithm>
#include <thread>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
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
        if (!msg->buttons.empty()) {
          float button0 = msg->buttons[0];
          if (button0 > 0) {
            current_height += 0.1;
            double minimum_time = 2.5;
            double angular_velocity_limit = 3.141592 * 1.5;
            double linear_velocity_limit = 1.5;
            double acceleration_limit = 1.0;
            double stop_orientation_tracking_error = 1e-5;
            double stop_position_tracking_error = 1e-5;
            std::cout << "Cartesian command example 1\n";
            Eigen::Matrix<double, 4, 4> T_torso, T_right, T_left;
            T_torso.setIdentity();
            T_right.setIdentity();
            T_left.setIdentity();
        
            T_torso.block(0, 0, 3, 3).setIdentity();
            T_torso.block(0, 3, 3, 1) << 0, 0, current_height;
        
            T_right.block(0, 0, 3, 3) = math::SO3::RotY(-3.141592 / 4.);
            T_right.block(0, 3, 3, 1) << 0.5, -0.3, 1.0;
        
            T_left.block(0, 0, 3, 3) = math::SO3::RotY(-3.141592 / 4.);
            T_left.block(0, 3, 3, 1) << 0.5, 0.3, 1.0;
        
            auto rv = robot_
                          ->SendCommand(RobotCommandBuilder().SetCommand(ComponentBasedCommandBuilder().SetBodyCommand(
                              BodyComponentBasedCommandBuilder()
                                  .SetTorsoCommand(CartesianCommandBuilder()
                                                       .AddTarget("base", "link_torso_5", T_torso, linear_velocity_limit,
                                                                  angular_velocity_limit, acceleration_limit / 2)
                                                       .SetMinimumTime(minimum_time * 1)
                                                       .SetStopOrientationTrackingError(stop_orientation_tracking_error)
                                                       .SetStopPositionTrackingError(stop_position_tracking_error))
                                  .SetRightArmCommand(CartesianCommandBuilder()
                                                          .AddTarget("base", "ee_right", T_right, linear_velocity_limit,
                                                                     angular_velocity_limit, acceleration_limit / 2)
                                                          /* Need to be verified */
                                                          .AddJointPositionTarget("right_arm_2", -10 * M_PI / 180, 3.14, 6.28)
                                                          .SetMinimumTime(minimum_time * 3)
                                                          .SetStopOrientationTrackingError(stop_orientation_tracking_error)
                                                          .SetStopPositionTrackingError(stop_position_tracking_error))
                                  .SetLeftArmCommand(CartesianCommandBuilder()
                                                         .AddTarget("base", "ee_left", T_left, linear_velocity_limit,
                                                                    angular_velocity_limit, acceleration_limit / 2)
                                                         /* Need to be verified */
                                                         .AddJointPositionTarget("left_arm_2", 10 * M_PI / 180, 3.14, 6.28)
                                                         .SetMinimumTime(minimum_time * 3)
                                                         .SetStopOrientationTrackingError(stop_orientation_tracking_error)
                                                         .SetStopPositionTrackingError(stop_position_tracking_error)))))
                          ->Get();
        
            if (rv.finish_code() != RobotCommandFeedback::FinishCode::kOk) {
              std::cerr << "Error: Failed to conduct demo motion." << std::endl;
            }
        
            std::this_thread::sleep_for(1s);
          }
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
    //robot_ = rb::Robot<rb::y1_model::A>::Create("192.168.30.1:50051");
    robot_ = rb::Robot<rb::y1_model::A>::Create("192.168.1.6:50051");
    int speed_control;
    robot_->Connect();
    if (!robot_->IsPowerOn(kAll)){
        robot_->PowerOn(kAll);
        robot_->ServoOn(kAll);
        robot_->EnableControlManager();
    }
    stream = robot_->CreateCommandStream();
    rclcpp::init(argc, argv);
    std::cout << "init" << std::endl;

    // Enabling servos and control manager
    /*
    std::string servo = ".*";
    std::cout << "Checking servo status..." << std::endl;
    if (!robot_->IsServoOn(servo)) {
      std::cout << "Servo is currently OFF. Attempting to activate servo..." << std::endl;
      if (!robot_->ServoOn(servo)) {
        std::cerr << "Error: Failed to activate servo." << std::endl;
        return 1;
      }
      std::cout << "Servo activated successfully." << std::endl;
    } else {
      std::cout << "Servo is already ON." << std::endl;
    }
  
    const auto& control_manager_state = robot_->GetControlManagerState();
    if (control_manager_state.state == ControlManagerState::State::kMajorFault ||
        control_manager_state.state == ControlManagerState::State::kMinorFault) {
      std::cerr << "Warning: Detected a "
                << (control_manager_state.state == ControlManagerState::State::kMajorFault ? "Major" : "Minor")
                << " Fault in the Control Manager." << std::endl;
  
      std::cout << "Attempting to reset the fault..." << std::endl;
      if (!robot_->ResetFaultControlManager()) {
        std::cerr << "Error: Unable to reset the fault in the Control Manager." << std::endl;
        return 1;
      }
      std::cout << "Fault reset successfully." << std::endl;
    }
    std::cout << "Control Manager state is normal. No faults detected." << std::endl;
  
    std::cout << "Enabling the Control Manager..." << std::endl;
    if (!robot_->EnableControlManager()) {
      std::cerr << "Error: Failed to enable the Control Manager." << std::endl;
      return 1;
    }
    std::cout << "Control Manager enabled successfully." << std::endl;
  
    try {
      if (robot_->IsPowerOn("48v")) {
        robot_->SetToolFlangeOutputVoltage("right", 12);
      }
    } catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
    */
  
    robot_->SetParameter("default.acceleration_limit_scaling", "0.8");
    robot_->SetParameter("joint_position_command.cutoff_frequency", "5");
    robot_->SetParameter("cartesian_command.cutoff_frequency", "5");
    robot_->SetParameter("default.linear_acceleration_limit", "5");

    double minimum_time = 2.5;

    // Going to start position
    Eigen::Vector<double, 6> q_joint_torso;
    Eigen::Vector<double, 7> q_joint_right_arm;
    Eigen::Vector<double, 7> q_joint_left_arm;
    q_joint_torso.setZero();
    q_joint_right_arm.setZero();
    q_joint_left_arm.setZero();
  
    if (1) {
      std::cout << "joint position command example 1\n";
      q_joint_torso.setZero();
      q_joint_right_arm.setZero();
      q_joint_left_arm.setZero();
  
      q_joint_right_arm(1) = -60 * D2R;
      q_joint_left_arm(1) = 60 * D2R;
  
      // go to ready position
      auto rv =
          robot_
              ->SendCommand(RobotCommandBuilder().SetCommand(ComponentBasedCommandBuilder().SetBodyCommand(
                  BodyComponentBasedCommandBuilder()
                      .SetTorsoCommand(
                          JointPositionCommandBuilder().SetMinimumTime(minimum_time).SetPosition(q_joint_torso))
                      .SetRightArmCommand(
                          JointPositionCommandBuilder().SetMinimumTime(minimum_time).SetPosition(q_joint_right_arm))
                      .SetLeftArmCommand(
                          JointPositionCommandBuilder().SetMinimumTime(minimum_time).SetPosition(q_joint_left_arm)))))
              ->Get();
      std::this_thread::sleep_for(1s);
  
      if (rv.finish_code() != RobotCommandFeedback::FinishCode::kOk) {
        std::cerr << "Error: Failed to conduct demo motion." << std::endl;
      }
      std::this_thread::sleep_for(1s);
    }

    // Sending arm joint command
    if (0) {
        std::cout << "joint position command example 2\n";
    
        q_joint_torso << 0, 30, -60, 30, 0, 0;
        q_joint_torso *= D2R;
    
        q_joint_right_arm << -45, -30, 0, -90, 0, 45, 0;
        q_joint_right_arm *= D2R;
    
        q_joint_left_arm << -45, 30, 0, -90, 0, 45, 0;
        q_joint_left_arm *= D2R;
    
        Eigen::Vector<double, 20> q;
        q.block(0, 0, 6, 1) = q_joint_torso;
        q.block(6, 0, 7, 1) = q_joint_right_arm;
        q.block(6 + 7, 0, 7, 1) = q_joint_left_arm;
    
        auto rv = robot_
                      ->SendCommand(RobotCommandBuilder().SetCommand(ComponentBasedCommandBuilder().SetBodyCommand(
                          JointPositionCommandBuilder().SetPosition(q).SetMinimumTime(minimum_time))))
                      ->Get();
    
        if (rv.finish_code() != RobotCommandFeedback::FinishCode::kOk) {
          std::cerr << "Error: Failed to conduct demo motion." << std::endl;
        }
    
        std::this_thread::sleep_for(1s);
      }

    // Sending arm cartesian command
    double angular_velocity_limit = 3.141592 * 1.5;
    double linear_velocity_limit = 1.5;
    double acceleration_limit = 1.0;
    double stop_orientation_tracking_error = 1e-5;
    double stop_position_tracking_error = 1e-5;
  
    Eigen::Matrix<double, 4, 4> T_torso, T_right, T_left;
    T_torso.setIdentity();
    T_right.setIdentity();
    T_left.setIdentity();
  
    if (0) {
      std::cout << "Cartesian command example 1\n";
  
      T_torso.block(0, 0, 3, 3).setIdentity();
      T_torso.block(0, 3, 3, 1) << 0, 0, 1;
  
      T_right.block(0, 0, 3, 3) = math::SO3::RotY(-3.141592 / 4.);
      T_right.block(0, 3, 3, 1) << 0.5, -0.3, 1.0;
  
      T_left.block(0, 0, 3, 3) = math::SO3::RotY(-3.141592 / 4.);
      T_left.block(0, 3, 3, 1) << 0.5, 0.3, 1.0;
  
      auto rv = robot_
                    ->SendCommand(RobotCommandBuilder().SetCommand(ComponentBasedCommandBuilder().SetBodyCommand(
                        BodyComponentBasedCommandBuilder()
                            .SetTorsoCommand(CartesianCommandBuilder()
                                                 .AddTarget("base", "link_torso_5", T_torso, linear_velocity_limit,
                                                            angular_velocity_limit, acceleration_limit / 2)
                                                 .SetMinimumTime(minimum_time * 1)
                                                 .SetStopOrientationTrackingError(stop_orientation_tracking_error)
                                                 .SetStopPositionTrackingError(stop_position_tracking_error))
                            .SetRightArmCommand(CartesianCommandBuilder()
                                                    .AddTarget("base", "ee_right", T_right, linear_velocity_limit,
                                                               angular_velocity_limit, acceleration_limit / 2)
                                                    /* Need to be verified */
                                                    .AddJointPositionTarget("right_arm_2", -10 * M_PI / 180, 3.14, 6.28)
                                                    .SetMinimumTime(minimum_time * 3)
                                                    .SetStopOrientationTrackingError(stop_orientation_tracking_error)
                                                    .SetStopPositionTrackingError(stop_position_tracking_error))
                            .SetLeftArmCommand(CartesianCommandBuilder()
                                                   .AddTarget("base", "ee_left", T_left, linear_velocity_limit,
                                                              angular_velocity_limit, acceleration_limit / 2)
                                                   /* Need to be verified */
                                                   .AddJointPositionTarget("left_arm_2", 10 * M_PI / 180, 3.14, 6.28)
                                                   .SetMinimumTime(minimum_time * 3)
                                                   .SetStopOrientationTrackingError(stop_orientation_tracking_error)
                                                   .SetStopPositionTrackingError(stop_position_tracking_error)))))
                    ->Get();
  
      if (rv.finish_code() != RobotCommandFeedback::FinishCode::kOk) {
        std::cerr << "Error: Failed to conduct demo motion." << std::endl;
      }
  
      std::this_thread::sleep_for(1s);
    }

    // Enabled grav comp
    if (0) {
        std::cout << "gravity compensation example 2\n";
        
        GravityCompensationCommandBuilder torso_command;
        GravityCompensationCommandBuilder right_arm_command;
        GravityCompensationCommandBuilder left_arm_command;
    
        torso_command.SetCommandHeader(CommandHeaderBuilder().SetControlHoldTime(minimum_time)).SetOn(true);
        right_arm_command.SetCommandHeader(CommandHeaderBuilder().SetControlHoldTime(minimum_time)).SetOn(true);
        left_arm_command.SetCommandHeader(CommandHeaderBuilder().SetControlHoldTime(minimum_time)).SetOn(true);
    
        auto rv = robot_
                      ->SendCommand(RobotCommandBuilder().SetCommand(
                          ComponentBasedCommandBuilder().SetBodyCommand(BodyComponentBasedCommandBuilder()
                                                                            .SetTorsoCommand(torso_command)
                                                                            .SetRightArmCommand(right_arm_command)
                                                                            .SetLeftArmCommand(left_arm_command))))
                      ->Get();
    
        std::cout << "!!" << std::endl;
    
        if (rv.finish_code() != RobotCommandFeedback::FinishCode::kOk) {
          std::cout << "Error: Failed to conduct demo motion." << std::endl;
        }
    
        std::this_thread::sleep_for(1s);
      }

    // Only moving torso
    if (1) {
      std::cout << "Only torso example 1\n";
      
      GravityCompensationCommandBuilder left_arm_command2;
      GravityCompensationCommandBuilder right_arm_command2;

      left_arm_command2.SetCommandHeader(CommandHeaderBuilder().SetControlHoldTime(minimum_time)).SetOn(true);
      left_arm_command2.SetCommandHeader(CommandHeaderBuilder().SetControlHoldTime(minimum_time)).SetOn(true);

      T_torso.block(0, 0, 3, 3).setIdentity();
      T_torso.block(0, 3, 3, 1) << 0, 0, 1;
  
      auto rv = robot_
                    ->SendCommand(RobotCommandBuilder().SetCommand(ComponentBasedCommandBuilder().SetBodyCommand(
                        BodyComponentBasedCommandBuilder()
                            .SetTorsoCommand(CartesianCommandBuilder()
                            .AddTarget("base", "link_torso_5", T_torso, linear_velocity_limit,
                                       angular_velocity_limit, acceleration_limit / 2)
                            .SetMinimumTime(minimum_time * 1)
                            .SetStopOrientationTrackingError(stop_orientation_tracking_error)
                            .SetStopPositionTrackingError(stop_position_tracking_error))
                            .SetRightArmCommand(right_arm_command2)
                            .SetLeftArmCommand(left_arm_command2))))
                    ->Get();
  
      if (rv.finish_code() != RobotCommandFeedback::FinishCode::kOk) {
        std::cerr << "Error: Failed to conduct demo motion." << std::endl;
      }
  
      std::this_thread::sleep_for(1s);
    }

    // Starting node
    rclcpp::spin(std::make_shared<RBY1_Movement>(robot_, std::move(stream)));
    rclcpp::shutdown();

    return 0;
    }
