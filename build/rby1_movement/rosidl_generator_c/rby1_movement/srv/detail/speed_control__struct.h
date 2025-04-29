// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from rby1_movement:srv/SpeedControl.idl
// generated code does not contain a copyright notice

#ifndef RBY1_MOVEMENT__SRV__DETAIL__SPEED_CONTROL__STRUCT_H_
#define RBY1_MOVEMENT__SRV__DETAIL__SPEED_CONTROL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SpeedControl in the package rby1_movement.
typedef struct rby1_movement__srv__SpeedControl_Request
{
  double speed_input;
} rby1_movement__srv__SpeedControl_Request;

// Struct for a sequence of rby1_movement__srv__SpeedControl_Request.
typedef struct rby1_movement__srv__SpeedControl_Request__Sequence
{
  rby1_movement__srv__SpeedControl_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rby1_movement__srv__SpeedControl_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/SpeedControl in the package rby1_movement.
typedef struct rby1_movement__srv__SpeedControl_Response
{
  bool success;
} rby1_movement__srv__SpeedControl_Response;

// Struct for a sequence of rby1_movement__srv__SpeedControl_Response.
typedef struct rby1_movement__srv__SpeedControl_Response__Sequence
{
  rby1_movement__srv__SpeedControl_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} rby1_movement__srv__SpeedControl_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // RBY1_MOVEMENT__SRV__DETAIL__SPEED_CONTROL__STRUCT_H_
