// generated from rosidl_typesupport_cpp/resource/idl__type_support.cpp.em
// with input from g_arm_msgs:action/GoToPose.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "g_arm_msgs/action/detail/go_to_pose__functions.h"
#include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
#include "rosidl_typesupport_cpp/identifier.hpp"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
#include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _GoToPose_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GoToPose_Goal_type_support_ids_t;

static const _GoToPose_Goal_type_support_ids_t _GoToPose_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GoToPose_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GoToPose_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GoToPose_Goal_type_support_symbol_names_t _GoToPose_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g_arm_msgs, action, GoToPose_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g_arm_msgs, action, GoToPose_Goal)),
  }
};

typedef struct _GoToPose_Goal_type_support_data_t
{
  void * data[2];
} _GoToPose_Goal_type_support_data_t;

static _GoToPose_Goal_type_support_data_t _GoToPose_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GoToPose_Goal_message_typesupport_map = {
  2,
  "g_arm_msgs",
  &_GoToPose_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_GoToPose_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_GoToPose_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GoToPose_Goal_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GoToPose_Goal_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_Goal__get_type_hash,
  &g_arm_msgs__action__GoToPose_Goal__get_type_description,
  &g_arm_msgs__action__GoToPose_Goal__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g_arm_msgs::action::GoToPose_Goal>()
{
  return &::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_Goal_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose_Goal)() {
  return get_message_type_support_handle<g_arm_msgs::action::GoToPose_Goal>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _GoToPose_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GoToPose_Result_type_support_ids_t;

static const _GoToPose_Result_type_support_ids_t _GoToPose_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GoToPose_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GoToPose_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GoToPose_Result_type_support_symbol_names_t _GoToPose_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g_arm_msgs, action, GoToPose_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g_arm_msgs, action, GoToPose_Result)),
  }
};

typedef struct _GoToPose_Result_type_support_data_t
{
  void * data[2];
} _GoToPose_Result_type_support_data_t;

static _GoToPose_Result_type_support_data_t _GoToPose_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GoToPose_Result_message_typesupport_map = {
  2,
  "g_arm_msgs",
  &_GoToPose_Result_message_typesupport_ids.typesupport_identifier[0],
  &_GoToPose_Result_message_typesupport_symbol_names.symbol_name[0],
  &_GoToPose_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GoToPose_Result_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GoToPose_Result_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_Result__get_type_hash,
  &g_arm_msgs__action__GoToPose_Result__get_type_description,
  &g_arm_msgs__action__GoToPose_Result__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g_arm_msgs::action::GoToPose_Result>()
{
  return &::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_Result_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose_Result)() {
  return get_message_type_support_handle<g_arm_msgs::action::GoToPose_Result>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _GoToPose_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GoToPose_Feedback_type_support_ids_t;

static const _GoToPose_Feedback_type_support_ids_t _GoToPose_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GoToPose_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GoToPose_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GoToPose_Feedback_type_support_symbol_names_t _GoToPose_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g_arm_msgs, action, GoToPose_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g_arm_msgs, action, GoToPose_Feedback)),
  }
};

typedef struct _GoToPose_Feedback_type_support_data_t
{
  void * data[2];
} _GoToPose_Feedback_type_support_data_t;

static _GoToPose_Feedback_type_support_data_t _GoToPose_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GoToPose_Feedback_message_typesupport_map = {
  2,
  "g_arm_msgs",
  &_GoToPose_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_GoToPose_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_GoToPose_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GoToPose_Feedback_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GoToPose_Feedback_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_Feedback__get_type_hash,
  &g_arm_msgs__action__GoToPose_Feedback__get_type_description,
  &g_arm_msgs__action__GoToPose_Feedback__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g_arm_msgs::action::GoToPose_Feedback>()
{
  return &::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose_Feedback)() {
  return get_message_type_support_handle<g_arm_msgs::action::GoToPose_Feedback>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _GoToPose_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GoToPose_SendGoal_Request_type_support_ids_t;

static const _GoToPose_SendGoal_Request_type_support_ids_t _GoToPose_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GoToPose_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GoToPose_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GoToPose_SendGoal_Request_type_support_symbol_names_t _GoToPose_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g_arm_msgs, action, GoToPose_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g_arm_msgs, action, GoToPose_SendGoal_Request)),
  }
};

typedef struct _GoToPose_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _GoToPose_SendGoal_Request_type_support_data_t;

static _GoToPose_SendGoal_Request_type_support_data_t _GoToPose_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GoToPose_SendGoal_Request_message_typesupport_map = {
  2,
  "g_arm_msgs",
  &_GoToPose_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_GoToPose_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_GoToPose_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GoToPose_SendGoal_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GoToPose_SendGoal_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_SendGoal_Request__get_type_hash,
  &g_arm_msgs__action__GoToPose_SendGoal_Request__get_type_description,
  &g_arm_msgs__action__GoToPose_SendGoal_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g_arm_msgs::action::GoToPose_SendGoal_Request>()
{
  return &::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose_SendGoal_Request)() {
  return get_message_type_support_handle<g_arm_msgs::action::GoToPose_SendGoal_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _GoToPose_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GoToPose_SendGoal_Response_type_support_ids_t;

static const _GoToPose_SendGoal_Response_type_support_ids_t _GoToPose_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GoToPose_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GoToPose_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GoToPose_SendGoal_Response_type_support_symbol_names_t _GoToPose_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g_arm_msgs, action, GoToPose_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g_arm_msgs, action, GoToPose_SendGoal_Response)),
  }
};

typedef struct _GoToPose_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _GoToPose_SendGoal_Response_type_support_data_t;

static _GoToPose_SendGoal_Response_type_support_data_t _GoToPose_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GoToPose_SendGoal_Response_message_typesupport_map = {
  2,
  "g_arm_msgs",
  &_GoToPose_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_GoToPose_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_GoToPose_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GoToPose_SendGoal_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GoToPose_SendGoal_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_SendGoal_Response__get_type_hash,
  &g_arm_msgs__action__GoToPose_SendGoal_Response__get_type_description,
  &g_arm_msgs__action__GoToPose_SendGoal_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g_arm_msgs::action::GoToPose_SendGoal_Response>()
{
  return &::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose_SendGoal_Response)() {
  return get_message_type_support_handle<g_arm_msgs::action::GoToPose_SendGoal_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _GoToPose_SendGoal_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GoToPose_SendGoal_Event_type_support_ids_t;

static const _GoToPose_SendGoal_Event_type_support_ids_t _GoToPose_SendGoal_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GoToPose_SendGoal_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GoToPose_SendGoal_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GoToPose_SendGoal_Event_type_support_symbol_names_t _GoToPose_SendGoal_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g_arm_msgs, action, GoToPose_SendGoal_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g_arm_msgs, action, GoToPose_SendGoal_Event)),
  }
};

typedef struct _GoToPose_SendGoal_Event_type_support_data_t
{
  void * data[2];
} _GoToPose_SendGoal_Event_type_support_data_t;

static _GoToPose_SendGoal_Event_type_support_data_t _GoToPose_SendGoal_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GoToPose_SendGoal_Event_message_typesupport_map = {
  2,
  "g_arm_msgs",
  &_GoToPose_SendGoal_Event_message_typesupport_ids.typesupport_identifier[0],
  &_GoToPose_SendGoal_Event_message_typesupport_symbol_names.symbol_name[0],
  &_GoToPose_SendGoal_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GoToPose_SendGoal_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GoToPose_SendGoal_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_SendGoal_Event__get_type_hash,
  &g_arm_msgs__action__GoToPose_SendGoal_Event__get_type_description,
  &g_arm_msgs__action__GoToPose_SendGoal_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g_arm_msgs::action::GoToPose_SendGoal_Event>()
{
  return &::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_SendGoal_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose_SendGoal_Event)() {
  return get_message_type_support_handle<g_arm_msgs::action::GoToPose_SendGoal_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
#include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _GoToPose_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GoToPose_SendGoal_type_support_ids_t;

static const _GoToPose_SendGoal_type_support_ids_t _GoToPose_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GoToPose_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GoToPose_SendGoal_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GoToPose_SendGoal_type_support_symbol_names_t _GoToPose_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g_arm_msgs, action, GoToPose_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g_arm_msgs, action, GoToPose_SendGoal)),
  }
};

typedef struct _GoToPose_SendGoal_type_support_data_t
{
  void * data[2];
} _GoToPose_SendGoal_type_support_data_t;

static _GoToPose_SendGoal_type_support_data_t _GoToPose_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GoToPose_SendGoal_service_typesupport_map = {
  2,
  "g_arm_msgs",
  &_GoToPose_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_GoToPose_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_GoToPose_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t GoToPose_SendGoal_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GoToPose_SendGoal_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<g_arm_msgs::action::GoToPose_SendGoal_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<g_arm_msgs::action::GoToPose_SendGoal_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<g_arm_msgs::action::GoToPose_SendGoal_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<g_arm_msgs::action::GoToPose_SendGoal>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<g_arm_msgs::action::GoToPose_SendGoal>,
  &g_arm_msgs__action__GoToPose_SendGoal__get_type_hash,
  &g_arm_msgs__action__GoToPose_SendGoal__get_type_description,
  &g_arm_msgs__action__GoToPose_SendGoal__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<g_arm_msgs::action::GoToPose_SendGoal>()
{
  return &::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_SendGoal_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose_SendGoal)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<g_arm_msgs::action::GoToPose_SendGoal>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _GoToPose_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GoToPose_GetResult_Request_type_support_ids_t;

static const _GoToPose_GetResult_Request_type_support_ids_t _GoToPose_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GoToPose_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GoToPose_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GoToPose_GetResult_Request_type_support_symbol_names_t _GoToPose_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g_arm_msgs, action, GoToPose_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g_arm_msgs, action, GoToPose_GetResult_Request)),
  }
};

typedef struct _GoToPose_GetResult_Request_type_support_data_t
{
  void * data[2];
} _GoToPose_GetResult_Request_type_support_data_t;

static _GoToPose_GetResult_Request_type_support_data_t _GoToPose_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GoToPose_GetResult_Request_message_typesupport_map = {
  2,
  "g_arm_msgs",
  &_GoToPose_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_GoToPose_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_GoToPose_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GoToPose_GetResult_Request_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GoToPose_GetResult_Request_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_GetResult_Request__get_type_hash,
  &g_arm_msgs__action__GoToPose_GetResult_Request__get_type_description,
  &g_arm_msgs__action__GoToPose_GetResult_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g_arm_msgs::action::GoToPose_GetResult_Request>()
{
  return &::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose_GetResult_Request)() {
  return get_message_type_support_handle<g_arm_msgs::action::GoToPose_GetResult_Request>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _GoToPose_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GoToPose_GetResult_Response_type_support_ids_t;

static const _GoToPose_GetResult_Response_type_support_ids_t _GoToPose_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GoToPose_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GoToPose_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GoToPose_GetResult_Response_type_support_symbol_names_t _GoToPose_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g_arm_msgs, action, GoToPose_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g_arm_msgs, action, GoToPose_GetResult_Response)),
  }
};

typedef struct _GoToPose_GetResult_Response_type_support_data_t
{
  void * data[2];
} _GoToPose_GetResult_Response_type_support_data_t;

static _GoToPose_GetResult_Response_type_support_data_t _GoToPose_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GoToPose_GetResult_Response_message_typesupport_map = {
  2,
  "g_arm_msgs",
  &_GoToPose_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_GoToPose_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_GoToPose_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GoToPose_GetResult_Response_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GoToPose_GetResult_Response_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_GetResult_Response__get_type_hash,
  &g_arm_msgs__action__GoToPose_GetResult_Response__get_type_description,
  &g_arm_msgs__action__GoToPose_GetResult_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g_arm_msgs::action::GoToPose_GetResult_Response>()
{
  return &::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose_GetResult_Response)() {
  return get_message_type_support_handle<g_arm_msgs::action::GoToPose_GetResult_Response>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _GoToPose_GetResult_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GoToPose_GetResult_Event_type_support_ids_t;

static const _GoToPose_GetResult_Event_type_support_ids_t _GoToPose_GetResult_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GoToPose_GetResult_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GoToPose_GetResult_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GoToPose_GetResult_Event_type_support_symbol_names_t _GoToPose_GetResult_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g_arm_msgs, action, GoToPose_GetResult_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g_arm_msgs, action, GoToPose_GetResult_Event)),
  }
};

typedef struct _GoToPose_GetResult_Event_type_support_data_t
{
  void * data[2];
} _GoToPose_GetResult_Event_type_support_data_t;

static _GoToPose_GetResult_Event_type_support_data_t _GoToPose_GetResult_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GoToPose_GetResult_Event_message_typesupport_map = {
  2,
  "g_arm_msgs",
  &_GoToPose_GetResult_Event_message_typesupport_ids.typesupport_identifier[0],
  &_GoToPose_GetResult_Event_message_typesupport_symbol_names.symbol_name[0],
  &_GoToPose_GetResult_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GoToPose_GetResult_Event_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GoToPose_GetResult_Event_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_GetResult_Event__get_type_hash,
  &g_arm_msgs__action__GoToPose_GetResult_Event__get_type_description,
  &g_arm_msgs__action__GoToPose_GetResult_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g_arm_msgs::action::GoToPose_GetResult_Event>()
{
  return &::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_GetResult_Event_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose_GetResult_Event)() {
  return get_message_type_support_handle<g_arm_msgs::action::GoToPose_GetResult_Event>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _GoToPose_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GoToPose_GetResult_type_support_ids_t;

static const _GoToPose_GetResult_type_support_ids_t _GoToPose_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GoToPose_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GoToPose_GetResult_type_support_symbol_names_t;
#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GoToPose_GetResult_type_support_symbol_names_t _GoToPose_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g_arm_msgs, action, GoToPose_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g_arm_msgs, action, GoToPose_GetResult)),
  }
};

typedef struct _GoToPose_GetResult_type_support_data_t
{
  void * data[2];
} _GoToPose_GetResult_type_support_data_t;

static _GoToPose_GetResult_type_support_data_t _GoToPose_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GoToPose_GetResult_service_typesupport_map = {
  2,
  "g_arm_msgs",
  &_GoToPose_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_GoToPose_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_GoToPose_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t GoToPose_GetResult_service_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GoToPose_GetResult_service_typesupport_map),
  ::rosidl_typesupport_cpp::get_service_typesupport_handle_function,
  ::rosidl_typesupport_cpp::get_message_type_support_handle<g_arm_msgs::action::GoToPose_GetResult_Request>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<g_arm_msgs::action::GoToPose_GetResult_Response>(),
  ::rosidl_typesupport_cpp::get_message_type_support_handle<g_arm_msgs::action::GoToPose_GetResult_Event>(),
  &::rosidl_typesupport_cpp::service_create_event_message<g_arm_msgs::action::GoToPose_GetResult>,
  &::rosidl_typesupport_cpp::service_destroy_event_message<g_arm_msgs::action::GoToPose_GetResult>,
  &g_arm_msgs__action__GoToPose_GetResult__get_type_hash,
  &g_arm_msgs__action__GoToPose_GetResult__get_type_description,
  &g_arm_msgs__action__GoToPose_GetResult__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
get_service_type_support_handle<g_arm_msgs::action::GoToPose_GetResult>()
{
  return &::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_GetResult_service_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose_GetResult)() {
  return ::rosidl_typesupport_cpp::get_service_type_support_handle<g_arm_msgs::action::GoToPose_GetResult>();
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__functions.h"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/identifier.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support_dispatch.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

typedef struct _GoToPose_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GoToPose_FeedbackMessage_type_support_ids_t;

static const _GoToPose_FeedbackMessage_type_support_ids_t _GoToPose_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_cpp",  // ::rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
    "rosidl_typesupport_introspection_cpp",  // ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  }
};

typedef struct _GoToPose_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GoToPose_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GoToPose_FeedbackMessage_type_support_symbol_names_t _GoToPose_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, g_arm_msgs, action, GoToPose_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, g_arm_msgs, action, GoToPose_FeedbackMessage)),
  }
};

typedef struct _GoToPose_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _GoToPose_FeedbackMessage_type_support_data_t;

static _GoToPose_FeedbackMessage_type_support_data_t _GoToPose_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GoToPose_FeedbackMessage_message_typesupport_map = {
  2,
  "g_arm_msgs",
  &_GoToPose_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_GoToPose_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_GoToPose_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GoToPose_FeedbackMessage_message_type_support_handle = {
  ::rosidl_typesupport_cpp::typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GoToPose_FeedbackMessage_message_typesupport_map),
  ::rosidl_typesupport_cpp::get_message_typesupport_handle_function,
  &g_arm_msgs__action__GoToPose_FeedbackMessage__get_type_hash,
  &g_arm_msgs__action__GoToPose_FeedbackMessage__get_type_description,
  &g_arm_msgs__action__GoToPose_FeedbackMessage__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<g_arm_msgs::action::GoToPose_FeedbackMessage>()
{
  return &::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose_FeedbackMessage)() {
  return get_message_type_support_handle<g_arm_msgs::action::GoToPose_FeedbackMessage>();
}

#ifdef __cplusplus
}
#endif
}  // namespace rosidl_typesupport_cpp

#include "action_msgs/msg/goal_status_array.hpp"
#include "action_msgs/srv/cancel_goal.hpp"
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
// already included above
// #include "rosidl_typesupport_cpp/visibility_control.h"
#include "rosidl_runtime_c/action_type_support_struct.h"
#include "rosidl_typesupport_cpp/action_type_support.hpp"
// already included above
// #include "rosidl_typesupport_cpp/message_type_support.hpp"
// already included above
// #include "rosidl_typesupport_cpp/service_type_support.hpp"

namespace g_arm_msgs
{

namespace action
{

namespace rosidl_typesupport_cpp
{

static rosidl_action_type_support_t GoToPose_action_type_support_handle = {
  NULL, NULL, NULL, NULL, NULL,
  &g_arm_msgs__action__GoToPose__get_type_hash,
  &g_arm_msgs__action__GoToPose__get_type_description,
  &g_arm_msgs__action__GoToPose__get_type_description_sources,
};

}  // namespace rosidl_typesupport_cpp

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_typesupport_cpp
{

template<>
ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
get_action_type_support_handle<g_arm_msgs::action::GoToPose>()
{
  using ::g_arm_msgs::action::rosidl_typesupport_cpp::GoToPose_action_type_support_handle;
  // Thread-safe by always writing the same values to the static struct
  GoToPose_action_type_support_handle.goal_service_type_support = get_service_type_support_handle<::g_arm_msgs::action::GoToPose::Impl::SendGoalService>();
  GoToPose_action_type_support_handle.result_service_type_support = get_service_type_support_handle<::g_arm_msgs::action::GoToPose::Impl::GetResultService>();
  GoToPose_action_type_support_handle.cancel_service_type_support = get_service_type_support_handle<::g_arm_msgs::action::GoToPose::Impl::CancelGoalService>();
  GoToPose_action_type_support_handle.feedback_message_type_support = get_message_type_support_handle<::g_arm_msgs::action::GoToPose::Impl::FeedbackMessage>();
  GoToPose_action_type_support_handle.status_message_type_support = get_message_type_support_handle<::g_arm_msgs::action::GoToPose::Impl::GoalStatusMessage>();
  return &GoToPose_action_type_support_handle;
}

}  // namespace rosidl_typesupport_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_CPP_PUBLIC
const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(rosidl_typesupport_cpp, g_arm_msgs, action, GoToPose)() {
  return ::rosidl_typesupport_cpp::get_action_type_support_handle<g_arm_msgs::action::GoToPose>();
}

#ifdef __cplusplus
}
#endif
