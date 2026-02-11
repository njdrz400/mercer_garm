// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from g_arm_msgs:action/GoToPose.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g_arm_msgs/action/go_to_pose.hpp"


#ifndef G_ARM_MSGS__ACTION__DETAIL__GO_TO_POSE__TRAITS_HPP_
#define G_ARM_MSGS__ACTION__DETAIL__GO_TO_POSE__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'target'
#include "geometry_msgs/msg/detail/pose_stamped__traits.hpp"

namespace g_arm_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const GoToPose_Goal & msg,
  std::ostream & out)
{
  out << "{";
  // member: target
  {
    out << "target: ";
    to_flow_style_yaml(msg.target, out);
    out << ", ";
  }

  // member: pos_tolerance_m
  {
    out << "pos_tolerance_m: ";
    rosidl_generator_traits::value_to_yaml(msg.pos_tolerance_m, out);
    out << ", ";
  }

  // member: ang_tolerance_rad
  {
    out << "ang_tolerance_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.ang_tolerance_rad, out);
    out << ", ";
  }

  // member: timeout_sec
  {
    out << "timeout_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.timeout_sec, out);
    out << ", ";
  }

  // member: allow_orientation
  {
    out << "allow_orientation: ";
    rosidl_generator_traits::value_to_yaml(msg.allow_orientation, out);
    out << ", ";
  }

  // member: planner_frame
  {
    out << "planner_frame: ";
    rosidl_generator_traits::value_to_yaml(msg.planner_frame, out);
    out << ", ";
  }

  // member: speed_scale
  {
    out << "speed_scale: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_scale, out);
    out << ", ";
  }

  // member: max_joint_vel
  {
    out << "max_joint_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.max_joint_vel, out);
    out << ", ";
  }

  // member: max_joint_acc
  {
    out << "max_joint_acc: ";
    rosidl_generator_traits::value_to_yaml(msg.max_joint_acc, out);
    out << ", ";
  }

  // member: electromagnet_on
  {
    out << "electromagnet_on: ";
    rosidl_generator_traits::value_to_yaml(msg.electromagnet_on, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoToPose_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: target
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "target:\n";
    to_block_style_yaml(msg.target, out, indentation + 2);
  }

  // member: pos_tolerance_m
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pos_tolerance_m: ";
    rosidl_generator_traits::value_to_yaml(msg.pos_tolerance_m, out);
    out << "\n";
  }

  // member: ang_tolerance_rad
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ang_tolerance_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.ang_tolerance_rad, out);
    out << "\n";
  }

  // member: timeout_sec
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "timeout_sec: ";
    rosidl_generator_traits::value_to_yaml(msg.timeout_sec, out);
    out << "\n";
  }

  // member: allow_orientation
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "allow_orientation: ";
    rosidl_generator_traits::value_to_yaml(msg.allow_orientation, out);
    out << "\n";
  }

  // member: planner_frame
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "planner_frame: ";
    rosidl_generator_traits::value_to_yaml(msg.planner_frame, out);
    out << "\n";
  }

  // member: speed_scale
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed_scale: ";
    rosidl_generator_traits::value_to_yaml(msg.speed_scale, out);
    out << "\n";
  }

  // member: max_joint_vel
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_joint_vel: ";
    rosidl_generator_traits::value_to_yaml(msg.max_joint_vel, out);
    out << "\n";
  }

  // member: max_joint_acc
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "max_joint_acc: ";
    rosidl_generator_traits::value_to_yaml(msg.max_joint_acc, out);
    out << "\n";
  }

  // member: electromagnet_on
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "electromagnet_on: ";
    rosidl_generator_traits::value_to_yaml(msg.electromagnet_on, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoToPose_Goal & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_generator_traits
{

[[deprecated("use g_arm_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g_arm_msgs::action::GoToPose_Goal & msg,
  std::ostream & out, size_t indentation = 0)
{
  g_arm_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g_arm_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const g_arm_msgs::action::GoToPose_Goal & msg)
{
  return g_arm_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<g_arm_msgs::action::GoToPose_Goal>()
{
  return "g_arm_msgs::action::GoToPose_Goal";
}

template<>
inline const char * name<g_arm_msgs::action::GoToPose_Goal>()
{
  return "g_arm_msgs/action/GoToPose_Goal";
}

template<>
struct has_fixed_size<g_arm_msgs::action::GoToPose_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<g_arm_msgs::action::GoToPose_Goal>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<g_arm_msgs::action::GoToPose_Goal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace g_arm_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const GoToPose_Result & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: error_code
  {
    out << "error_code: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << ", ";
  }

  // member: final_pos_error_m
  {
    out << "final_pos_error_m: ";
    rosidl_generator_traits::value_to_yaml(msg.final_pos_error_m, out);
    out << ", ";
  }

  // member: final_ang_error_rad
  {
    out << "final_ang_error_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.final_ang_error_rad, out);
    out << ", ";
  }

  // member: final_joint_positions
  {
    if (msg.final_joint_positions.size() == 0) {
      out << "final_joint_positions: []";
    } else {
      out << "final_joint_positions: [";
      size_t pending_items = msg.final_joint_positions.size();
      for (auto item : msg.final_joint_positions) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoToPose_Result & msg,
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

  // member: error_code
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "error_code: ";
    rosidl_generator_traits::value_to_yaml(msg.error_code, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
  }

  // member: final_pos_error_m
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "final_pos_error_m: ";
    rosidl_generator_traits::value_to_yaml(msg.final_pos_error_m, out);
    out << "\n";
  }

  // member: final_ang_error_rad
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "final_ang_error_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.final_ang_error_rad, out);
    out << "\n";
  }

  // member: final_joint_positions
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.final_joint_positions.size() == 0) {
      out << "final_joint_positions: []\n";
    } else {
      out << "final_joint_positions:\n";
      for (auto item : msg.final_joint_positions) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoToPose_Result & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_generator_traits
{

[[deprecated("use g_arm_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g_arm_msgs::action::GoToPose_Result & msg,
  std::ostream & out, size_t indentation = 0)
{
  g_arm_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g_arm_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const g_arm_msgs::action::GoToPose_Result & msg)
{
  return g_arm_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<g_arm_msgs::action::GoToPose_Result>()
{
  return "g_arm_msgs::action::GoToPose_Result";
}

template<>
inline const char * name<g_arm_msgs::action::GoToPose_Result>()
{
  return "g_arm_msgs/action/GoToPose_Result";
}

template<>
struct has_fixed_size<g_arm_msgs::action::GoToPose_Result>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<g_arm_msgs::action::GoToPose_Result>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<g_arm_msgs::action::GoToPose_Result>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace g_arm_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const GoToPose_Feedback & msg,
  std::ostream & out)
{
  out << "{";
  // member: state
  {
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << ", ";
  }

  // member: pos_error_m
  {
    out << "pos_error_m: ";
    rosidl_generator_traits::value_to_yaml(msg.pos_error_m, out);
    out << ", ";
  }

  // member: ang_error_rad
  {
    out << "ang_error_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.ang_error_rad, out);
    out << ", ";
  }

  // member: progress
  {
    out << "progress: ";
    rosidl_generator_traits::value_to_yaml(msg.progress, out);
    out << ", ";
  }

  // member: detail
  {
    out << "detail: ";
    rosidl_generator_traits::value_to_yaml(msg.detail, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoToPose_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: state
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "state: ";
    rosidl_generator_traits::value_to_yaml(msg.state, out);
    out << "\n";
  }

  // member: pos_error_m
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pos_error_m: ";
    rosidl_generator_traits::value_to_yaml(msg.pos_error_m, out);
    out << "\n";
  }

  // member: ang_error_rad
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "ang_error_rad: ";
    rosidl_generator_traits::value_to_yaml(msg.ang_error_rad, out);
    out << "\n";
  }

  // member: progress
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "progress: ";
    rosidl_generator_traits::value_to_yaml(msg.progress, out);
    out << "\n";
  }

  // member: detail
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "detail: ";
    rosidl_generator_traits::value_to_yaml(msg.detail, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoToPose_Feedback & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_generator_traits
{

[[deprecated("use g_arm_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g_arm_msgs::action::GoToPose_Feedback & msg,
  std::ostream & out, size_t indentation = 0)
{
  g_arm_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g_arm_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const g_arm_msgs::action::GoToPose_Feedback & msg)
{
  return g_arm_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<g_arm_msgs::action::GoToPose_Feedback>()
{
  return "g_arm_msgs::action::GoToPose_Feedback";
}

template<>
inline const char * name<g_arm_msgs::action::GoToPose_Feedback>()
{
  return "g_arm_msgs/action/GoToPose_Feedback";
}

template<>
struct has_fixed_size<g_arm_msgs::action::GoToPose_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<g_arm_msgs::action::GoToPose_Feedback>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<g_arm_msgs::action::GoToPose_Feedback>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'goal'
#include "g_arm_msgs/action/detail/go_to_pose__traits.hpp"

namespace g_arm_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const GoToPose_SendGoal_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: goal
  {
    out << "goal: ";
    to_flow_style_yaml(msg.goal, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoToPose_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: goal
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal:\n";
    to_block_style_yaml(msg.goal, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoToPose_SendGoal_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_generator_traits
{

[[deprecated("use g_arm_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g_arm_msgs::action::GoToPose_SendGoal_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  g_arm_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g_arm_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const g_arm_msgs::action::GoToPose_SendGoal_Request & msg)
{
  return g_arm_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<g_arm_msgs::action::GoToPose_SendGoal_Request>()
{
  return "g_arm_msgs::action::GoToPose_SendGoal_Request";
}

template<>
inline const char * name<g_arm_msgs::action::GoToPose_SendGoal_Request>()
{
  return "g_arm_msgs/action/GoToPose_SendGoal_Request";
}

template<>
struct has_fixed_size<g_arm_msgs::action::GoToPose_SendGoal_Request>
  : std::integral_constant<bool, has_fixed_size<g_arm_msgs::action::GoToPose_Goal>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<g_arm_msgs::action::GoToPose_SendGoal_Request>
  : std::integral_constant<bool, has_bounded_size<g_arm_msgs::action::GoToPose_Goal>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<g_arm_msgs::action::GoToPose_SendGoal_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__traits.hpp"

namespace g_arm_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const GoToPose_SendGoal_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: accepted
  {
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << ", ";
  }

  // member: stamp
  {
    out << "stamp: ";
    to_flow_style_yaml(msg.stamp, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoToPose_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: accepted
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "accepted: ";
    rosidl_generator_traits::value_to_yaml(msg.accepted, out);
    out << "\n";
  }

  // member: stamp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "stamp:\n";
    to_block_style_yaml(msg.stamp, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoToPose_SendGoal_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_generator_traits
{

[[deprecated("use g_arm_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g_arm_msgs::action::GoToPose_SendGoal_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  g_arm_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g_arm_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const g_arm_msgs::action::GoToPose_SendGoal_Response & msg)
{
  return g_arm_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<g_arm_msgs::action::GoToPose_SendGoal_Response>()
{
  return "g_arm_msgs::action::GoToPose_SendGoal_Response";
}

template<>
inline const char * name<g_arm_msgs::action::GoToPose_SendGoal_Response>()
{
  return "g_arm_msgs/action/GoToPose_SendGoal_Response";
}

template<>
struct has_fixed_size<g_arm_msgs::action::GoToPose_SendGoal_Response>
  : std::integral_constant<bool, has_fixed_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct has_bounded_size<g_arm_msgs::action::GoToPose_SendGoal_Response>
  : std::integral_constant<bool, has_bounded_size<builtin_interfaces::msg::Time>::value> {};

template<>
struct is_message<g_arm_msgs::action::GoToPose_SendGoal_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace g_arm_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const GoToPose_SendGoal_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoToPose_SendGoal_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoToPose_SendGoal_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_generator_traits
{

[[deprecated("use g_arm_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g_arm_msgs::action::GoToPose_SendGoal_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  g_arm_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g_arm_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const g_arm_msgs::action::GoToPose_SendGoal_Event & msg)
{
  return g_arm_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<g_arm_msgs::action::GoToPose_SendGoal_Event>()
{
  return "g_arm_msgs::action::GoToPose_SendGoal_Event";
}

template<>
inline const char * name<g_arm_msgs::action::GoToPose_SendGoal_Event>()
{
  return "g_arm_msgs/action/GoToPose_SendGoal_Event";
}

template<>
struct has_fixed_size<g_arm_msgs::action::GoToPose_SendGoal_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<g_arm_msgs::action::GoToPose_SendGoal_Event>
  : std::integral_constant<bool, has_bounded_size<g_arm_msgs::action::GoToPose_SendGoal_Request>::value && has_bounded_size<g_arm_msgs::action::GoToPose_SendGoal_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<g_arm_msgs::action::GoToPose_SendGoal_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<g_arm_msgs::action::GoToPose_SendGoal>()
{
  return "g_arm_msgs::action::GoToPose_SendGoal";
}

template<>
inline const char * name<g_arm_msgs::action::GoToPose_SendGoal>()
{
  return "g_arm_msgs/action/GoToPose_SendGoal";
}

template<>
struct has_fixed_size<g_arm_msgs::action::GoToPose_SendGoal>
  : std::integral_constant<
    bool,
    has_fixed_size<g_arm_msgs::action::GoToPose_SendGoal_Request>::value &&
    has_fixed_size<g_arm_msgs::action::GoToPose_SendGoal_Response>::value
  >
{
};

template<>
struct has_bounded_size<g_arm_msgs::action::GoToPose_SendGoal>
  : std::integral_constant<
    bool,
    has_bounded_size<g_arm_msgs::action::GoToPose_SendGoal_Request>::value &&
    has_bounded_size<g_arm_msgs::action::GoToPose_SendGoal_Response>::value
  >
{
};

template<>
struct is_service<g_arm_msgs::action::GoToPose_SendGoal>
  : std::true_type
{
};

template<>
struct is_service_request<g_arm_msgs::action::GoToPose_SendGoal_Request>
  : std::true_type
{
};

template<>
struct is_service_response<g_arm_msgs::action::GoToPose_SendGoal_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"

namespace g_arm_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const GoToPose_GetResult_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoToPose_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoToPose_GetResult_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_generator_traits
{

[[deprecated("use g_arm_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g_arm_msgs::action::GoToPose_GetResult_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  g_arm_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g_arm_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const g_arm_msgs::action::GoToPose_GetResult_Request & msg)
{
  return g_arm_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<g_arm_msgs::action::GoToPose_GetResult_Request>()
{
  return "g_arm_msgs::action::GoToPose_GetResult_Request";
}

template<>
inline const char * name<g_arm_msgs::action::GoToPose_GetResult_Request>()
{
  return "g_arm_msgs/action/GoToPose_GetResult_Request";
}

template<>
struct has_fixed_size<g_arm_msgs::action::GoToPose_GetResult_Request>
  : std::integral_constant<bool, has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<g_arm_msgs::action::GoToPose_GetResult_Request>
  : std::integral_constant<bool, has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<g_arm_msgs::action::GoToPose_GetResult_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'result'
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__traits.hpp"

namespace g_arm_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const GoToPose_GetResult_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: status
  {
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << ", ";
  }

  // member: result
  {
    out << "result: ";
    to_flow_style_yaml(msg.result, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoToPose_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: status
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "status: ";
    rosidl_generator_traits::value_to_yaml(msg.status, out);
    out << "\n";
  }

  // member: result
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "result:\n";
    to_block_style_yaml(msg.result, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoToPose_GetResult_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_generator_traits
{

[[deprecated("use g_arm_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g_arm_msgs::action::GoToPose_GetResult_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  g_arm_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g_arm_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const g_arm_msgs::action::GoToPose_GetResult_Response & msg)
{
  return g_arm_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<g_arm_msgs::action::GoToPose_GetResult_Response>()
{
  return "g_arm_msgs::action::GoToPose_GetResult_Response";
}

template<>
inline const char * name<g_arm_msgs::action::GoToPose_GetResult_Response>()
{
  return "g_arm_msgs/action/GoToPose_GetResult_Response";
}

template<>
struct has_fixed_size<g_arm_msgs::action::GoToPose_GetResult_Response>
  : std::integral_constant<bool, has_fixed_size<g_arm_msgs::action::GoToPose_Result>::value> {};

template<>
struct has_bounded_size<g_arm_msgs::action::GoToPose_GetResult_Response>
  : std::integral_constant<bool, has_bounded_size<g_arm_msgs::action::GoToPose_Result>::value> {};

template<>
struct is_message<g_arm_msgs::action::GoToPose_GetResult_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace g_arm_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const GoToPose_GetResult_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoToPose_GetResult_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoToPose_GetResult_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_generator_traits
{

[[deprecated("use g_arm_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g_arm_msgs::action::GoToPose_GetResult_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  g_arm_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g_arm_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const g_arm_msgs::action::GoToPose_GetResult_Event & msg)
{
  return g_arm_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<g_arm_msgs::action::GoToPose_GetResult_Event>()
{
  return "g_arm_msgs::action::GoToPose_GetResult_Event";
}

template<>
inline const char * name<g_arm_msgs::action::GoToPose_GetResult_Event>()
{
  return "g_arm_msgs/action/GoToPose_GetResult_Event";
}

template<>
struct has_fixed_size<g_arm_msgs::action::GoToPose_GetResult_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<g_arm_msgs::action::GoToPose_GetResult_Event>
  : std::integral_constant<bool, has_bounded_size<g_arm_msgs::action::GoToPose_GetResult_Request>::value && has_bounded_size<g_arm_msgs::action::GoToPose_GetResult_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<g_arm_msgs::action::GoToPose_GetResult_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<g_arm_msgs::action::GoToPose_GetResult>()
{
  return "g_arm_msgs::action::GoToPose_GetResult";
}

template<>
inline const char * name<g_arm_msgs::action::GoToPose_GetResult>()
{
  return "g_arm_msgs/action/GoToPose_GetResult";
}

template<>
struct has_fixed_size<g_arm_msgs::action::GoToPose_GetResult>
  : std::integral_constant<
    bool,
    has_fixed_size<g_arm_msgs::action::GoToPose_GetResult_Request>::value &&
    has_fixed_size<g_arm_msgs::action::GoToPose_GetResult_Response>::value
  >
{
};

template<>
struct has_bounded_size<g_arm_msgs::action::GoToPose_GetResult>
  : std::integral_constant<
    bool,
    has_bounded_size<g_arm_msgs::action::GoToPose_GetResult_Request>::value &&
    has_bounded_size<g_arm_msgs::action::GoToPose_GetResult_Response>::value
  >
{
};

template<>
struct is_service<g_arm_msgs::action::GoToPose_GetResult>
  : std::true_type
{
};

template<>
struct is_service_request<g_arm_msgs::action::GoToPose_GetResult_Request>
  : std::true_type
{
};

template<>
struct is_service_response<g_arm_msgs::action::GoToPose_GetResult_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__traits.hpp"
// Member 'feedback'
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__traits.hpp"

namespace g_arm_msgs
{

namespace action
{

inline void to_flow_style_yaml(
  const GoToPose_FeedbackMessage & msg,
  std::ostream & out)
{
  out << "{";
  // member: goal_id
  {
    out << "goal_id: ";
    to_flow_style_yaml(msg.goal_id, out);
    out << ", ";
  }

  // member: feedback
  {
    out << "feedback: ";
    to_flow_style_yaml(msg.feedback, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const GoToPose_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: goal_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "goal_id:\n";
    to_block_style_yaml(msg.goal_id, out, indentation + 2);
  }

  // member: feedback
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "feedback:\n";
    to_block_style_yaml(msg.feedback, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const GoToPose_FeedbackMessage & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace action

}  // namespace g_arm_msgs

namespace rosidl_generator_traits
{

[[deprecated("use g_arm_msgs::action::to_block_style_yaml() instead")]]
inline void to_yaml(
  const g_arm_msgs::action::GoToPose_FeedbackMessage & msg,
  std::ostream & out, size_t indentation = 0)
{
  g_arm_msgs::action::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use g_arm_msgs::action::to_yaml() instead")]]
inline std::string to_yaml(const g_arm_msgs::action::GoToPose_FeedbackMessage & msg)
{
  return g_arm_msgs::action::to_yaml(msg);
}

template<>
inline const char * data_type<g_arm_msgs::action::GoToPose_FeedbackMessage>()
{
  return "g_arm_msgs::action::GoToPose_FeedbackMessage";
}

template<>
inline const char * name<g_arm_msgs::action::GoToPose_FeedbackMessage>()
{
  return "g_arm_msgs/action/GoToPose_FeedbackMessage";
}

template<>
struct has_fixed_size<g_arm_msgs::action::GoToPose_FeedbackMessage>
  : std::integral_constant<bool, has_fixed_size<g_arm_msgs::action::GoToPose_Feedback>::value && has_fixed_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct has_bounded_size<g_arm_msgs::action::GoToPose_FeedbackMessage>
  : std::integral_constant<bool, has_bounded_size<g_arm_msgs::action::GoToPose_Feedback>::value && has_bounded_size<unique_identifier_msgs::msg::UUID>::value> {};

template<>
struct is_message<g_arm_msgs::action::GoToPose_FeedbackMessage>
  : std::true_type {};

}  // namespace rosidl_generator_traits


namespace rosidl_generator_traits
{

template<>
struct is_action<g_arm_msgs::action::GoToPose>
  : std::true_type
{
};

template<>
struct is_action_goal<g_arm_msgs::action::GoToPose_Goal>
  : std::true_type
{
};

template<>
struct is_action_result<g_arm_msgs::action::GoToPose_Result>
  : std::true_type
{
};

template<>
struct is_action_feedback<g_arm_msgs::action::GoToPose_Feedback>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits


#endif  // G_ARM_MSGS__ACTION__DETAIL__GO_TO_POSE__TRAITS_HPP_
