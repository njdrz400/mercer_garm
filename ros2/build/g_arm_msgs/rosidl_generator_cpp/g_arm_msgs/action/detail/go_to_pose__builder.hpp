// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from g_arm_msgs:action/GoToPose.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g_arm_msgs/action/go_to_pose.hpp"


#ifndef G_ARM_MSGS__ACTION__DETAIL__GO_TO_POSE__BUILDER_HPP_
#define G_ARM_MSGS__ACTION__DETAIL__GO_TO_POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace g_arm_msgs
{

namespace action
{

namespace builder
{

class Init_GoToPose_Goal_electromagnet_on
{
public:
  explicit Init_GoToPose_Goal_electromagnet_on(::g_arm_msgs::action::GoToPose_Goal & msg)
  : msg_(msg)
  {}
  ::g_arm_msgs::action::GoToPose_Goal electromagnet_on(::g_arm_msgs::action::GoToPose_Goal::_electromagnet_on_type arg)
  {
    msg_.electromagnet_on = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Goal msg_;
};

class Init_GoToPose_Goal_max_joint_acc
{
public:
  explicit Init_GoToPose_Goal_max_joint_acc(::g_arm_msgs::action::GoToPose_Goal & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Goal_electromagnet_on max_joint_acc(::g_arm_msgs::action::GoToPose_Goal::_max_joint_acc_type arg)
  {
    msg_.max_joint_acc = std::move(arg);
    return Init_GoToPose_Goal_electromagnet_on(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Goal msg_;
};

class Init_GoToPose_Goal_max_joint_vel
{
public:
  explicit Init_GoToPose_Goal_max_joint_vel(::g_arm_msgs::action::GoToPose_Goal & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Goal_max_joint_acc max_joint_vel(::g_arm_msgs::action::GoToPose_Goal::_max_joint_vel_type arg)
  {
    msg_.max_joint_vel = std::move(arg);
    return Init_GoToPose_Goal_max_joint_acc(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Goal msg_;
};

class Init_GoToPose_Goal_speed_scale
{
public:
  explicit Init_GoToPose_Goal_speed_scale(::g_arm_msgs::action::GoToPose_Goal & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Goal_max_joint_vel speed_scale(::g_arm_msgs::action::GoToPose_Goal::_speed_scale_type arg)
  {
    msg_.speed_scale = std::move(arg);
    return Init_GoToPose_Goal_max_joint_vel(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Goal msg_;
};

class Init_GoToPose_Goal_planner_frame
{
public:
  explicit Init_GoToPose_Goal_planner_frame(::g_arm_msgs::action::GoToPose_Goal & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Goal_speed_scale planner_frame(::g_arm_msgs::action::GoToPose_Goal::_planner_frame_type arg)
  {
    msg_.planner_frame = std::move(arg);
    return Init_GoToPose_Goal_speed_scale(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Goal msg_;
};

class Init_GoToPose_Goal_allow_orientation
{
public:
  explicit Init_GoToPose_Goal_allow_orientation(::g_arm_msgs::action::GoToPose_Goal & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Goal_planner_frame allow_orientation(::g_arm_msgs::action::GoToPose_Goal::_allow_orientation_type arg)
  {
    msg_.allow_orientation = std::move(arg);
    return Init_GoToPose_Goal_planner_frame(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Goal msg_;
};

class Init_GoToPose_Goal_timeout_sec
{
public:
  explicit Init_GoToPose_Goal_timeout_sec(::g_arm_msgs::action::GoToPose_Goal & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Goal_allow_orientation timeout_sec(::g_arm_msgs::action::GoToPose_Goal::_timeout_sec_type arg)
  {
    msg_.timeout_sec = std::move(arg);
    return Init_GoToPose_Goal_allow_orientation(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Goal msg_;
};

class Init_GoToPose_Goal_ang_tolerance_rad
{
public:
  explicit Init_GoToPose_Goal_ang_tolerance_rad(::g_arm_msgs::action::GoToPose_Goal & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Goal_timeout_sec ang_tolerance_rad(::g_arm_msgs::action::GoToPose_Goal::_ang_tolerance_rad_type arg)
  {
    msg_.ang_tolerance_rad = std::move(arg);
    return Init_GoToPose_Goal_timeout_sec(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Goal msg_;
};

class Init_GoToPose_Goal_pos_tolerance_m
{
public:
  explicit Init_GoToPose_Goal_pos_tolerance_m(::g_arm_msgs::action::GoToPose_Goal & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Goal_ang_tolerance_rad pos_tolerance_m(::g_arm_msgs::action::GoToPose_Goal::_pos_tolerance_m_type arg)
  {
    msg_.pos_tolerance_m = std::move(arg);
    return Init_GoToPose_Goal_ang_tolerance_rad(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Goal msg_;
};

class Init_GoToPose_Goal_target
{
public:
  Init_GoToPose_Goal_target()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_Goal_pos_tolerance_m target(::g_arm_msgs::action::GoToPose_Goal::_target_type arg)
  {
    msg_.target = std::move(arg);
    return Init_GoToPose_Goal_pos_tolerance_m(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g_arm_msgs::action::GoToPose_Goal>()
{
  return g_arm_msgs::action::builder::Init_GoToPose_Goal_target();
}

}  // namespace g_arm_msgs


namespace g_arm_msgs
{

namespace action
{

namespace builder
{

class Init_GoToPose_Result_final_joint_positions
{
public:
  explicit Init_GoToPose_Result_final_joint_positions(::g_arm_msgs::action::GoToPose_Result & msg)
  : msg_(msg)
  {}
  ::g_arm_msgs::action::GoToPose_Result final_joint_positions(::g_arm_msgs::action::GoToPose_Result::_final_joint_positions_type arg)
  {
    msg_.final_joint_positions = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Result msg_;
};

class Init_GoToPose_Result_final_ang_error_rad
{
public:
  explicit Init_GoToPose_Result_final_ang_error_rad(::g_arm_msgs::action::GoToPose_Result & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Result_final_joint_positions final_ang_error_rad(::g_arm_msgs::action::GoToPose_Result::_final_ang_error_rad_type arg)
  {
    msg_.final_ang_error_rad = std::move(arg);
    return Init_GoToPose_Result_final_joint_positions(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Result msg_;
};

class Init_GoToPose_Result_final_pos_error_m
{
public:
  explicit Init_GoToPose_Result_final_pos_error_m(::g_arm_msgs::action::GoToPose_Result & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Result_final_ang_error_rad final_pos_error_m(::g_arm_msgs::action::GoToPose_Result::_final_pos_error_m_type arg)
  {
    msg_.final_pos_error_m = std::move(arg);
    return Init_GoToPose_Result_final_ang_error_rad(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Result msg_;
};

class Init_GoToPose_Result_message
{
public:
  explicit Init_GoToPose_Result_message(::g_arm_msgs::action::GoToPose_Result & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Result_final_pos_error_m message(::g_arm_msgs::action::GoToPose_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_GoToPose_Result_final_pos_error_m(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Result msg_;
};

class Init_GoToPose_Result_error_code
{
public:
  explicit Init_GoToPose_Result_error_code(::g_arm_msgs::action::GoToPose_Result & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Result_message error_code(::g_arm_msgs::action::GoToPose_Result::_error_code_type arg)
  {
    msg_.error_code = std::move(arg);
    return Init_GoToPose_Result_message(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Result msg_;
};

class Init_GoToPose_Result_success
{
public:
  Init_GoToPose_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_Result_error_code success(::g_arm_msgs::action::GoToPose_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GoToPose_Result_error_code(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g_arm_msgs::action::GoToPose_Result>()
{
  return g_arm_msgs::action::builder::Init_GoToPose_Result_success();
}

}  // namespace g_arm_msgs


namespace g_arm_msgs
{

namespace action
{

namespace builder
{

class Init_GoToPose_Feedback_detail
{
public:
  explicit Init_GoToPose_Feedback_detail(::g_arm_msgs::action::GoToPose_Feedback & msg)
  : msg_(msg)
  {}
  ::g_arm_msgs::action::GoToPose_Feedback detail(::g_arm_msgs::action::GoToPose_Feedback::_detail_type arg)
  {
    msg_.detail = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Feedback msg_;
};

class Init_GoToPose_Feedback_progress
{
public:
  explicit Init_GoToPose_Feedback_progress(::g_arm_msgs::action::GoToPose_Feedback & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Feedback_detail progress(::g_arm_msgs::action::GoToPose_Feedback::_progress_type arg)
  {
    msg_.progress = std::move(arg);
    return Init_GoToPose_Feedback_detail(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Feedback msg_;
};

class Init_GoToPose_Feedback_ang_error_rad
{
public:
  explicit Init_GoToPose_Feedback_ang_error_rad(::g_arm_msgs::action::GoToPose_Feedback & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Feedback_progress ang_error_rad(::g_arm_msgs::action::GoToPose_Feedback::_ang_error_rad_type arg)
  {
    msg_.ang_error_rad = std::move(arg);
    return Init_GoToPose_Feedback_progress(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Feedback msg_;
};

class Init_GoToPose_Feedback_pos_error_m
{
public:
  explicit Init_GoToPose_Feedback_pos_error_m(::g_arm_msgs::action::GoToPose_Feedback & msg)
  : msg_(msg)
  {}
  Init_GoToPose_Feedback_ang_error_rad pos_error_m(::g_arm_msgs::action::GoToPose_Feedback::_pos_error_m_type arg)
  {
    msg_.pos_error_m = std::move(arg);
    return Init_GoToPose_Feedback_ang_error_rad(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Feedback msg_;
};

class Init_GoToPose_Feedback_state
{
public:
  Init_GoToPose_Feedback_state()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_Feedback_pos_error_m state(::g_arm_msgs::action::GoToPose_Feedback::_state_type arg)
  {
    msg_.state = std::move(arg);
    return Init_GoToPose_Feedback_pos_error_m(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g_arm_msgs::action::GoToPose_Feedback>()
{
  return g_arm_msgs::action::builder::Init_GoToPose_Feedback_state();
}

}  // namespace g_arm_msgs


namespace g_arm_msgs
{

namespace action
{

namespace builder
{

class Init_GoToPose_SendGoal_Request_goal
{
public:
  explicit Init_GoToPose_SendGoal_Request_goal(::g_arm_msgs::action::GoToPose_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::g_arm_msgs::action::GoToPose_SendGoal_Request goal(::g_arm_msgs::action::GoToPose_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_SendGoal_Request msg_;
};

class Init_GoToPose_SendGoal_Request_goal_id
{
public:
  Init_GoToPose_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_SendGoal_Request_goal goal_id(::g_arm_msgs::action::GoToPose_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_GoToPose_SendGoal_Request_goal(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g_arm_msgs::action::GoToPose_SendGoal_Request>()
{
  return g_arm_msgs::action::builder::Init_GoToPose_SendGoal_Request_goal_id();
}

}  // namespace g_arm_msgs


namespace g_arm_msgs
{

namespace action
{

namespace builder
{

class Init_GoToPose_SendGoal_Response_stamp
{
public:
  explicit Init_GoToPose_SendGoal_Response_stamp(::g_arm_msgs::action::GoToPose_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::g_arm_msgs::action::GoToPose_SendGoal_Response stamp(::g_arm_msgs::action::GoToPose_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_SendGoal_Response msg_;
};

class Init_GoToPose_SendGoal_Response_accepted
{
public:
  Init_GoToPose_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_SendGoal_Response_stamp accepted(::g_arm_msgs::action::GoToPose_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_GoToPose_SendGoal_Response_stamp(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g_arm_msgs::action::GoToPose_SendGoal_Response>()
{
  return g_arm_msgs::action::builder::Init_GoToPose_SendGoal_Response_accepted();
}

}  // namespace g_arm_msgs


namespace g_arm_msgs
{

namespace action
{

namespace builder
{

class Init_GoToPose_SendGoal_Event_response
{
public:
  explicit Init_GoToPose_SendGoal_Event_response(::g_arm_msgs::action::GoToPose_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::g_arm_msgs::action::GoToPose_SendGoal_Event response(::g_arm_msgs::action::GoToPose_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_SendGoal_Event msg_;
};

class Init_GoToPose_SendGoal_Event_request
{
public:
  explicit Init_GoToPose_SendGoal_Event_request(::g_arm_msgs::action::GoToPose_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_GoToPose_SendGoal_Event_response request(::g_arm_msgs::action::GoToPose_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GoToPose_SendGoal_Event_response(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_SendGoal_Event msg_;
};

class Init_GoToPose_SendGoal_Event_info
{
public:
  Init_GoToPose_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_SendGoal_Event_request info(::g_arm_msgs::action::GoToPose_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GoToPose_SendGoal_Event_request(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g_arm_msgs::action::GoToPose_SendGoal_Event>()
{
  return g_arm_msgs::action::builder::Init_GoToPose_SendGoal_Event_info();
}

}  // namespace g_arm_msgs


namespace g_arm_msgs
{

namespace action
{

namespace builder
{

class Init_GoToPose_GetResult_Request_goal_id
{
public:
  Init_GoToPose_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::g_arm_msgs::action::GoToPose_GetResult_Request goal_id(::g_arm_msgs::action::GoToPose_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g_arm_msgs::action::GoToPose_GetResult_Request>()
{
  return g_arm_msgs::action::builder::Init_GoToPose_GetResult_Request_goal_id();
}

}  // namespace g_arm_msgs


namespace g_arm_msgs
{

namespace action
{

namespace builder
{

class Init_GoToPose_GetResult_Response_result
{
public:
  explicit Init_GoToPose_GetResult_Response_result(::g_arm_msgs::action::GoToPose_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::g_arm_msgs::action::GoToPose_GetResult_Response result(::g_arm_msgs::action::GoToPose_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_GetResult_Response msg_;
};

class Init_GoToPose_GetResult_Response_status
{
public:
  Init_GoToPose_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_GetResult_Response_result status(::g_arm_msgs::action::GoToPose_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_GoToPose_GetResult_Response_result(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g_arm_msgs::action::GoToPose_GetResult_Response>()
{
  return g_arm_msgs::action::builder::Init_GoToPose_GetResult_Response_status();
}

}  // namespace g_arm_msgs


namespace g_arm_msgs
{

namespace action
{

namespace builder
{

class Init_GoToPose_GetResult_Event_response
{
public:
  explicit Init_GoToPose_GetResult_Event_response(::g_arm_msgs::action::GoToPose_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::g_arm_msgs::action::GoToPose_GetResult_Event response(::g_arm_msgs::action::GoToPose_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_GetResult_Event msg_;
};

class Init_GoToPose_GetResult_Event_request
{
public:
  explicit Init_GoToPose_GetResult_Event_request(::g_arm_msgs::action::GoToPose_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_GoToPose_GetResult_Event_response request(::g_arm_msgs::action::GoToPose_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_GoToPose_GetResult_Event_response(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_GetResult_Event msg_;
};

class Init_GoToPose_GetResult_Event_info
{
public:
  Init_GoToPose_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_GetResult_Event_request info(::g_arm_msgs::action::GoToPose_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_GoToPose_GetResult_Event_request(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g_arm_msgs::action::GoToPose_GetResult_Event>()
{
  return g_arm_msgs::action::builder::Init_GoToPose_GetResult_Event_info();
}

}  // namespace g_arm_msgs


namespace g_arm_msgs
{

namespace action
{

namespace builder
{

class Init_GoToPose_FeedbackMessage_feedback
{
public:
  explicit Init_GoToPose_FeedbackMessage_feedback(::g_arm_msgs::action::GoToPose_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::g_arm_msgs::action::GoToPose_FeedbackMessage feedback(::g_arm_msgs::action::GoToPose_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_FeedbackMessage msg_;
};

class Init_GoToPose_FeedbackMessage_goal_id
{
public:
  Init_GoToPose_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GoToPose_FeedbackMessage_feedback goal_id(::g_arm_msgs::action::GoToPose_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_GoToPose_FeedbackMessage_feedback(msg_);
  }

private:
  ::g_arm_msgs::action::GoToPose_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::g_arm_msgs::action::GoToPose_FeedbackMessage>()
{
  return g_arm_msgs::action::builder::Init_GoToPose_FeedbackMessage_goal_id();
}

}  // namespace g_arm_msgs

#endif  // G_ARM_MSGS__ACTION__DETAIL__GO_TO_POSE__BUILDER_HPP_
