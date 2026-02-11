// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from g_arm_msgs:action/GoToPose.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g_arm_msgs/action/go_to_pose.h"


#ifndef G_ARM_MSGS__ACTION__DETAIL__GO_TO_POSE__STRUCT_H_
#define G_ARM_MSGS__ACTION__DETAIL__GO_TO_POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'target'
#include "geometry_msgs/msg/detail/pose_stamped__struct.h"
// Member 'planner_frame'
#include "rosidl_runtime_c/string.h"

/// Struct defined in action/GoToPose in the package g_arm_msgs.
typedef struct g_arm_msgs__action__GoToPose_Goal
{
  geometry_msgs__msg__PoseStamped target;
  double pos_tolerance_m;
  double ang_tolerance_rad;
  double timeout_sec;
  bool allow_orientation;
  rosidl_runtime_c__String planner_frame;
  double speed_scale;
  double max_joint_vel;
  double max_joint_acc;
  bool electromagnet_on;
} g_arm_msgs__action__GoToPose_Goal;

// Struct for a sequence of g_arm_msgs__action__GoToPose_Goal.
typedef struct g_arm_msgs__action__GoToPose_Goal__Sequence
{
  g_arm_msgs__action__GoToPose_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g_arm_msgs__action__GoToPose_Goal__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'final_joint_positions'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in action/GoToPose in the package g_arm_msgs.
typedef struct g_arm_msgs__action__GoToPose_Result
{
  bool success;
  int32_t error_code;
  rosidl_runtime_c__String message;
  double final_pos_error_m;
  double final_ang_error_rad;
  rosidl_runtime_c__double__Sequence final_joint_positions;
} g_arm_msgs__action__GoToPose_Result;

// Struct for a sequence of g_arm_msgs__action__GoToPose_Result.
typedef struct g_arm_msgs__action__GoToPose_Result__Sequence
{
  g_arm_msgs__action__GoToPose_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g_arm_msgs__action__GoToPose_Result__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'state'
// Member 'detail'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/GoToPose in the package g_arm_msgs.
typedef struct g_arm_msgs__action__GoToPose_Feedback
{
  rosidl_runtime_c__String state;
  double pos_error_m;
  double ang_error_rad;
  double progress;
  rosidl_runtime_c__String detail;
} g_arm_msgs__action__GoToPose_Feedback;

// Struct for a sequence of g_arm_msgs__action__GoToPose_Feedback.
typedef struct g_arm_msgs__action__GoToPose_Feedback__Sequence
{
  g_arm_msgs__action__GoToPose_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g_arm_msgs__action__GoToPose_Feedback__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "g_arm_msgs/action/detail/go_to_pose__struct.h"

/// Struct defined in action/GoToPose in the package g_arm_msgs.
typedef struct g_arm_msgs__action__GoToPose_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  g_arm_msgs__action__GoToPose_Goal goal;
} g_arm_msgs__action__GoToPose_SendGoal_Request;

// Struct for a sequence of g_arm_msgs__action__GoToPose_SendGoal_Request.
typedef struct g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence
{
  g_arm_msgs__action__GoToPose_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/GoToPose in the package g_arm_msgs.
typedef struct g_arm_msgs__action__GoToPose_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} g_arm_msgs__action__GoToPose_SendGoal_Response;

// Struct for a sequence of g_arm_msgs__action__GoToPose_SendGoal_Response.
typedef struct g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence
{
  g_arm_msgs__action__GoToPose_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  g_arm_msgs__action__GoToPose_SendGoal_Event__request__MAX_SIZE = 1
};
// response
enum
{
  g_arm_msgs__action__GoToPose_SendGoal_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/GoToPose in the package g_arm_msgs.
typedef struct g_arm_msgs__action__GoToPose_SendGoal_Event
{
  service_msgs__msg__ServiceEventInfo info;
  g_arm_msgs__action__GoToPose_SendGoal_Request__Sequence request;
  g_arm_msgs__action__GoToPose_SendGoal_Response__Sequence response;
} g_arm_msgs__action__GoToPose_SendGoal_Event;

// Struct for a sequence of g_arm_msgs__action__GoToPose_SendGoal_Event.
typedef struct g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence
{
  g_arm_msgs__action__GoToPose_SendGoal_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g_arm_msgs__action__GoToPose_SendGoal_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/GoToPose in the package g_arm_msgs.
typedef struct g_arm_msgs__action__GoToPose_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} g_arm_msgs__action__GoToPose_GetResult_Request;

// Struct for a sequence of g_arm_msgs__action__GoToPose_GetResult_Request.
typedef struct g_arm_msgs__action__GoToPose_GetResult_Request__Sequence
{
  g_arm_msgs__action__GoToPose_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g_arm_msgs__action__GoToPose_GetResult_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.h"

/// Struct defined in action/GoToPose in the package g_arm_msgs.
typedef struct g_arm_msgs__action__GoToPose_GetResult_Response
{
  int8_t status;
  g_arm_msgs__action__GoToPose_Result result;
} g_arm_msgs__action__GoToPose_GetResult_Response;

// Struct for a sequence of g_arm_msgs__action__GoToPose_GetResult_Response.
typedef struct g_arm_msgs__action__GoToPose_GetResult_Response__Sequence
{
  g_arm_msgs__action__GoToPose_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g_arm_msgs__action__GoToPose_GetResult_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  g_arm_msgs__action__GoToPose_GetResult_Event__request__MAX_SIZE = 1
};
// response
enum
{
  g_arm_msgs__action__GoToPose_GetResult_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/GoToPose in the package g_arm_msgs.
typedef struct g_arm_msgs__action__GoToPose_GetResult_Event
{
  service_msgs__msg__ServiceEventInfo info;
  g_arm_msgs__action__GoToPose_GetResult_Request__Sequence request;
  g_arm_msgs__action__GoToPose_GetResult_Response__Sequence response;
} g_arm_msgs__action__GoToPose_GetResult_Event;

// Struct for a sequence of g_arm_msgs__action__GoToPose_GetResult_Event.
typedef struct g_arm_msgs__action__GoToPose_GetResult_Event__Sequence
{
  g_arm_msgs__action__GoToPose_GetResult_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g_arm_msgs__action__GoToPose_GetResult_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.h"

/// Struct defined in action/GoToPose in the package g_arm_msgs.
typedef struct g_arm_msgs__action__GoToPose_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  g_arm_msgs__action__GoToPose_Feedback feedback;
} g_arm_msgs__action__GoToPose_FeedbackMessage;

// Struct for a sequence of g_arm_msgs__action__GoToPose_FeedbackMessage.
typedef struct g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence
{
  g_arm_msgs__action__GoToPose_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} g_arm_msgs__action__GoToPose_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // G_ARM_MSGS__ACTION__DETAIL__GO_TO_POSE__STRUCT_H_
