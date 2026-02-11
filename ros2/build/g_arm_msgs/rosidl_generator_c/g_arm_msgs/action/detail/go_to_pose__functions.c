// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from g_arm_msgs:action/GoToPose.idl
// generated code does not contain a copyright notice
#include "g_arm_msgs/action/detail/go_to_pose__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `target`
#include "geometry_msgs/msg/detail/pose_stamped__functions.h"
// Member `planner_frame`
#include "rosidl_runtime_c/string_functions.h"

bool
g_arm_msgs__action__GoToPose_Goal__init(g_arm_msgs__action__GoToPose_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // target
  if (!geometry_msgs__msg__PoseStamped__init(&msg->target)) {
    g_arm_msgs__action__GoToPose_Goal__fini(msg);
    return false;
  }
  // pos_tolerance_m
  // ang_tolerance_rad
  // timeout_sec
  // allow_orientation
  // planner_frame
  if (!rosidl_runtime_c__String__init(&msg->planner_frame)) {
    g_arm_msgs__action__GoToPose_Goal__fini(msg);
    return false;
  }
  // speed_scale
  // max_joint_vel
  // max_joint_acc
  // electromagnet_on
  return true;
}

void
g_arm_msgs__action__GoToPose_Goal__fini(g_arm_msgs__action__GoToPose_Goal * msg)
{
  if (!msg) {
    return;
  }
  // target
  geometry_msgs__msg__PoseStamped__fini(&msg->target);
  // pos_tolerance_m
  // ang_tolerance_rad
  // timeout_sec
  // allow_orientation
  // planner_frame
  rosidl_runtime_c__String__fini(&msg->planner_frame);
  // speed_scale
  // max_joint_vel
  // max_joint_acc
  // electromagnet_on
}

bool
g_arm_msgs__action__GoToPose_Goal__are_equal(const g_arm_msgs__action__GoToPose_Goal * lhs, const g_arm_msgs__action__GoToPose_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // target
  if (!geometry_msgs__msg__PoseStamped__are_equal(
      &(lhs->target), &(rhs->target)))
  {
    return false;
  }
  // pos_tolerance_m
  if (lhs->pos_tolerance_m != rhs->pos_tolerance_m) {
    return false;
  }
  // ang_tolerance_rad
  if (lhs->ang_tolerance_rad != rhs->ang_tolerance_rad) {
    return false;
  }
  // timeout_sec
  if (lhs->timeout_sec != rhs->timeout_sec) {
    return false;
  }
  // allow_orientation
  if (lhs->allow_orientation != rhs->allow_orientation) {
    return false;
  }
  // planner_frame
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->planner_frame), &(rhs->planner_frame)))
  {
    return false;
  }
  // speed_scale
  if (lhs->speed_scale != rhs->speed_scale) {
    return false;
  }
  // max_joint_vel
  if (lhs->max_joint_vel != rhs->max_joint_vel) {
    return false;
  }
  // max_joint_acc
  if (lhs->max_joint_acc != rhs->max_joint_acc) {
    return false;
  }
  // electromagnet_on
  if (lhs->electromagnet_on != rhs->electromagnet_on) {
    return false;
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_Goal__copy(
  const g_arm_msgs__action__GoToPose_Goal * input,
  g_arm_msgs__action__GoToPose_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // target
  if (!geometry_msgs__msg__PoseStamped__copy(
      &(input->target), &(output->target)))
  {
    return false;
  }
  // pos_tolerance_m
  output->pos_tolerance_m = input->pos_tolerance_m;
  // ang_tolerance_rad
  output->ang_tolerance_rad = input->ang_tolerance_rad;
  // timeout_sec
  output->timeout_sec = input->timeout_sec;
  // allow_orientation
  output->allow_orientation = input->allow_orientation;
  // planner_frame
  if (!rosidl_runtime_c__String__copy(
      &(input->planner_frame), &(output->planner_frame)))
  {
    return false;
  }
  // speed_scale
  output->speed_scale = input->speed_scale;
  // max_joint_vel
  output->max_joint_vel = input->max_joint_vel;
  // max_joint_acc
  output->max_joint_acc = input->max_joint_acc;
  // electromagnet_on
  output->electromagnet_on = input->electromagnet_on;
  return true;
}

g_arm_msgs__action__GoToPose_Goal *
g_arm_msgs__action__GoToPose_Goal__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_Goal * msg = (g_arm_msgs__action__GoToPose_Goal *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g_arm_msgs__action__GoToPose_Goal));
  bool success = g_arm_msgs__action__GoToPose_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g_arm_msgs__action__GoToPose_Goal__destroy(g_arm_msgs__action__GoToPose_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g_arm_msgs__action__GoToPose_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g_arm_msgs__action__GoToPose_Goal__Sequence__init(g_arm_msgs__action__GoToPose_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_Goal * data = NULL;

  if (size) {
    data = (g_arm_msgs__action__GoToPose_Goal *)allocator.zero_allocate(size, sizeof(g_arm_msgs__action__GoToPose_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g_arm_msgs__action__GoToPose_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g_arm_msgs__action__GoToPose_Goal__fini(&data[i - 1]);
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
g_arm_msgs__action__GoToPose_Goal__Sequence__fini(g_arm_msgs__action__GoToPose_Goal__Sequence * array)
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
      g_arm_msgs__action__GoToPose_Goal__fini(&array->data[i]);
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

g_arm_msgs__action__GoToPose_Goal__Sequence *
g_arm_msgs__action__GoToPose_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_Goal__Sequence * array = (g_arm_msgs__action__GoToPose_Goal__Sequence *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g_arm_msgs__action__GoToPose_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g_arm_msgs__action__GoToPose_Goal__Sequence__destroy(g_arm_msgs__action__GoToPose_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g_arm_msgs__action__GoToPose_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g_arm_msgs__action__GoToPose_Goal__Sequence__are_equal(const g_arm_msgs__action__GoToPose_Goal__Sequence * lhs, const g_arm_msgs__action__GoToPose_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_Goal__Sequence__copy(
  const g_arm_msgs__action__GoToPose_Goal__Sequence * input,
  g_arm_msgs__action__GoToPose_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g_arm_msgs__action__GoToPose_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g_arm_msgs__action__GoToPose_Goal * data =
      (g_arm_msgs__action__GoToPose_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g_arm_msgs__action__GoToPose_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g_arm_msgs__action__GoToPose_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `final_joint_positions`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
g_arm_msgs__action__GoToPose_Result__init(g_arm_msgs__action__GoToPose_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // error_code
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    g_arm_msgs__action__GoToPose_Result__fini(msg);
    return false;
  }
  // final_pos_error_m
  // final_ang_error_rad
  // final_joint_positions
  if (!rosidl_runtime_c__double__Sequence__init(&msg->final_joint_positions, 0)) {
    g_arm_msgs__action__GoToPose_Result__fini(msg);
    return false;
  }
  return true;
}

void
g_arm_msgs__action__GoToPose_Result__fini(g_arm_msgs__action__GoToPose_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
  // error_code
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // final_pos_error_m
  // final_ang_error_rad
  // final_joint_positions
  rosidl_runtime_c__double__Sequence__fini(&msg->final_joint_positions);
}

bool
g_arm_msgs__action__GoToPose_Result__are_equal(const g_arm_msgs__action__GoToPose_Result * lhs, const g_arm_msgs__action__GoToPose_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // error_code
  if (lhs->error_code != rhs->error_code) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  // final_pos_error_m
  if (lhs->final_pos_error_m != rhs->final_pos_error_m) {
    return false;
  }
  // final_ang_error_rad
  if (lhs->final_ang_error_rad != rhs->final_ang_error_rad) {
    return false;
  }
  // final_joint_positions
  if (!rosidl_runtime_c__double__Sequence__are_equal(
      &(lhs->final_joint_positions), &(rhs->final_joint_positions)))
  {
    return false;
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_Result__copy(
  const g_arm_msgs__action__GoToPose_Result * input,
  g_arm_msgs__action__GoToPose_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // error_code
  output->error_code = input->error_code;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  // final_pos_error_m
  output->final_pos_error_m = input->final_pos_error_m;
  // final_ang_error_rad
  output->final_ang_error_rad = input->final_ang_error_rad;
  // final_joint_positions
  if (!rosidl_runtime_c__double__Sequence__copy(
      &(input->final_joint_positions), &(output->final_joint_positions)))
  {
    return false;
  }
  return true;
}

g_arm_msgs__action__GoToPose_Result *
g_arm_msgs__action__GoToPose_Result__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_Result * msg = (g_arm_msgs__action__GoToPose_Result *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g_arm_msgs__action__GoToPose_Result));
  bool success = g_arm_msgs__action__GoToPose_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g_arm_msgs__action__GoToPose_Result__destroy(g_arm_msgs__action__GoToPose_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g_arm_msgs__action__GoToPose_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g_arm_msgs__action__GoToPose_Result__Sequence__init(g_arm_msgs__action__GoToPose_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_Result * data = NULL;

  if (size) {
    data = (g_arm_msgs__action__GoToPose_Result *)allocator.zero_allocate(size, sizeof(g_arm_msgs__action__GoToPose_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g_arm_msgs__action__GoToPose_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g_arm_msgs__action__GoToPose_Result__fini(&data[i - 1]);
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
g_arm_msgs__action__GoToPose_Result__Sequence__fini(g_arm_msgs__action__GoToPose_Result__Sequence * array)
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
      g_arm_msgs__action__GoToPose_Result__fini(&array->data[i]);
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

g_arm_msgs__action__GoToPose_Result__Sequence *
g_arm_msgs__action__GoToPose_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_Result__Sequence * array = (g_arm_msgs__action__GoToPose_Result__Sequence *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g_arm_msgs__action__GoToPose_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g_arm_msgs__action__GoToPose_Result__Sequence__destroy(g_arm_msgs__action__GoToPose_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g_arm_msgs__action__GoToPose_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g_arm_msgs__action__GoToPose_Result__Sequence__are_equal(const g_arm_msgs__action__GoToPose_Result__Sequence * lhs, const g_arm_msgs__action__GoToPose_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_Result__Sequence__copy(
  const g_arm_msgs__action__GoToPose_Result__Sequence * input,
  g_arm_msgs__action__GoToPose_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g_arm_msgs__action__GoToPose_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g_arm_msgs__action__GoToPose_Result * data =
      (g_arm_msgs__action__GoToPose_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g_arm_msgs__action__GoToPose_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g_arm_msgs__action__GoToPose_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `state`
// Member `detail`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
g_arm_msgs__action__GoToPose_Feedback__init(g_arm_msgs__action__GoToPose_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__init(&msg->state)) {
    g_arm_msgs__action__GoToPose_Feedback__fini(msg);
    return false;
  }
  // pos_error_m
  // ang_error_rad
  // progress
  // detail
  if (!rosidl_runtime_c__String__init(&msg->detail)) {
    g_arm_msgs__action__GoToPose_Feedback__fini(msg);
    return false;
  }
  return true;
}

void
g_arm_msgs__action__GoToPose_Feedback__fini(g_arm_msgs__action__GoToPose_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // state
  rosidl_runtime_c__String__fini(&msg->state);
  // pos_error_m
  // ang_error_rad
  // progress
  // detail
  rosidl_runtime_c__String__fini(&msg->detail);
}

bool
g_arm_msgs__action__GoToPose_Feedback__are_equal(const g_arm_msgs__action__GoToPose_Feedback * lhs, const g_arm_msgs__action__GoToPose_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->state), &(rhs->state)))
  {
    return false;
  }
  // pos_error_m
  if (lhs->pos_error_m != rhs->pos_error_m) {
    return false;
  }
  // ang_error_rad
  if (lhs->ang_error_rad != rhs->ang_error_rad) {
    return false;
  }
  // progress
  if (lhs->progress != rhs->progress) {
    return false;
  }
  // detail
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->detail), &(rhs->detail)))
  {
    return false;
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_Feedback__copy(
  const g_arm_msgs__action__GoToPose_Feedback * input,
  g_arm_msgs__action__GoToPose_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // state
  if (!rosidl_runtime_c__String__copy(
      &(input->state), &(output->state)))
  {
    return false;
  }
  // pos_error_m
  output->pos_error_m = input->pos_error_m;
  // ang_error_rad
  output->ang_error_rad = input->ang_error_rad;
  // progress
  output->progress = input->progress;
  // detail
  if (!rosidl_runtime_c__String__copy(
      &(input->detail), &(output->detail)))
  {
    return false;
  }
  return true;
}

g_arm_msgs__action__GoToPose_Feedback *
g_arm_msgs__action__GoToPose_Feedback__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_Feedback * msg = (g_arm_msgs__action__GoToPose_Feedback *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g_arm_msgs__action__GoToPose_Feedback));
  bool success = g_arm_msgs__action__GoToPose_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g_arm_msgs__action__GoToPose_Feedback__destroy(g_arm_msgs__action__GoToPose_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g_arm_msgs__action__GoToPose_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g_arm_msgs__action__GoToPose_Feedback__Sequence__init(g_arm_msgs__action__GoToPose_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_Feedback * data = NULL;

  if (size) {
    data = (g_arm_msgs__action__GoToPose_Feedback *)allocator.zero_allocate(size, sizeof(g_arm_msgs__action__GoToPose_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g_arm_msgs__action__GoToPose_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g_arm_msgs__action__GoToPose_Feedback__fini(&data[i - 1]);
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
g_arm_msgs__action__GoToPose_Feedback__Sequence__fini(g_arm_msgs__action__GoToPose_Feedback__Sequence * array)
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
      g_arm_msgs__action__GoToPose_Feedback__fini(&array->data[i]);
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

g_arm_msgs__action__GoToPose_Feedback__Sequence *
g_arm_msgs__action__GoToPose_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_Feedback__Sequence * array = (g_arm_msgs__action__GoToPose_Feedback__Sequence *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g_arm_msgs__action__GoToPose_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g_arm_msgs__action__GoToPose_Feedback__Sequence__destroy(g_arm_msgs__action__GoToPose_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g_arm_msgs__action__GoToPose_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g_arm_msgs__action__GoToPose_Feedback__Sequence__are_equal(const g_arm_msgs__action__GoToPose_Feedback__Sequence * lhs, const g_arm_msgs__action__GoToPose_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_Feedback__Sequence__copy(
  const g_arm_msgs__action__GoToPose_Feedback__Sequence * input,
  g_arm_msgs__action__GoToPose_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g_arm_msgs__action__GoToPose_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g_arm_msgs__action__GoToPose_Feedback * data =
      (g_arm_msgs__action__GoToPose_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g_arm_msgs__action__GoToPose_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g_arm_msgs__action__GoToPose_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"

bool
g_arm_msgs__action__GoToPose_SendGoal_Request__init(g_arm_msgs__action__GoToPose_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    g_arm_msgs__action__GoToPose_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!g_arm_msgs__action__GoToPose_Goal__init(&msg->goal)) {
    g_arm_msgs__action__GoToPose_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
g_arm_msgs__action__GoToPose_SendGoal_Request__fini(g_arm_msgs__action__GoToPose_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  g_arm_msgs__action__GoToPose_Goal__fini(&msg->goal);
}

bool
g_arm_msgs__action__GoToPose_SendGoal_Request__are_equal(const g_arm_msgs__action__GoToPose_SendGoal_Request * lhs, const g_arm_msgs__action__GoToPose_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!g_arm_msgs__action__GoToPose_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_SendGoal_Request__copy(
  const g_arm_msgs__action__GoToPose_SendGoal_Request * input,
  g_arm_msgs__action__GoToPose_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!g_arm_msgs__action__GoToPose_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

g_arm_msgs__action__GoToPose_SendGoal_Request *
g_arm_msgs__action__GoToPose_SendGoal_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_SendGoal_Request * msg = (g_arm_msgs__action__GoToPose_SendGoal_Request *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g_arm_msgs__action__GoToPose_SendGoal_Request));
  bool success = g_arm_msgs__action__GoToPose_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g_arm_msgs__action__GoToPose_SendGoal_Request__destroy(g_arm_msgs__action__GoToPose_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g_arm_msgs__action__GoToPose_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__init(g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_SendGoal_Request * data = NULL;

  if (size) {
    data = (g_arm_msgs__action__GoToPose_SendGoal_Request *)allocator.zero_allocate(size, sizeof(g_arm_msgs__action__GoToPose_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g_arm_msgs__action__GoToPose_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g_arm_msgs__action__GoToPose_SendGoal_Request__fini(&data[i - 1]);
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
g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__fini(g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence * array)
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
      g_arm_msgs__action__GoToPose_SendGoal_Request__fini(&array->data[i]);
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

g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence *
g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence * array = (g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__destroy(g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__are_equal(const g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence * lhs, const g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__copy(
  const g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence * input,
  g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g_arm_msgs__action__GoToPose_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g_arm_msgs__action__GoToPose_SendGoal_Request * data =
      (g_arm_msgs__action__GoToPose_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g_arm_msgs__action__GoToPose_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g_arm_msgs__action__GoToPose_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
g_arm_msgs__action__GoToPose_SendGoal_Response__init(g_arm_msgs__action__GoToPose_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    g_arm_msgs__action__GoToPose_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
g_arm_msgs__action__GoToPose_SendGoal_Response__fini(g_arm_msgs__action__GoToPose_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
g_arm_msgs__action__GoToPose_SendGoal_Response__are_equal(const g_arm_msgs__action__GoToPose_SendGoal_Response * lhs, const g_arm_msgs__action__GoToPose_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_SendGoal_Response__copy(
  const g_arm_msgs__action__GoToPose_SendGoal_Response * input,
  g_arm_msgs__action__GoToPose_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

g_arm_msgs__action__GoToPose_SendGoal_Response *
g_arm_msgs__action__GoToPose_SendGoal_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_SendGoal_Response * msg = (g_arm_msgs__action__GoToPose_SendGoal_Response *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g_arm_msgs__action__GoToPose_SendGoal_Response));
  bool success = g_arm_msgs__action__GoToPose_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g_arm_msgs__action__GoToPose_SendGoal_Response__destroy(g_arm_msgs__action__GoToPose_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g_arm_msgs__action__GoToPose_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__init(g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_SendGoal_Response * data = NULL;

  if (size) {
    data = (g_arm_msgs__action__GoToPose_SendGoal_Response *)allocator.zero_allocate(size, sizeof(g_arm_msgs__action__GoToPose_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g_arm_msgs__action__GoToPose_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g_arm_msgs__action__GoToPose_SendGoal_Response__fini(&data[i - 1]);
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
g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__fini(g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence * array)
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
      g_arm_msgs__action__GoToPose_SendGoal_Response__fini(&array->data[i]);
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

g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence *
g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence * array = (g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__destroy(g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__are_equal(const g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence * lhs, const g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__copy(
  const g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence * input,
  g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g_arm_msgs__action__GoToPose_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g_arm_msgs__action__GoToPose_SendGoal_Response * data =
      (g_arm_msgs__action__GoToPose_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g_arm_msgs__action__GoToPose_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g_arm_msgs__action__GoToPose_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"

bool
g_arm_msgs__action__GoToPose_SendGoal_Event__init(g_arm_msgs__action__GoToPose_SendGoal_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    g_arm_msgs__action__GoToPose_SendGoal_Event__fini(msg);
    return false;
  }
  // request
  if (!g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__init(&msg->request, 0)) {
    g_arm_msgs__action__GoToPose_SendGoal_Event__fini(msg);
    return false;
  }
  // response
  if (!g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__init(&msg->response, 0)) {
    g_arm_msgs__action__GoToPose_SendGoal_Event__fini(msg);
    return false;
  }
  return true;
}

void
g_arm_msgs__action__GoToPose_SendGoal_Event__fini(g_arm_msgs__action__GoToPose_SendGoal_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__fini(&msg->request);
  // response
  g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__fini(&msg->response);
}

bool
g_arm_msgs__action__GoToPose_SendGoal_Event__are_equal(const g_arm_msgs__action__GoToPose_SendGoal_Event * lhs, const g_arm_msgs__action__GoToPose_SendGoal_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_SendGoal_Event__copy(
  const g_arm_msgs__action__GoToPose_SendGoal_Event * input,
  g_arm_msgs__action__GoToPose_SendGoal_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

g_arm_msgs__action__GoToPose_SendGoal_Event *
g_arm_msgs__action__GoToPose_SendGoal_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_SendGoal_Event * msg = (g_arm_msgs__action__GoToPose_SendGoal_Event *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_SendGoal_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g_arm_msgs__action__GoToPose_SendGoal_Event));
  bool success = g_arm_msgs__action__GoToPose_SendGoal_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g_arm_msgs__action__GoToPose_SendGoal_Event__destroy(g_arm_msgs__action__GoToPose_SendGoal_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g_arm_msgs__action__GoToPose_SendGoal_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence__init(g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_SendGoal_Event * data = NULL;

  if (size) {
    data = (g_arm_msgs__action__GoToPose_SendGoal_Event *)allocator.zero_allocate(size, sizeof(g_arm_msgs__action__GoToPose_SendGoal_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g_arm_msgs__action__GoToPose_SendGoal_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g_arm_msgs__action__GoToPose_SendGoal_Event__fini(&data[i - 1]);
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
g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence__fini(g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence * array)
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
      g_arm_msgs__action__GoToPose_SendGoal_Event__fini(&array->data[i]);
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

g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence *
g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence * array = (g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence__destroy(g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence__are_equal(const g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence * lhs, const g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_SendGoal_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence__copy(
  const g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence * input,
  g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g_arm_msgs__action__GoToPose_SendGoal_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g_arm_msgs__action__GoToPose_SendGoal_Event * data =
      (g_arm_msgs__action__GoToPose_SendGoal_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g_arm_msgs__action__GoToPose_SendGoal_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g_arm_msgs__action__GoToPose_SendGoal_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_SendGoal_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
g_arm_msgs__action__GoToPose_GetResult_Request__init(g_arm_msgs__action__GoToPose_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    g_arm_msgs__action__GoToPose_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
g_arm_msgs__action__GoToPose_GetResult_Request__fini(g_arm_msgs__action__GoToPose_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
g_arm_msgs__action__GoToPose_GetResult_Request__are_equal(const g_arm_msgs__action__GoToPose_GetResult_Request * lhs, const g_arm_msgs__action__GoToPose_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_GetResult_Request__copy(
  const g_arm_msgs__action__GoToPose_GetResult_Request * input,
  g_arm_msgs__action__GoToPose_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

g_arm_msgs__action__GoToPose_GetResult_Request *
g_arm_msgs__action__GoToPose_GetResult_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_GetResult_Request * msg = (g_arm_msgs__action__GoToPose_GetResult_Request *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g_arm_msgs__action__GoToPose_GetResult_Request));
  bool success = g_arm_msgs__action__GoToPose_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g_arm_msgs__action__GoToPose_GetResult_Request__destroy(g_arm_msgs__action__GoToPose_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g_arm_msgs__action__GoToPose_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__init(g_arm_msgs__action__GoToPose_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_GetResult_Request * data = NULL;

  if (size) {
    data = (g_arm_msgs__action__GoToPose_GetResult_Request *)allocator.zero_allocate(size, sizeof(g_arm_msgs__action__GoToPose_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g_arm_msgs__action__GoToPose_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g_arm_msgs__action__GoToPose_GetResult_Request__fini(&data[i - 1]);
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
g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__fini(g_arm_msgs__action__GoToPose_GetResult_Request__Sequence * array)
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
      g_arm_msgs__action__GoToPose_GetResult_Request__fini(&array->data[i]);
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

g_arm_msgs__action__GoToPose_GetResult_Request__Sequence *
g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_GetResult_Request__Sequence * array = (g_arm_msgs__action__GoToPose_GetResult_Request__Sequence *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__destroy(g_arm_msgs__action__GoToPose_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__are_equal(const g_arm_msgs__action__GoToPose_GetResult_Request__Sequence * lhs, const g_arm_msgs__action__GoToPose_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__copy(
  const g_arm_msgs__action__GoToPose_GetResult_Request__Sequence * input,
  g_arm_msgs__action__GoToPose_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g_arm_msgs__action__GoToPose_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g_arm_msgs__action__GoToPose_GetResult_Request * data =
      (g_arm_msgs__action__GoToPose_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g_arm_msgs__action__GoToPose_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g_arm_msgs__action__GoToPose_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"

bool
g_arm_msgs__action__GoToPose_GetResult_Response__init(g_arm_msgs__action__GoToPose_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!g_arm_msgs__action__GoToPose_Result__init(&msg->result)) {
    g_arm_msgs__action__GoToPose_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
g_arm_msgs__action__GoToPose_GetResult_Response__fini(g_arm_msgs__action__GoToPose_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  g_arm_msgs__action__GoToPose_Result__fini(&msg->result);
}

bool
g_arm_msgs__action__GoToPose_GetResult_Response__are_equal(const g_arm_msgs__action__GoToPose_GetResult_Response * lhs, const g_arm_msgs__action__GoToPose_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!g_arm_msgs__action__GoToPose_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_GetResult_Response__copy(
  const g_arm_msgs__action__GoToPose_GetResult_Response * input,
  g_arm_msgs__action__GoToPose_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!g_arm_msgs__action__GoToPose_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

g_arm_msgs__action__GoToPose_GetResult_Response *
g_arm_msgs__action__GoToPose_GetResult_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_GetResult_Response * msg = (g_arm_msgs__action__GoToPose_GetResult_Response *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g_arm_msgs__action__GoToPose_GetResult_Response));
  bool success = g_arm_msgs__action__GoToPose_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g_arm_msgs__action__GoToPose_GetResult_Response__destroy(g_arm_msgs__action__GoToPose_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g_arm_msgs__action__GoToPose_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__init(g_arm_msgs__action__GoToPose_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_GetResult_Response * data = NULL;

  if (size) {
    data = (g_arm_msgs__action__GoToPose_GetResult_Response *)allocator.zero_allocate(size, sizeof(g_arm_msgs__action__GoToPose_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g_arm_msgs__action__GoToPose_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g_arm_msgs__action__GoToPose_GetResult_Response__fini(&data[i - 1]);
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
g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__fini(g_arm_msgs__action__GoToPose_GetResult_Response__Sequence * array)
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
      g_arm_msgs__action__GoToPose_GetResult_Response__fini(&array->data[i]);
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

g_arm_msgs__action__GoToPose_GetResult_Response__Sequence *
g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_GetResult_Response__Sequence * array = (g_arm_msgs__action__GoToPose_GetResult_Response__Sequence *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__destroy(g_arm_msgs__action__GoToPose_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__are_equal(const g_arm_msgs__action__GoToPose_GetResult_Response__Sequence * lhs, const g_arm_msgs__action__GoToPose_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__copy(
  const g_arm_msgs__action__GoToPose_GetResult_Response__Sequence * input,
  g_arm_msgs__action__GoToPose_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g_arm_msgs__action__GoToPose_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g_arm_msgs__action__GoToPose_GetResult_Response * data =
      (g_arm_msgs__action__GoToPose_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g_arm_msgs__action__GoToPose_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g_arm_msgs__action__GoToPose_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
// already included above
// #include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"

bool
g_arm_msgs__action__GoToPose_GetResult_Event__init(g_arm_msgs__action__GoToPose_GetResult_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    g_arm_msgs__action__GoToPose_GetResult_Event__fini(msg);
    return false;
  }
  // request
  if (!g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__init(&msg->request, 0)) {
    g_arm_msgs__action__GoToPose_GetResult_Event__fini(msg);
    return false;
  }
  // response
  if (!g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__init(&msg->response, 0)) {
    g_arm_msgs__action__GoToPose_GetResult_Event__fini(msg);
    return false;
  }
  return true;
}

void
g_arm_msgs__action__GoToPose_GetResult_Event__fini(g_arm_msgs__action__GoToPose_GetResult_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__fini(&msg->request);
  // response
  g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__fini(&msg->response);
}

bool
g_arm_msgs__action__GoToPose_GetResult_Event__are_equal(const g_arm_msgs__action__GoToPose_GetResult_Event * lhs, const g_arm_msgs__action__GoToPose_GetResult_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_GetResult_Event__copy(
  const g_arm_msgs__action__GoToPose_GetResult_Event * input,
  g_arm_msgs__action__GoToPose_GetResult_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

g_arm_msgs__action__GoToPose_GetResult_Event *
g_arm_msgs__action__GoToPose_GetResult_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_GetResult_Event * msg = (g_arm_msgs__action__GoToPose_GetResult_Event *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_GetResult_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g_arm_msgs__action__GoToPose_GetResult_Event));
  bool success = g_arm_msgs__action__GoToPose_GetResult_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g_arm_msgs__action__GoToPose_GetResult_Event__destroy(g_arm_msgs__action__GoToPose_GetResult_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g_arm_msgs__action__GoToPose_GetResult_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g_arm_msgs__action__GoToPose_GetResult_Event__Sequence__init(g_arm_msgs__action__GoToPose_GetResult_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_GetResult_Event * data = NULL;

  if (size) {
    data = (g_arm_msgs__action__GoToPose_GetResult_Event *)allocator.zero_allocate(size, sizeof(g_arm_msgs__action__GoToPose_GetResult_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g_arm_msgs__action__GoToPose_GetResult_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g_arm_msgs__action__GoToPose_GetResult_Event__fini(&data[i - 1]);
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
g_arm_msgs__action__GoToPose_GetResult_Event__Sequence__fini(g_arm_msgs__action__GoToPose_GetResult_Event__Sequence * array)
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
      g_arm_msgs__action__GoToPose_GetResult_Event__fini(&array->data[i]);
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

g_arm_msgs__action__GoToPose_GetResult_Event__Sequence *
g_arm_msgs__action__GoToPose_GetResult_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_GetResult_Event__Sequence * array = (g_arm_msgs__action__GoToPose_GetResult_Event__Sequence *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_GetResult_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g_arm_msgs__action__GoToPose_GetResult_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g_arm_msgs__action__GoToPose_GetResult_Event__Sequence__destroy(g_arm_msgs__action__GoToPose_GetResult_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g_arm_msgs__action__GoToPose_GetResult_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g_arm_msgs__action__GoToPose_GetResult_Event__Sequence__are_equal(const g_arm_msgs__action__GoToPose_GetResult_Event__Sequence * lhs, const g_arm_msgs__action__GoToPose_GetResult_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_GetResult_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_GetResult_Event__Sequence__copy(
  const g_arm_msgs__action__GoToPose_GetResult_Event__Sequence * input,
  g_arm_msgs__action__GoToPose_GetResult_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g_arm_msgs__action__GoToPose_GetResult_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g_arm_msgs__action__GoToPose_GetResult_Event * data =
      (g_arm_msgs__action__GoToPose_GetResult_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g_arm_msgs__action__GoToPose_GetResult_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g_arm_msgs__action__GoToPose_GetResult_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_GetResult_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"

bool
g_arm_msgs__action__GoToPose_FeedbackMessage__init(g_arm_msgs__action__GoToPose_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    g_arm_msgs__action__GoToPose_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!g_arm_msgs__action__GoToPose_Feedback__init(&msg->feedback)) {
    g_arm_msgs__action__GoToPose_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
g_arm_msgs__action__GoToPose_FeedbackMessage__fini(g_arm_msgs__action__GoToPose_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  g_arm_msgs__action__GoToPose_Feedback__fini(&msg->feedback);
}

bool
g_arm_msgs__action__GoToPose_FeedbackMessage__are_equal(const g_arm_msgs__action__GoToPose_FeedbackMessage * lhs, const g_arm_msgs__action__GoToPose_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!g_arm_msgs__action__GoToPose_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_FeedbackMessage__copy(
  const g_arm_msgs__action__GoToPose_FeedbackMessage * input,
  g_arm_msgs__action__GoToPose_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!g_arm_msgs__action__GoToPose_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

g_arm_msgs__action__GoToPose_FeedbackMessage *
g_arm_msgs__action__GoToPose_FeedbackMessage__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_FeedbackMessage * msg = (g_arm_msgs__action__GoToPose_FeedbackMessage *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(g_arm_msgs__action__GoToPose_FeedbackMessage));
  bool success = g_arm_msgs__action__GoToPose_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
g_arm_msgs__action__GoToPose_FeedbackMessage__destroy(g_arm_msgs__action__GoToPose_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    g_arm_msgs__action__GoToPose_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence__init(g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_FeedbackMessage * data = NULL;

  if (size) {
    data = (g_arm_msgs__action__GoToPose_FeedbackMessage *)allocator.zero_allocate(size, sizeof(g_arm_msgs__action__GoToPose_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = g_arm_msgs__action__GoToPose_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        g_arm_msgs__action__GoToPose_FeedbackMessage__fini(&data[i - 1]);
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
g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence__fini(g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence * array)
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
      g_arm_msgs__action__GoToPose_FeedbackMessage__fini(&array->data[i]);
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

g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence *
g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence * array = (g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence *)allocator.allocate(sizeof(g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence__destroy(g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence__are_equal(const g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence * lhs, const g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence__copy(
  const g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence * input,
  g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(g_arm_msgs__action__GoToPose_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    g_arm_msgs__action__GoToPose_FeedbackMessage * data =
      (g_arm_msgs__action__GoToPose_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!g_arm_msgs__action__GoToPose_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          g_arm_msgs__action__GoToPose_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!g_arm_msgs__action__GoToPose_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
