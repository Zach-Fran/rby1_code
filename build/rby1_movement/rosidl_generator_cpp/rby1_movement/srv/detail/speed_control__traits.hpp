// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from rby1_movement:srv/SpeedControl.idl
// generated code does not contain a copyright notice

#ifndef RBY1_MOVEMENT__SRV__DETAIL__SPEED_CONTROL__TRAITS_HPP_
#define RBY1_MOVEMENT__SRV__DETAIL__SPEED_CONTROL__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "rby1_movement/srv/detail/speed_control__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace rby1_movement
{

namespace srv
{

inline void to_flow_style_yaml(
  const SpeedControl_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: speed_input
  {
    out << "speed_input: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_input, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SpeedControl_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: speed_input
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed_input: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_input, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SpeedControl_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace rby1_movement

namespace rosidl_generator_traits
{

[[deprecated("use rby1_movement::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rby1_movement::srv::SpeedControl_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  rby1_movement::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rby1_movement::srv::to_yaml() instead")]]
inline std::string to_yaml(const rby1_movement::srv::SpeedControl_Request & msg)
{
  return rby1_movement::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rby1_movement::srv::SpeedControl_Request>()
{
  return "rby1_movement::srv::SpeedControl_Request";
}

template<>
inline const char * name<rby1_movement::srv::SpeedControl_Request>()
{
  return "rby1_movement/srv/SpeedControl_Request";
}

template<>
struct has_fixed_size<rby1_movement::srv::SpeedControl_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rby1_movement::srv::SpeedControl_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rby1_movement::srv::SpeedControl_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rby1_movement
{

namespace srv
{

inline void to_flow_style_yaml(
  const SpeedControl_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const SpeedControl_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const SpeedControl_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace rby1_movement

namespace rosidl_generator_traits
{

[[deprecated("use rby1_movement::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const rby1_movement::srv::SpeedControl_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  rby1_movement::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use rby1_movement::srv::to_yaml() instead")]]
inline std::string to_yaml(const rby1_movement::srv::SpeedControl_Response & msg)
{
  return rby1_movement::srv::to_yaml(msg);
}

template<>
inline const char * data_type<rby1_movement::srv::SpeedControl_Response>()
{
  return "rby1_movement::srv::SpeedControl_Response";
}

template<>
inline const char * name<rby1_movement::srv::SpeedControl_Response>()
{
  return "rby1_movement/srv/SpeedControl_Response";
}

template<>
struct has_fixed_size<rby1_movement::srv::SpeedControl_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<rby1_movement::srv::SpeedControl_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<rby1_movement::srv::SpeedControl_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<rby1_movement::srv::SpeedControl>()
{
  return "rby1_movement::srv::SpeedControl";
}

template<>
inline const char * name<rby1_movement::srv::SpeedControl>()
{
  return "rby1_movement/srv/SpeedControl";
}

template<>
struct has_fixed_size<rby1_movement::srv::SpeedControl>
  : std::integral_constant<
    bool,
    has_fixed_size<rby1_movement::srv::SpeedControl_Request>::value &&
    has_fixed_size<rby1_movement::srv::SpeedControl_Response>::value
  >
{
};

template<>
struct has_bounded_size<rby1_movement::srv::SpeedControl>
  : std::integral_constant<
    bool,
    has_bounded_size<rby1_movement::srv::SpeedControl_Request>::value &&
    has_bounded_size<rby1_movement::srv::SpeedControl_Response>::value
  >
{
};

template<>
struct is_service<rby1_movement::srv::SpeedControl>
  : std::true_type
{
};

template<>
struct is_service_request<rby1_movement::srv::SpeedControl_Request>
  : std::true_type
{
};

template<>
struct is_service_response<rby1_movement::srv::SpeedControl_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // RBY1_MOVEMENT__SRV__DETAIL__SPEED_CONTROL__TRAITS_HPP_
