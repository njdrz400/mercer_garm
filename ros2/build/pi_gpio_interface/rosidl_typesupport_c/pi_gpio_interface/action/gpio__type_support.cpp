// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from pi_gpio_interface:action/GPIO.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "pi_gpio_interface/action/detail/gpio__struct.h"
#include "pi_gpio_interface/action/detail/gpio__type_support.h"
#include "pi_gpio_interface/action/detail/gpio__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace pi_gpio_interface
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _GPIO_Goal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GPIO_Goal_type_support_ids_t;

static const _GPIO_Goal_type_support_ids_t _GPIO_Goal_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GPIO_Goal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GPIO_Goal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GPIO_Goal_type_support_symbol_names_t _GPIO_Goal_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pi_gpio_interface, action, GPIO_Goal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pi_gpio_interface, action, GPIO_Goal)),
  }
};

typedef struct _GPIO_Goal_type_support_data_t
{
  void * data[2];
} _GPIO_Goal_type_support_data_t;

static _GPIO_Goal_type_support_data_t _GPIO_Goal_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GPIO_Goal_message_typesupport_map = {
  2,
  "pi_gpio_interface",
  &_GPIO_Goal_message_typesupport_ids.typesupport_identifier[0],
  &_GPIO_Goal_message_typesupport_symbol_names.symbol_name[0],
  &_GPIO_Goal_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GPIO_Goal_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GPIO_Goal_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &pi_gpio_interface__action__GPIO_Goal__get_type_hash,
  &pi_gpio_interface__action__GPIO_Goal__get_type_description,
  &pi_gpio_interface__action__GPIO_Goal__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace pi_gpio_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, pi_gpio_interface, action, GPIO_Goal)() {
  return &::pi_gpio_interface::action::rosidl_typesupport_c::GPIO_Goal_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__type_support.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace pi_gpio_interface
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _GPIO_Result_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GPIO_Result_type_support_ids_t;

static const _GPIO_Result_type_support_ids_t _GPIO_Result_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GPIO_Result_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GPIO_Result_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GPIO_Result_type_support_symbol_names_t _GPIO_Result_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pi_gpio_interface, action, GPIO_Result)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pi_gpio_interface, action, GPIO_Result)),
  }
};

typedef struct _GPIO_Result_type_support_data_t
{
  void * data[2];
} _GPIO_Result_type_support_data_t;

static _GPIO_Result_type_support_data_t _GPIO_Result_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GPIO_Result_message_typesupport_map = {
  2,
  "pi_gpio_interface",
  &_GPIO_Result_message_typesupport_ids.typesupport_identifier[0],
  &_GPIO_Result_message_typesupport_symbol_names.symbol_name[0],
  &_GPIO_Result_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GPIO_Result_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GPIO_Result_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &pi_gpio_interface__action__GPIO_Result__get_type_hash,
  &pi_gpio_interface__action__GPIO_Result__get_type_description,
  &pi_gpio_interface__action__GPIO_Result__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace pi_gpio_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, pi_gpio_interface, action, GPIO_Result)() {
  return &::pi_gpio_interface::action::rosidl_typesupport_c::GPIO_Result_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__type_support.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace pi_gpio_interface
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _GPIO_Feedback_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GPIO_Feedback_type_support_ids_t;

static const _GPIO_Feedback_type_support_ids_t _GPIO_Feedback_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GPIO_Feedback_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GPIO_Feedback_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GPIO_Feedback_type_support_symbol_names_t _GPIO_Feedback_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pi_gpio_interface, action, GPIO_Feedback)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pi_gpio_interface, action, GPIO_Feedback)),
  }
};

typedef struct _GPIO_Feedback_type_support_data_t
{
  void * data[2];
} _GPIO_Feedback_type_support_data_t;

static _GPIO_Feedback_type_support_data_t _GPIO_Feedback_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GPIO_Feedback_message_typesupport_map = {
  2,
  "pi_gpio_interface",
  &_GPIO_Feedback_message_typesupport_ids.typesupport_identifier[0],
  &_GPIO_Feedback_message_typesupport_symbol_names.symbol_name[0],
  &_GPIO_Feedback_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GPIO_Feedback_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GPIO_Feedback_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &pi_gpio_interface__action__GPIO_Feedback__get_type_hash,
  &pi_gpio_interface__action__GPIO_Feedback__get_type_description,
  &pi_gpio_interface__action__GPIO_Feedback__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace pi_gpio_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, pi_gpio_interface, action, GPIO_Feedback)() {
  return &::pi_gpio_interface::action::rosidl_typesupport_c::GPIO_Feedback_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__type_support.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace pi_gpio_interface
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _GPIO_SendGoal_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GPIO_SendGoal_Request_type_support_ids_t;

static const _GPIO_SendGoal_Request_type_support_ids_t _GPIO_SendGoal_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GPIO_SendGoal_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GPIO_SendGoal_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GPIO_SendGoal_Request_type_support_symbol_names_t _GPIO_SendGoal_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pi_gpio_interface, action, GPIO_SendGoal_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pi_gpio_interface, action, GPIO_SendGoal_Request)),
  }
};

typedef struct _GPIO_SendGoal_Request_type_support_data_t
{
  void * data[2];
} _GPIO_SendGoal_Request_type_support_data_t;

static _GPIO_SendGoal_Request_type_support_data_t _GPIO_SendGoal_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GPIO_SendGoal_Request_message_typesupport_map = {
  2,
  "pi_gpio_interface",
  &_GPIO_SendGoal_Request_message_typesupport_ids.typesupport_identifier[0],
  &_GPIO_SendGoal_Request_message_typesupport_symbol_names.symbol_name[0],
  &_GPIO_SendGoal_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GPIO_SendGoal_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GPIO_SendGoal_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &pi_gpio_interface__action__GPIO_SendGoal_Request__get_type_hash,
  &pi_gpio_interface__action__GPIO_SendGoal_Request__get_type_description,
  &pi_gpio_interface__action__GPIO_SendGoal_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace pi_gpio_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, pi_gpio_interface, action, GPIO_SendGoal_Request)() {
  return &::pi_gpio_interface::action::rosidl_typesupport_c::GPIO_SendGoal_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__type_support.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace pi_gpio_interface
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _GPIO_SendGoal_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GPIO_SendGoal_Response_type_support_ids_t;

static const _GPIO_SendGoal_Response_type_support_ids_t _GPIO_SendGoal_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GPIO_SendGoal_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GPIO_SendGoal_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GPIO_SendGoal_Response_type_support_symbol_names_t _GPIO_SendGoal_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pi_gpio_interface, action, GPIO_SendGoal_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pi_gpio_interface, action, GPIO_SendGoal_Response)),
  }
};

typedef struct _GPIO_SendGoal_Response_type_support_data_t
{
  void * data[2];
} _GPIO_SendGoal_Response_type_support_data_t;

static _GPIO_SendGoal_Response_type_support_data_t _GPIO_SendGoal_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GPIO_SendGoal_Response_message_typesupport_map = {
  2,
  "pi_gpio_interface",
  &_GPIO_SendGoal_Response_message_typesupport_ids.typesupport_identifier[0],
  &_GPIO_SendGoal_Response_message_typesupport_symbol_names.symbol_name[0],
  &_GPIO_SendGoal_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GPIO_SendGoal_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GPIO_SendGoal_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &pi_gpio_interface__action__GPIO_SendGoal_Response__get_type_hash,
  &pi_gpio_interface__action__GPIO_SendGoal_Response__get_type_description,
  &pi_gpio_interface__action__GPIO_SendGoal_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace pi_gpio_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, pi_gpio_interface, action, GPIO_SendGoal_Response)() {
  return &::pi_gpio_interface::action::rosidl_typesupport_c::GPIO_SendGoal_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__type_support.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace pi_gpio_interface
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _GPIO_SendGoal_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GPIO_SendGoal_Event_type_support_ids_t;

static const _GPIO_SendGoal_Event_type_support_ids_t _GPIO_SendGoal_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GPIO_SendGoal_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GPIO_SendGoal_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GPIO_SendGoal_Event_type_support_symbol_names_t _GPIO_SendGoal_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pi_gpio_interface, action, GPIO_SendGoal_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pi_gpio_interface, action, GPIO_SendGoal_Event)),
  }
};

typedef struct _GPIO_SendGoal_Event_type_support_data_t
{
  void * data[2];
} _GPIO_SendGoal_Event_type_support_data_t;

static _GPIO_SendGoal_Event_type_support_data_t _GPIO_SendGoal_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GPIO_SendGoal_Event_message_typesupport_map = {
  2,
  "pi_gpio_interface",
  &_GPIO_SendGoal_Event_message_typesupport_ids.typesupport_identifier[0],
  &_GPIO_SendGoal_Event_message_typesupport_symbol_names.symbol_name[0],
  &_GPIO_SendGoal_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GPIO_SendGoal_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GPIO_SendGoal_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &pi_gpio_interface__action__GPIO_SendGoal_Event__get_type_hash,
  &pi_gpio_interface__action__GPIO_SendGoal_Event__get_type_description,
  &pi_gpio_interface__action__GPIO_SendGoal_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace pi_gpio_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, pi_gpio_interface, action, GPIO_SendGoal_Event)() {
  return &::pi_gpio_interface::action::rosidl_typesupport_c::GPIO_SendGoal_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace pi_gpio_interface
{

namespace action
{

namespace rosidl_typesupport_c
{
typedef struct _GPIO_SendGoal_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GPIO_SendGoal_type_support_ids_t;

static const _GPIO_SendGoal_type_support_ids_t _GPIO_SendGoal_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GPIO_SendGoal_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GPIO_SendGoal_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GPIO_SendGoal_type_support_symbol_names_t _GPIO_SendGoal_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pi_gpio_interface, action, GPIO_SendGoal)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pi_gpio_interface, action, GPIO_SendGoal)),
  }
};

typedef struct _GPIO_SendGoal_type_support_data_t
{
  void * data[2];
} _GPIO_SendGoal_type_support_data_t;

static _GPIO_SendGoal_type_support_data_t _GPIO_SendGoal_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GPIO_SendGoal_service_typesupport_map = {
  2,
  "pi_gpio_interface",
  &_GPIO_SendGoal_service_typesupport_ids.typesupport_identifier[0],
  &_GPIO_SendGoal_service_typesupport_symbol_names.symbol_name[0],
  &_GPIO_SendGoal_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t GPIO_SendGoal_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GPIO_SendGoal_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &GPIO_SendGoal_Request_message_type_support_handle,
  &GPIO_SendGoal_Response_message_type_support_handle,
  &GPIO_SendGoal_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    pi_gpio_interface,
    action,
    GPIO_SendGoal
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    pi_gpio_interface,
    action,
    GPIO_SendGoal
  ),
  &pi_gpio_interface__action__GPIO_SendGoal__get_type_hash,
  &pi_gpio_interface__action__GPIO_SendGoal__get_type_description,
  &pi_gpio_interface__action__GPIO_SendGoal__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace pi_gpio_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, pi_gpio_interface, action, GPIO_SendGoal)() {
  return &::pi_gpio_interface::action::rosidl_typesupport_c::GPIO_SendGoal_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__type_support.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace pi_gpio_interface
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _GPIO_GetResult_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GPIO_GetResult_Request_type_support_ids_t;

static const _GPIO_GetResult_Request_type_support_ids_t _GPIO_GetResult_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GPIO_GetResult_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GPIO_GetResult_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GPIO_GetResult_Request_type_support_symbol_names_t _GPIO_GetResult_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pi_gpio_interface, action, GPIO_GetResult_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pi_gpio_interface, action, GPIO_GetResult_Request)),
  }
};

typedef struct _GPIO_GetResult_Request_type_support_data_t
{
  void * data[2];
} _GPIO_GetResult_Request_type_support_data_t;

static _GPIO_GetResult_Request_type_support_data_t _GPIO_GetResult_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GPIO_GetResult_Request_message_typesupport_map = {
  2,
  "pi_gpio_interface",
  &_GPIO_GetResult_Request_message_typesupport_ids.typesupport_identifier[0],
  &_GPIO_GetResult_Request_message_typesupport_symbol_names.symbol_name[0],
  &_GPIO_GetResult_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GPIO_GetResult_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GPIO_GetResult_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &pi_gpio_interface__action__GPIO_GetResult_Request__get_type_hash,
  &pi_gpio_interface__action__GPIO_GetResult_Request__get_type_description,
  &pi_gpio_interface__action__GPIO_GetResult_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace pi_gpio_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, pi_gpio_interface, action, GPIO_GetResult_Request)() {
  return &::pi_gpio_interface::action::rosidl_typesupport_c::GPIO_GetResult_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__type_support.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace pi_gpio_interface
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _GPIO_GetResult_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GPIO_GetResult_Response_type_support_ids_t;

static const _GPIO_GetResult_Response_type_support_ids_t _GPIO_GetResult_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GPIO_GetResult_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GPIO_GetResult_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GPIO_GetResult_Response_type_support_symbol_names_t _GPIO_GetResult_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pi_gpio_interface, action, GPIO_GetResult_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pi_gpio_interface, action, GPIO_GetResult_Response)),
  }
};

typedef struct _GPIO_GetResult_Response_type_support_data_t
{
  void * data[2];
} _GPIO_GetResult_Response_type_support_data_t;

static _GPIO_GetResult_Response_type_support_data_t _GPIO_GetResult_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GPIO_GetResult_Response_message_typesupport_map = {
  2,
  "pi_gpio_interface",
  &_GPIO_GetResult_Response_message_typesupport_ids.typesupport_identifier[0],
  &_GPIO_GetResult_Response_message_typesupport_symbol_names.symbol_name[0],
  &_GPIO_GetResult_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GPIO_GetResult_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GPIO_GetResult_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &pi_gpio_interface__action__GPIO_GetResult_Response__get_type_hash,
  &pi_gpio_interface__action__GPIO_GetResult_Response__get_type_description,
  &pi_gpio_interface__action__GPIO_GetResult_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace pi_gpio_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, pi_gpio_interface, action, GPIO_GetResult_Response)() {
  return &::pi_gpio_interface::action::rosidl_typesupport_c::GPIO_GetResult_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__type_support.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace pi_gpio_interface
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _GPIO_GetResult_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GPIO_GetResult_Event_type_support_ids_t;

static const _GPIO_GetResult_Event_type_support_ids_t _GPIO_GetResult_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GPIO_GetResult_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GPIO_GetResult_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GPIO_GetResult_Event_type_support_symbol_names_t _GPIO_GetResult_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pi_gpio_interface, action, GPIO_GetResult_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pi_gpio_interface, action, GPIO_GetResult_Event)),
  }
};

typedef struct _GPIO_GetResult_Event_type_support_data_t
{
  void * data[2];
} _GPIO_GetResult_Event_type_support_data_t;

static _GPIO_GetResult_Event_type_support_data_t _GPIO_GetResult_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GPIO_GetResult_Event_message_typesupport_map = {
  2,
  "pi_gpio_interface",
  &_GPIO_GetResult_Event_message_typesupport_ids.typesupport_identifier[0],
  &_GPIO_GetResult_Event_message_typesupport_symbol_names.symbol_name[0],
  &_GPIO_GetResult_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GPIO_GetResult_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GPIO_GetResult_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &pi_gpio_interface__action__GPIO_GetResult_Event__get_type_hash,
  &pi_gpio_interface__action__GPIO_GetResult_Event__get_type_description,
  &pi_gpio_interface__action__GPIO_GetResult_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace pi_gpio_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, pi_gpio_interface, action, GPIO_GetResult_Event)() {
  return &::pi_gpio_interface::action::rosidl_typesupport_c::GPIO_GetResult_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
// already included above
// #include "service_msgs/msg/service_event_info.h"
// already included above
// #include "builtin_interfaces/msg/time.h"

namespace pi_gpio_interface
{

namespace action
{

namespace rosidl_typesupport_c
{
typedef struct _GPIO_GetResult_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GPIO_GetResult_type_support_ids_t;

static const _GPIO_GetResult_type_support_ids_t _GPIO_GetResult_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GPIO_GetResult_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GPIO_GetResult_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GPIO_GetResult_type_support_symbol_names_t _GPIO_GetResult_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pi_gpio_interface, action, GPIO_GetResult)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pi_gpio_interface, action, GPIO_GetResult)),
  }
};

typedef struct _GPIO_GetResult_type_support_data_t
{
  void * data[2];
} _GPIO_GetResult_type_support_data_t;

static _GPIO_GetResult_type_support_data_t _GPIO_GetResult_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GPIO_GetResult_service_typesupport_map = {
  2,
  "pi_gpio_interface",
  &_GPIO_GetResult_service_typesupport_ids.typesupport_identifier[0],
  &_GPIO_GetResult_service_typesupport_symbol_names.symbol_name[0],
  &_GPIO_GetResult_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t GPIO_GetResult_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GPIO_GetResult_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &GPIO_GetResult_Request_message_type_support_handle,
  &GPIO_GetResult_Response_message_type_support_handle,
  &GPIO_GetResult_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    pi_gpio_interface,
    action,
    GPIO_GetResult
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    pi_gpio_interface,
    action,
    GPIO_GetResult
  ),
  &pi_gpio_interface__action__GPIO_GetResult__get_type_hash,
  &pi_gpio_interface__action__GPIO_GetResult__get_type_description,
  &pi_gpio_interface__action__GPIO_GetResult__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace pi_gpio_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, pi_gpio_interface, action, GPIO_GetResult)() {
  return &::pi_gpio_interface::action::rosidl_typesupport_c::GPIO_GetResult_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__struct.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__type_support.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace pi_gpio_interface
{

namespace action
{

namespace rosidl_typesupport_c
{

typedef struct _GPIO_FeedbackMessage_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _GPIO_FeedbackMessage_type_support_ids_t;

static const _GPIO_FeedbackMessage_type_support_ids_t _GPIO_FeedbackMessage_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _GPIO_FeedbackMessage_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _GPIO_FeedbackMessage_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _GPIO_FeedbackMessage_type_support_symbol_names_t _GPIO_FeedbackMessage_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, pi_gpio_interface, action, GPIO_FeedbackMessage)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, pi_gpio_interface, action, GPIO_FeedbackMessage)),
  }
};

typedef struct _GPIO_FeedbackMessage_type_support_data_t
{
  void * data[2];
} _GPIO_FeedbackMessage_type_support_data_t;

static _GPIO_FeedbackMessage_type_support_data_t _GPIO_FeedbackMessage_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _GPIO_FeedbackMessage_message_typesupport_map = {
  2,
  "pi_gpio_interface",
  &_GPIO_FeedbackMessage_message_typesupport_ids.typesupport_identifier[0],
  &_GPIO_FeedbackMessage_message_typesupport_symbol_names.symbol_name[0],
  &_GPIO_FeedbackMessage_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t GPIO_FeedbackMessage_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_GPIO_FeedbackMessage_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &pi_gpio_interface__action__GPIO_FeedbackMessage__get_type_hash,
  &pi_gpio_interface__action__GPIO_FeedbackMessage__get_type_description,
  &pi_gpio_interface__action__GPIO_FeedbackMessage__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace action

}  // namespace pi_gpio_interface

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, pi_gpio_interface, action, GPIO_FeedbackMessage)() {
  return &::pi_gpio_interface::action::rosidl_typesupport_c::GPIO_FeedbackMessage_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

#include "action_msgs/msg/goal_status_array.h"
#include "action_msgs/srv/cancel_goal.h"
#include "pi_gpio_interface/action/gpio.h"
// already included above
// #include "pi_gpio_interface/action/detail/gpio__type_support.h"

static rosidl_action_type_support_t _pi_gpio_interface__action__GPIO__typesupport_c = {
  NULL, NULL, NULL, NULL, NULL,
  &pi_gpio_interface__action__GPIO__get_type_hash,
  &pi_gpio_interface__action__GPIO__get_type_description,
  &pi_gpio_interface__action__GPIO__get_type_description_sources,
};

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_action_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__ACTION_SYMBOL_NAME(
  rosidl_typesupport_c, pi_gpio_interface, action, GPIO)()
{
  // Thread-safe by always writing the same values to the static struct
  _pi_gpio_interface__action__GPIO__typesupport_c.goal_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, pi_gpio_interface, action, GPIO_SendGoal)();
  _pi_gpio_interface__action__GPIO__typesupport_c.result_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, pi_gpio_interface, action, GPIO_GetResult)();
  _pi_gpio_interface__action__GPIO__typesupport_c.cancel_service_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, srv, CancelGoal)();
  _pi_gpio_interface__action__GPIO__typesupport_c.feedback_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, pi_gpio_interface, action, GPIO_FeedbackMessage)();
  _pi_gpio_interface__action__GPIO__typesupport_c.status_message_type_support =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c, action_msgs, msg, GoalStatusArray)();

  return &_pi_gpio_interface__action__GPIO__typesupport_c;
}

#ifdef __cplusplus
}
#endif
