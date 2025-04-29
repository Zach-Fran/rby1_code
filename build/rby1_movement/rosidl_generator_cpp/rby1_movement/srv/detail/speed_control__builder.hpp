// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from rby1_movement:srv/SpeedControl.idl
// generated code does not contain a copyright notice

#ifndef RBY1_MOVEMENT__SRV__DETAIL__SPEED_CONTROL__BUILDER_HPP_
#define RBY1_MOVEMENT__SRV__DETAIL__SPEED_CONTROL__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "rby1_movement/srv/detail/speed_control__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace rby1_movement
{

namespace srv
{

namespace builder
{

class Init_SpeedControl_Request_speed_input
{
public:
  Init_SpeedControl_Request_speed_input()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rby1_movement::srv::SpeedControl_Request speed_input(::rby1_movement::srv::SpeedControl_Request::_speed_input_type arg)
  {
    msg_.speed_input = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rby1_movement::srv::SpeedControl_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rby1_movement::srv::SpeedControl_Request>()
{
  return rby1_movement::srv::builder::Init_SpeedControl_Request_speed_input();
}

}  // namespace rby1_movement


namespace rby1_movement
{

namespace srv
{

namespace builder
{

class Init_SpeedControl_Response_success
{
public:
  Init_SpeedControl_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::rby1_movement::srv::SpeedControl_Response success(::rby1_movement::srv::SpeedControl_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return std::move(msg_);
  }

private:
  ::rby1_movement::srv::SpeedControl_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::rby1_movement::srv::SpeedControl_Response>()
{
  return rby1_movement::srv::builder::Init_SpeedControl_Response_success();
}

}  // namespace rby1_movement

#endif  // RBY1_MOVEMENT__SRV__DETAIL__SPEED_CONTROL__BUILDER_HPP_
