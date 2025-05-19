#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joint_state.hpp"
#include "rby1-sdk/robot.h"
#include "rby1-sdk/model.h"

using namespace rb;

class RobotStatePublisher : public rclcpp::Node {
public:
    RobotStatePublisher(std::shared_ptr<rb::Robot<rb::y1_model::A>> robot, 
        std::unique_ptr<rb::RobotCommandStreamHandler<rb::y1_model::A>> stream) : 
        Node("rby1_state_publisher"),
        robot(robot),
        stream(std::move(stream))
        {
        std::cout << robot->GetRobotInfo().robot_version << std::endl;
        /*
        robot->StartStateUpdate(
            [](const auto& state, const auto& control_manager) {
              std::cout << "Timestamp: " << state.timestamp.tv_sec << ".";
              std::cout << std::setw(9) << std::setfill('0') << state.timestamp.tv_nsec << std::endl;
              std::cout << "  Position: " << state.position.transpose() << std::endl;
              std::cout << "Control Manager State: " << rb::to_string(control_manager.state) << std::endl;
              
            },
            100);
      */
        //std::this_thread::sleep_for(1s);
      
        robot->PowerOn(".*");


        
        joint_pub_ = create_publisher<sensor_msgs::msg::JointState>("joint_states", 10);
        


        robot->StartStateUpdate(
            [this](const auto& state, const auto& control_manager) {
                auto msg = std::make_unique<sensor_msgs::msg::JointState>();
                msg->header.stamp = now();
                
                // Populate joint data
                const std::array<std::string, 24> JOINT_NAMES = {  // Change 6 to your joint count
                    "left_wheel", "right_wheel", "torso_0", 
                    "torso_1", "torso_2", "torso_3",
                    "torso_4", "torso_5", "right_arm_0",
                    "right_arm_1", "right_arm_2", "right_arm_3",
                    "right_arm_4", "right_arm_5", "right_arm_6",
                    "left_arm_0", "left_arm_1", "left_arm_2", 
                    "left_arm_3", "left_arm_4", "left_arm_5", 
                    "left_arm_6", "head_0", "head_1"
                };
                const std::array<std::string, 4> GRIPPER_JOINT_NAMES = {  // Change 6 to your joint count
                    "gripper_finger_l1", "gripper_finger_l2",
                    "gripper_finger_r1", "gripper_finger_r2"
                };
                for (std::size_t i =0; i <  state.joint_states.size(); i++) {
                    //msg->name.push_back("joint_" + std::to_string(state.joint_states[i]));
                    msg->name.push_back(JOINT_NAMES[i]);
                    msg->position.push_back(state.joint_states[i].position);
                    msg->velocity.push_back(state.joint_states[i].velocity);
                    //msg->effort.push_back(state.joint_states[i].effort);
                }
                for (std::size_t j =0; j <  GRIPPER_JOINT_NAMES.size(); j++) {
                    //msg->name.push_back("joint_" + std::to_string(state.joint_states[i]));
                    msg->name.push_back(GRIPPER_JOINT_NAMES[j]);
                    msg->position.push_back(0);
                    msg->velocity.push_back(0);
                    //msg->effort.push_back(state.joint_states[i].effort);
                }

                joint_pub_->publish(std::move(msg));
            }, 100);
    
    }

private:
    std::shared_ptr<rb::Robot<rb::y1_model::A>> robot;
    std::unique_ptr<rb::RobotCommandStreamHandler<rb::y1_model::A>> stream;
    std::string robot_ip_ = "192.168.30.1"; // Configure via parameters
    rclcpp::Publisher<sensor_msgs::msg::JointState>::SharedPtr joint_pub_;
};

int main(int argc, char** argv) {
    std::shared_ptr<rb::Robot<rb::y1_model::A>> robot;
    std::unique_ptr<rb::RobotCommandStreamHandler<rb::y1_model::A>> stream;
    robot = rb::Robot<rb::y1_model::A>::Create("192.168.30.1:50051");
    robot->Connect();
    stream = robot->CreateCommandStream();
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RobotStatePublisher>(robot, std::move(stream)));
    rclcpp::shutdown();
    return 0;
}