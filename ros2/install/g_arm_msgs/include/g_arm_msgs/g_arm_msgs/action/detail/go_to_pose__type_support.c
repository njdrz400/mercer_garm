// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from g_arm_msgs:action/GoToPose.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"
#include "g_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "g_arm_msgs/action/detail/go_to_pose__functions.h"
#include "g_arm_msgs/action/detail/go_to_pose__struct.h"


// Include directives for member types
// Member `target`
#include "geometry_msgs/msg/pose_stamped.h"
// Member `target`
#include "geometry_msgs/msg/detail/pose_stamped__rosidl_typesupport_introspection_c.h"
// Member `planner_frame`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  g_arm_msgs__action__GoToPose_Goal__init(message_memory);
}

void g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_fini_function(void * message_memory)
{
  g_arm_msgs__action__GoToPose_Goal__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_message_member_array[10] = {
  {
    "target",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Goal, target),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pos_tolerance_m",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Goal, pos_tolerance_m),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ang_tolerance_rad",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Goal, ang_tolerance_rad),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "timeout_sec",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Goal, timeout_sec),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "allow_orientation",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Goal, allow_orientation),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "planner_frame",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Goal, planner_frame),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "speed_scale",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Goal, speed_scale),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "max_joint_vel",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Goal, max_joint_vel),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "max_joint_acc",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Goal, max_joint_acc),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "electromagnet_on",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Goal, electromagnet_on),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_message_members = {
  "g_arm_msgs__action",  // message namespace
  "GoToPose_Goal",  // message name
  10,  // number of fields
  sizeof(g_arm_msgs__action__GoToPose_Goal),
  false,  // has_any_key_member_
  g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_message_member_array,  // message members
  g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_init_function,  // function to initialize message memory (memory has to be allocated)
  g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_message_type_support_handle = {
  0,
  &g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_message_members,
  get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_Goal__get_type_hash,
  &g_arm_msgs__action__GoToPose_Goal__get_type_description,
  &g_arm_msgs__action__GoToPose_Goal__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_Goal)() {
  g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, PoseStamped)();
  if (!g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_message_type_support_handle.typesupport_identifier) {
    g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &g_arm_msgs__action__GoToPose_Goal__rosidl_typesupport_introspection_c__GoToPose_Goal_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"
// already included above
// #include "g_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.h"


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `final_joint_positions`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__GoToPose_Result_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  g_arm_msgs__action__GoToPose_Result__init(message_memory);
}

void g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__GoToPose_Result_fini_function(void * message_memory)
{
  g_arm_msgs__action__GoToPose_Result__fini(message_memory);
}

size_t g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__size_function__GoToPose_Result__final_joint_positions(
  const void * untyped_member)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return member->size;
}

const void * g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__get_const_function__GoToPose_Result__final_joint_positions(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__double__Sequence * member =
    (const rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void * g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__get_function__GoToPose_Result__final_joint_positions(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  return &member->data[index];
}

void g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__fetch_function__GoToPose_Result__final_joint_positions(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const double * item =
    ((const double *)
    g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__get_const_function__GoToPose_Result__final_joint_positions(untyped_member, index));
  double * value =
    (double *)(untyped_value);
  *value = *item;
}

void g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__assign_function__GoToPose_Result__final_joint_positions(
  void * untyped_member, size_t index, const void * untyped_value)
{
  double * item =
    ((double *)
    g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__get_function__GoToPose_Result__final_joint_positions(untyped_member, index));
  const double * value =
    (const double *)(untyped_value);
  *item = *value;
}

bool g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__resize_function__GoToPose_Result__final_joint_positions(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__double__Sequence * member =
    (rosidl_runtime_c__double__Sequence *)(untyped_member);
  rosidl_runtime_c__double__Sequence__fini(member);
  return rosidl_runtime_c__double__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__GoToPose_Result_message_member_array[6] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Result, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "error_code",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Result, error_code),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Result, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "final_pos_error_m",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Result, final_pos_error_m),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "final_ang_error_rad",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Result, final_ang_error_rad),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "final_joint_positions",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Result, final_joint_positions),  // bytes offset in struct
    NULL,  // default value
    g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__size_function__GoToPose_Result__final_joint_positions,  // size() function pointer
    g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__get_const_function__GoToPose_Result__final_joint_positions,  // get_const(index) function pointer
    g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__get_function__GoToPose_Result__final_joint_positions,  // get(index) function pointer
    g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__fetch_function__GoToPose_Result__final_joint_positions,  // fetch(index, &value) function pointer
    g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__assign_function__GoToPose_Result__final_joint_positions,  // assign(index, value) function pointer
    g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__resize_function__GoToPose_Result__final_joint_positions  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__GoToPose_Result_message_members = {
  "g_arm_msgs__action",  // message namespace
  "GoToPose_Result",  // message name
  6,  // number of fields
  sizeof(g_arm_msgs__action__GoToPose_Result),
  false,  // has_any_key_member_
  g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__GoToPose_Result_message_member_array,  // message members
  g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__GoToPose_Result_init_function,  // function to initialize message memory (memory has to be allocated)
  g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__GoToPose_Result_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__GoToPose_Result_message_type_support_handle = {
  0,
  &g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__GoToPose_Result_message_members,
  get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_Result__get_type_hash,
  &g_arm_msgs__action__GoToPose_Result__get_type_description,
  &g_arm_msgs__action__GoToPose_Result__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_Result)() {
  if (!g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__GoToPose_Result_message_type_support_handle.typesupport_identifier) {
    g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__GoToPose_Result_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &g_arm_msgs__action__GoToPose_Result__rosidl_typesupport_introspection_c__GoToPose_Result_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"
// already included above
// #include "g_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.h"


// Include directives for member types
// Member `state`
// Member `detail`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void g_arm_msgs__action__GoToPose_Feedback__rosidl_typesupport_introspection_c__GoToPose_Feedback_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  g_arm_msgs__action__GoToPose_Feedback__init(message_memory);
}

void g_arm_msgs__action__GoToPose_Feedback__rosidl_typesupport_introspection_c__GoToPose_Feedback_fini_function(void * message_memory)
{
  g_arm_msgs__action__GoToPose_Feedback__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember g_arm_msgs__action__GoToPose_Feedback__rosidl_typesupport_introspection_c__GoToPose_Feedback_message_member_array[5] = {
  {
    "state",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Feedback, state),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pos_error_m",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Feedback, pos_error_m),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "ang_error_rad",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Feedback, ang_error_rad),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "progress",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Feedback, progress),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "detail",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_Feedback, detail),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers g_arm_msgs__action__GoToPose_Feedback__rosidl_typesupport_introspection_c__GoToPose_Feedback_message_members = {
  "g_arm_msgs__action",  // message namespace
  "GoToPose_Feedback",  // message name
  5,  // number of fields
  sizeof(g_arm_msgs__action__GoToPose_Feedback),
  false,  // has_any_key_member_
  g_arm_msgs__action__GoToPose_Feedback__rosidl_typesupport_introspection_c__GoToPose_Feedback_message_member_array,  // message members
  g_arm_msgs__action__GoToPose_Feedback__rosidl_typesupport_introspection_c__GoToPose_Feedback_init_function,  // function to initialize message memory (memory has to be allocated)
  g_arm_msgs__action__GoToPose_Feedback__rosidl_typesupport_introspection_c__GoToPose_Feedback_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t g_arm_msgs__action__GoToPose_Feedback__rosidl_typesupport_introspection_c__GoToPose_Feedback_message_type_support_handle = {
  0,
  &g_arm_msgs__action__GoToPose_Feedback__rosidl_typesupport_introspection_c__GoToPose_Feedback_message_members,
  get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_Feedback__get_type_hash,
  &g_arm_msgs__action__GoToPose_Feedback__get_type_description,
  &g_arm_msgs__action__GoToPose_Feedback__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_Feedback)() {
  if (!g_arm_msgs__action__GoToPose_Feedback__rosidl_typesupport_introspection_c__GoToPose_Feedback_message_type_support_handle.typesupport_identifier) {
    g_arm_msgs__action__GoToPose_Feedback__rosidl_typesupport_introspection_c__GoToPose_Feedback_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &g_arm_msgs__action__GoToPose_Feedback__rosidl_typesupport_introspection_c__GoToPose_Feedback_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"
// already included above
// #include "g_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.h"


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `goal`
#include "g_arm_msgs/action/go_to_pose.h"
// Member `goal`
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  g_arm_msgs__action__GoToPose_SendGoal_Request__init(message_memory);
}

void g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_fini_function(void * message_memory)
{
  g_arm_msgs__action__GoToPose_SendGoal_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_SendGoal_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "goal",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_SendGoal_Request, goal),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_message_members = {
  "g_arm_msgs__action",  // message namespace
  "GoToPose_SendGoal_Request",  // message name
  2,  // number of fields
  sizeof(g_arm_msgs__action__GoToPose_SendGoal_Request),
  false,  // has_any_key_member_
  g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_message_member_array,  // message members
  g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_message_type_support_handle = {
  0,
  &g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_message_members,
  get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_SendGoal_Request__get_type_hash,
  &g_arm_msgs__action__GoToPose_SendGoal_Request__get_type_description,
  &g_arm_msgs__action__GoToPose_SendGoal_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_SendGoal_Request)() {
  g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_Goal)();
  if (!g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_message_type_support_handle.typesupport_identifier) {
    g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"
// already included above
// #include "g_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.h"


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/time.h"
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  g_arm_msgs__action__GoToPose_SendGoal_Response__init(message_memory);
}

void g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_fini_function(void * message_memory)
{
  g_arm_msgs__action__GoToPose_SendGoal_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_message_member_array[2] = {
  {
    "accepted",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_SendGoal_Response, accepted),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "stamp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_SendGoal_Response, stamp),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_message_members = {
  "g_arm_msgs__action",  // message namespace
  "GoToPose_SendGoal_Response",  // message name
  2,  // number of fields
  sizeof(g_arm_msgs__action__GoToPose_SendGoal_Response),
  false,  // has_any_key_member_
  g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_message_member_array,  // message members
  g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_message_type_support_handle = {
  0,
  &g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_message_members,
  get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_SendGoal_Response__get_type_hash,
  &g_arm_msgs__action__GoToPose_SendGoal_Response__get_type_description,
  &g_arm_msgs__action__GoToPose_SendGoal_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_SendGoal_Response)() {
  g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, builtin_interfaces, msg, Time)();
  if (!g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_message_type_support_handle.typesupport_identifier) {
    g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"
// already included above
// #include "g_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
// already included above
// #include "g_arm_msgs/action/go_to_pose.h"
// Member `request`
// Member `response`
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  g_arm_msgs__action__GoToPose_SendGoal_Event__init(message_memory);
}

void g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_fini_function(void * message_memory)
{
  g_arm_msgs__action__GoToPose_SendGoal_Event__fini(message_memory);
}

size_t g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__GoToPose_SendGoal_Event__request(
  const void * untyped_member)
{
  const g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence * member =
    (const g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__GoToPose_SendGoal_Event__request(
  const void * untyped_member, size_t index)
{
  const g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence * member =
    (const g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__GoToPose_SendGoal_Event__request(
  void * untyped_member, size_t index)
{
  g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence * member =
    (g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__GoToPose_SendGoal_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const g_arm_msgs__action__GoToPose_SendGoal_Request * item =
    ((const g_arm_msgs__action__GoToPose_SendGoal_Request *)
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__GoToPose_SendGoal_Event__request(untyped_member, index));
  g_arm_msgs__action__GoToPose_SendGoal_Request * value =
    (g_arm_msgs__action__GoToPose_SendGoal_Request *)(untyped_value);
  *value = *item;
}

void g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__GoToPose_SendGoal_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  g_arm_msgs__action__GoToPose_SendGoal_Request * item =
    ((g_arm_msgs__action__GoToPose_SendGoal_Request *)
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__GoToPose_SendGoal_Event__request(untyped_member, index));
  const g_arm_msgs__action__GoToPose_SendGoal_Request * value =
    (const g_arm_msgs__action__GoToPose_SendGoal_Request *)(untyped_value);
  *item = *value;
}

bool g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__GoToPose_SendGoal_Event__request(
  void * untyped_member, size_t size)
{
  g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence * member =
    (g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence *)(untyped_member);
  g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__fini(member);
  return g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence__init(member, size);
}

size_t g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__GoToPose_SendGoal_Event__response(
  const void * untyped_member)
{
  const g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence * member =
    (const g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__GoToPose_SendGoal_Event__response(
  const void * untyped_member, size_t index)
{
  const g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence * member =
    (const g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__GoToPose_SendGoal_Event__response(
  void * untyped_member, size_t index)
{
  g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence * member =
    (g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__GoToPose_SendGoal_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const g_arm_msgs__action__GoToPose_SendGoal_Response * item =
    ((const g_arm_msgs__action__GoToPose_SendGoal_Response *)
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__GoToPose_SendGoal_Event__response(untyped_member, index));
  g_arm_msgs__action__GoToPose_SendGoal_Response * value =
    (g_arm_msgs__action__GoToPose_SendGoal_Response *)(untyped_value);
  *value = *item;
}

void g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__GoToPose_SendGoal_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  g_arm_msgs__action__GoToPose_SendGoal_Response * item =
    ((g_arm_msgs__action__GoToPose_SendGoal_Response *)
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__GoToPose_SendGoal_Event__response(untyped_member, index));
  const g_arm_msgs__action__GoToPose_SendGoal_Response * value =
    (const g_arm_msgs__action__GoToPose_SendGoal_Response *)(untyped_value);
  *item = *value;
}

bool g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__GoToPose_SendGoal_Event__response(
  void * untyped_member, size_t size)
{
  g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence * member =
    (g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence *)(untyped_member);
  g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__fini(member);
  return g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_SendGoal_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_SendGoal_Event, request),  // bytes offset in struct
    NULL,  // default value
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__GoToPose_SendGoal_Event__request,  // size() function pointer
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__GoToPose_SendGoal_Event__request,  // get_const(index) function pointer
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__GoToPose_SendGoal_Event__request,  // get(index) function pointer
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__GoToPose_SendGoal_Event__request,  // fetch(index, &value) function pointer
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__GoToPose_SendGoal_Event__request,  // assign(index, value) function pointer
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__GoToPose_SendGoal_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_SendGoal_Event, response),  // bytes offset in struct
    NULL,  // default value
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__size_function__GoToPose_SendGoal_Event__response,  // size() function pointer
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__get_const_function__GoToPose_SendGoal_Event__response,  // get_const(index) function pointer
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__get_function__GoToPose_SendGoal_Event__response,  // get(index) function pointer
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__fetch_function__GoToPose_SendGoal_Event__response,  // fetch(index, &value) function pointer
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__assign_function__GoToPose_SendGoal_Event__response,  // assign(index, value) function pointer
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__resize_function__GoToPose_SendGoal_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_message_members = {
  "g_arm_msgs__action",  // message namespace
  "GoToPose_SendGoal_Event",  // message name
  3,  // number of fields
  sizeof(g_arm_msgs__action__GoToPose_SendGoal_Event),
  false,  // has_any_key_member_
  g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_message_member_array,  // message members
  g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_message_type_support_handle = {
  0,
  &g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_message_members,
  get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_SendGoal_Event__get_type_hash,
  &g_arm_msgs__action__GoToPose_SendGoal_Event__get_type_description,
  &g_arm_msgs__action__GoToPose_SendGoal_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_SendGoal_Event)() {
  g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_SendGoal_Request)();
  g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_SendGoal_Response)();
  if (!g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_message_type_support_handle.typesupport_identifier) {
    g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "g_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_SendGoal_service_members = {
  "g_arm_msgs__action",  // service namespace
  "GoToPose_SendGoal",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_message_type_support_handle,
  NULL,  // response message
  // g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_message_type_support_handle
  NULL  // event_message
  // g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_message_type_support_handle
};


static rosidl_service_type_support_t g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_SendGoal_service_type_support_handle = {
  0,
  &g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_SendGoal_service_members,
  get_service_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_SendGoal_Request__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Request_message_type_support_handle,
  &g_arm_msgs__action__GoToPose_SendGoal_Response__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Response_message_type_support_handle,
  &g_arm_msgs__action__GoToPose_SendGoal_Event__rosidl_typesupport_introspection_c__GoToPose_SendGoal_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    g_arm_msgs,
    action,
    GoToPose_SendGoal
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    g_arm_msgs,
    action,
    GoToPose_SendGoal
  ),
  &g_arm_msgs__action__GoToPose_SendGoal__get_type_hash,
  &g_arm_msgs__action__GoToPose_SendGoal__get_type_description,
  &g_arm_msgs__action__GoToPose_SendGoal__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_SendGoal_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_SendGoal_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_SendGoal_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g_arm_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_SendGoal)(void) {
  if (!g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_SendGoal_service_type_support_handle.typesupport_identifier) {
    g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_SendGoal_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_SendGoal_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_SendGoal_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_SendGoal_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_SendGoal_Event)()->data;
  }

  return &g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_SendGoal_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"
// already included above
// #include "g_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  g_arm_msgs__action__GoToPose_GetResult_Request__init(message_memory);
}

void g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_fini_function(void * message_memory)
{
  g_arm_msgs__action__GoToPose_GetResult_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_message_member_array[1] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_GetResult_Request, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_message_members = {
  "g_arm_msgs__action",  // message namespace
  "GoToPose_GetResult_Request",  // message name
  1,  // number of fields
  sizeof(g_arm_msgs__action__GoToPose_GetResult_Request),
  false,  // has_any_key_member_
  g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_message_member_array,  // message members
  g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_message_type_support_handle = {
  0,
  &g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_message_members,
  get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_GetResult_Request__get_type_hash,
  &g_arm_msgs__action__GoToPose_GetResult_Request__get_type_description,
  &g_arm_msgs__action__GoToPose_GetResult_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_GetResult_Request)() {
  g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  if (!g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_message_type_support_handle.typesupport_identifier) {
    g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"
// already included above
// #include "g_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.h"


// Include directives for member types
// Member `result`
// already included above
// #include "g_arm_msgs/action/go_to_pose.h"
// Member `result`
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  g_arm_msgs__action__GoToPose_GetResult_Response__init(message_memory);
}

void g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_fini_function(void * message_memory)
{
  g_arm_msgs__action__GoToPose_GetResult_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_message_member_array[2] = {
  {
    "status",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT8,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_GetResult_Response, status),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "result",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_GetResult_Response, result),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_message_members = {
  "g_arm_msgs__action",  // message namespace
  "GoToPose_GetResult_Response",  // message name
  2,  // number of fields
  sizeof(g_arm_msgs__action__GoToPose_GetResult_Response),
  false,  // has_any_key_member_
  g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_message_member_array,  // message members
  g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_message_type_support_handle = {
  0,
  &g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_message_members,
  get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_GetResult_Response__get_type_hash,
  &g_arm_msgs__action__GoToPose_GetResult_Response__get_type_description,
  &g_arm_msgs__action__GoToPose_GetResult_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_GetResult_Response)() {
  g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_Result)();
  if (!g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_message_type_support_handle.typesupport_identifier) {
    g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"
// already included above
// #include "g_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.h"


// Include directives for member types
// Member `info`
// already included above
// #include "service_msgs/msg/service_event_info.h"
// Member `info`
// already included above
// #include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
// already included above
// #include "g_arm_msgs/action/go_to_pose.h"
// Member `request`
// Member `response`
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  g_arm_msgs__action__GoToPose_GetResult_Event__init(message_memory);
}

void g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_fini_function(void * message_memory)
{
  g_arm_msgs__action__GoToPose_GetResult_Event__fini(message_memory);
}

size_t g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__size_function__GoToPose_GetResult_Event__request(
  const void * untyped_member)
{
  const g_arm_msgs__action__GoToPose_GetResult_Request__Sequence * member =
    (const g_arm_msgs__action__GoToPose_GetResult_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__GoToPose_GetResult_Event__request(
  const void * untyped_member, size_t index)
{
  const g_arm_msgs__action__GoToPose_GetResult_Request__Sequence * member =
    (const g_arm_msgs__action__GoToPose_GetResult_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__get_function__GoToPose_GetResult_Event__request(
  void * untyped_member, size_t index)
{
  g_arm_msgs__action__GoToPose_GetResult_Request__Sequence * member =
    (g_arm_msgs__action__GoToPose_GetResult_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__GoToPose_GetResult_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const g_arm_msgs__action__GoToPose_GetResult_Request * item =
    ((const g_arm_msgs__action__GoToPose_GetResult_Request *)
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__GoToPose_GetResult_Event__request(untyped_member, index));
  g_arm_msgs__action__GoToPose_GetResult_Request * value =
    (g_arm_msgs__action__GoToPose_GetResult_Request *)(untyped_value);
  *value = *item;
}

void g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__GoToPose_GetResult_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  g_arm_msgs__action__GoToPose_GetResult_Request * item =
    ((g_arm_msgs__action__GoToPose_GetResult_Request *)
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__get_function__GoToPose_GetResult_Event__request(untyped_member, index));
  const g_arm_msgs__action__GoToPose_GetResult_Request * value =
    (const g_arm_msgs__action__GoToPose_GetResult_Request *)(untyped_value);
  *item = *value;
}

bool g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__GoToPose_GetResult_Event__request(
  void * untyped_member, size_t size)
{
  g_arm_msgs__action__GoToPose_GetResult_Request__Sequence * member =
    (g_arm_msgs__action__GoToPose_GetResult_Request__Sequence *)(untyped_member);
  g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__fini(member);
  return g_arm_msgs__action__GoToPose_GetResult_Request__Sequence__init(member, size);
}

size_t g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__size_function__GoToPose_GetResult_Event__response(
  const void * untyped_member)
{
  const g_arm_msgs__action__GoToPose_GetResult_Response__Sequence * member =
    (const g_arm_msgs__action__GoToPose_GetResult_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__GoToPose_GetResult_Event__response(
  const void * untyped_member, size_t index)
{
  const g_arm_msgs__action__GoToPose_GetResult_Response__Sequence * member =
    (const g_arm_msgs__action__GoToPose_GetResult_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__get_function__GoToPose_GetResult_Event__response(
  void * untyped_member, size_t index)
{
  g_arm_msgs__action__GoToPose_GetResult_Response__Sequence * member =
    (g_arm_msgs__action__GoToPose_GetResult_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__GoToPose_GetResult_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const g_arm_msgs__action__GoToPose_GetResult_Response * item =
    ((const g_arm_msgs__action__GoToPose_GetResult_Response *)
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__GoToPose_GetResult_Event__response(untyped_member, index));
  g_arm_msgs__action__GoToPose_GetResult_Response * value =
    (g_arm_msgs__action__GoToPose_GetResult_Response *)(untyped_value);
  *value = *item;
}

void g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__GoToPose_GetResult_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  g_arm_msgs__action__GoToPose_GetResult_Response * item =
    ((g_arm_msgs__action__GoToPose_GetResult_Response *)
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__get_function__GoToPose_GetResult_Event__response(untyped_member, index));
  const g_arm_msgs__action__GoToPose_GetResult_Response * value =
    (const g_arm_msgs__action__GoToPose_GetResult_Response *)(untyped_value);
  *item = *value;
}

bool g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__GoToPose_GetResult_Event__response(
  void * untyped_member, size_t size)
{
  g_arm_msgs__action__GoToPose_GetResult_Response__Sequence * member =
    (g_arm_msgs__action__GoToPose_GetResult_Response__Sequence *)(untyped_member);
  g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__fini(member);
  return g_arm_msgs__action__GoToPose_GetResult_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_GetResult_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_GetResult_Event, request),  // bytes offset in struct
    NULL,  // default value
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__size_function__GoToPose_GetResult_Event__request,  // size() function pointer
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__GoToPose_GetResult_Event__request,  // get_const(index) function pointer
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__get_function__GoToPose_GetResult_Event__request,  // get(index) function pointer
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__GoToPose_GetResult_Event__request,  // fetch(index, &value) function pointer
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__GoToPose_GetResult_Event__request,  // assign(index, value) function pointer
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__GoToPose_GetResult_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_GetResult_Event, response),  // bytes offset in struct
    NULL,  // default value
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__size_function__GoToPose_GetResult_Event__response,  // size() function pointer
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__get_const_function__GoToPose_GetResult_Event__response,  // get_const(index) function pointer
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__get_function__GoToPose_GetResult_Event__response,  // get(index) function pointer
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__fetch_function__GoToPose_GetResult_Event__response,  // fetch(index, &value) function pointer
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__assign_function__GoToPose_GetResult_Event__response,  // assign(index, value) function pointer
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__resize_function__GoToPose_GetResult_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_message_members = {
  "g_arm_msgs__action",  // message namespace
  "GoToPose_GetResult_Event",  // message name
  3,  // number of fields
  sizeof(g_arm_msgs__action__GoToPose_GetResult_Event),
  false,  // has_any_key_member_
  g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_message_member_array,  // message members
  g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_message_type_support_handle = {
  0,
  &g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_message_members,
  get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_GetResult_Event__get_type_hash,
  &g_arm_msgs__action__GoToPose_GetResult_Event__get_type_description,
  &g_arm_msgs__action__GoToPose_GetResult_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_GetResult_Event)() {
  g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_GetResult_Request)();
  g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_GetResult_Response)();
  if (!g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_message_type_support_handle.typesupport_identifier) {
    g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "g_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_GetResult_service_members = {
  "g_arm_msgs__action",  // service namespace
  "GoToPose_GetResult",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_message_type_support_handle,
  NULL,  // response message
  // g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_message_type_support_handle
  NULL  // event_message
  // g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_message_type_support_handle
};


static rosidl_service_type_support_t g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_GetResult_service_type_support_handle = {
  0,
  &g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_GetResult_service_members,
  get_service_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_GetResult_Request__rosidl_typesupport_introspection_c__GoToPose_GetResult_Request_message_type_support_handle,
  &g_arm_msgs__action__GoToPose_GetResult_Response__rosidl_typesupport_introspection_c__GoToPose_GetResult_Response_message_type_support_handle,
  &g_arm_msgs__action__GoToPose_GetResult_Event__rosidl_typesupport_introspection_c__GoToPose_GetResult_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    g_arm_msgs,
    action,
    GoToPose_GetResult
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    g_arm_msgs,
    action,
    GoToPose_GetResult
  ),
  &g_arm_msgs__action__GoToPose_GetResult__get_type_hash,
  &g_arm_msgs__action__GoToPose_GetResult__get_type_description,
  &g_arm_msgs__action__GoToPose_GetResult__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_GetResult_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_GetResult_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_GetResult_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g_arm_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_GetResult)(void) {
  if (!g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_GetResult_service_type_support_handle.typesupport_identifier) {
    g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_GetResult_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_GetResult_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_GetResult_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_GetResult_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_GetResult_Event)()->data;
  }

  return &g_arm_msgs__action__detail__go_to_pose__rosidl_typesupport_introspection_c__GoToPose_GetResult_service_type_support_handle;
}

// already included above
// #include <stddef.h>
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"
// already included above
// #include "g_arm_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.h"


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/uuid.h"
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__rosidl_typesupport_introspection_c.h"
// Member `feedback`
// already included above
// #include "g_arm_msgs/action/go_to_pose.h"
// Member `feedback`
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  g_arm_msgs__action__GoToPose_FeedbackMessage__init(message_memory);
}

void g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_fini_function(void * message_memory)
{
  g_arm_msgs__action__GoToPose_FeedbackMessage__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_message_member_array[2] = {
  {
    "goal_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_FeedbackMessage, goal_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "feedback",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(g_arm_msgs__action__GoToPose_FeedbackMessage, feedback),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_message_members = {
  "g_arm_msgs__action",  // message namespace
  "GoToPose_FeedbackMessage",  // message name
  2,  // number of fields
  sizeof(g_arm_msgs__action__GoToPose_FeedbackMessage),
  false,  // has_any_key_member_
  g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_message_member_array,  // message members
  g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_init_function,  // function to initialize message memory (memory has to be allocated)
  g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_message_type_support_handle = {
  0,
  &g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_message_members,
  get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_FeedbackMessage__get_type_hash,
  &g_arm_msgs__action__GoToPose_FeedbackMessage__get_type_description,
  &g_arm_msgs__action__GoToPose_FeedbackMessage__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_g_arm_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_FeedbackMessage)() {
  g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, unique_identifier_msgs, msg, UUID)();
  g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, g_arm_msgs, action, GoToPose_Feedback)();
  if (!g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_message_type_support_handle.typesupport_identifier) {
    g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &g_arm_msgs__action__GoToPose_FeedbackMessage__rosidl_typesupport_introspection_c__GoToPose_FeedbackMessage_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
