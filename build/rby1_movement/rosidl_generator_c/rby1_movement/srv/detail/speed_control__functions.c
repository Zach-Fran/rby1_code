// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from rby1_movement:srv/SpeedControl.idl
// generated code does not contain a copyright notice
#include "rby1_movement/srv/detail/speed_control__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
rby1_movement__srv__SpeedControl_Request__init(rby1_movement__srv__SpeedControl_Request * msg)
{
  if (!msg) {
    return false;
  }
  // speed_input
  return true;
}

void
rby1_movement__srv__SpeedControl_Request__fini(rby1_movement__srv__SpeedControl_Request * msg)
{
  if (!msg) {
    return;
  }
  // speed_input
}

bool
rby1_movement__srv__SpeedControl_Request__are_equal(const rby1_movement__srv__SpeedControl_Request * lhs, const rby1_movement__srv__SpeedControl_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // speed_input
  if (lhs->speed_input != rhs->speed_input) {
    return false;
  }
  return true;
}

bool
rby1_movement__srv__SpeedControl_Request__copy(
  const rby1_movement__srv__SpeedControl_Request * input,
  rby1_movement__srv__SpeedControl_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // speed_input
  output->speed_input = input->speed_input;
  return true;
}

rby1_movement__srv__SpeedControl_Request *
rby1_movement__srv__SpeedControl_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rby1_movement__srv__SpeedControl_Request * msg = (rby1_movement__srv__SpeedControl_Request *)allocator.allocate(sizeof(rby1_movement__srv__SpeedControl_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rby1_movement__srv__SpeedControl_Request));
  bool success = rby1_movement__srv__SpeedControl_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rby1_movement__srv__SpeedControl_Request__destroy(rby1_movement__srv__SpeedControl_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rby1_movement__srv__SpeedControl_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rby1_movement__srv__SpeedControl_Request__Sequence__init(rby1_movement__srv__SpeedControl_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rby1_movement__srv__SpeedControl_Request * data = NULL;

  if (size) {
    data = (rby1_movement__srv__SpeedControl_Request *)allocator.zero_allocate(size, sizeof(rby1_movement__srv__SpeedControl_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rby1_movement__srv__SpeedControl_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rby1_movement__srv__SpeedControl_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rby1_movement__srv__SpeedControl_Request__Sequence__fini(rby1_movement__srv__SpeedControl_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rby1_movement__srv__SpeedControl_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rby1_movement__srv__SpeedControl_Request__Sequence *
rby1_movement__srv__SpeedControl_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rby1_movement__srv__SpeedControl_Request__Sequence * array = (rby1_movement__srv__SpeedControl_Request__Sequence *)allocator.allocate(sizeof(rby1_movement__srv__SpeedControl_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rby1_movement__srv__SpeedControl_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rby1_movement__srv__SpeedControl_Request__Sequence__destroy(rby1_movement__srv__SpeedControl_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rby1_movement__srv__SpeedControl_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rby1_movement__srv__SpeedControl_Request__Sequence__are_equal(const rby1_movement__srv__SpeedControl_Request__Sequence * lhs, const rby1_movement__srv__SpeedControl_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rby1_movement__srv__SpeedControl_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rby1_movement__srv__SpeedControl_Request__Sequence__copy(
  const rby1_movement__srv__SpeedControl_Request__Sequence * input,
  rby1_movement__srv__SpeedControl_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rby1_movement__srv__SpeedControl_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rby1_movement__srv__SpeedControl_Request * data =
      (rby1_movement__srv__SpeedControl_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rby1_movement__srv__SpeedControl_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rby1_movement__srv__SpeedControl_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rby1_movement__srv__SpeedControl_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
rby1_movement__srv__SpeedControl_Response__init(rby1_movement__srv__SpeedControl_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  return true;
}

void
rby1_movement__srv__SpeedControl_Response__fini(rby1_movement__srv__SpeedControl_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
}

bool
rby1_movement__srv__SpeedControl_Response__are_equal(const rby1_movement__srv__SpeedControl_Response * lhs, const rby1_movement__srv__SpeedControl_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  return true;
}

bool
rby1_movement__srv__SpeedControl_Response__copy(
  const rby1_movement__srv__SpeedControl_Response * input,
  rby1_movement__srv__SpeedControl_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  return true;
}

rby1_movement__srv__SpeedControl_Response *
rby1_movement__srv__SpeedControl_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rby1_movement__srv__SpeedControl_Response * msg = (rby1_movement__srv__SpeedControl_Response *)allocator.allocate(sizeof(rby1_movement__srv__SpeedControl_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(rby1_movement__srv__SpeedControl_Response));
  bool success = rby1_movement__srv__SpeedControl_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
rby1_movement__srv__SpeedControl_Response__destroy(rby1_movement__srv__SpeedControl_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    rby1_movement__srv__SpeedControl_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
rby1_movement__srv__SpeedControl_Response__Sequence__init(rby1_movement__srv__SpeedControl_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rby1_movement__srv__SpeedControl_Response * data = NULL;

  if (size) {
    data = (rby1_movement__srv__SpeedControl_Response *)allocator.zero_allocate(size, sizeof(rby1_movement__srv__SpeedControl_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = rby1_movement__srv__SpeedControl_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        rby1_movement__srv__SpeedControl_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
rby1_movement__srv__SpeedControl_Response__Sequence__fini(rby1_movement__srv__SpeedControl_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      rby1_movement__srv__SpeedControl_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

rby1_movement__srv__SpeedControl_Response__Sequence *
rby1_movement__srv__SpeedControl_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  rby1_movement__srv__SpeedControl_Response__Sequence * array = (rby1_movement__srv__SpeedControl_Response__Sequence *)allocator.allocate(sizeof(rby1_movement__srv__SpeedControl_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = rby1_movement__srv__SpeedControl_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
rby1_movement__srv__SpeedControl_Response__Sequence__destroy(rby1_movement__srv__SpeedControl_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    rby1_movement__srv__SpeedControl_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
rby1_movement__srv__SpeedControl_Response__Sequence__are_equal(const rby1_movement__srv__SpeedControl_Response__Sequence * lhs, const rby1_movement__srv__SpeedControl_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!rby1_movement__srv__SpeedControl_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
rby1_movement__srv__SpeedControl_Response__Sequence__copy(
  const rby1_movement__srv__SpeedControl_Response__Sequence * input,
  rby1_movement__srv__SpeedControl_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(rby1_movement__srv__SpeedControl_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    rby1_movement__srv__SpeedControl_Response * data =
      (rby1_movement__srv__SpeedControl_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!rby1_movement__srv__SpeedControl_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          rby1_movement__srv__SpeedControl_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!rby1_movement__srv__SpeedControl_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
