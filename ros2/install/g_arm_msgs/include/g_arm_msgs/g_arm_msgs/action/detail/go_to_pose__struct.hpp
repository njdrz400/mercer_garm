// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from g_arm_msgs:action/GoToPose.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "g_arm_msgs/action/go_to_pose.hpp"


#ifndef G_ARM_MSGS__ACTION__DETAIL__GO_TO_POSE__STRUCT_HPP_
#define G_ARM_MSGS__ACTION__DETAIL__GO_TO_POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'target'
#include "geometry_msgs/msg/detail/pose_stamped__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__g_arm_msgs__action__GoToPose_Goal __attribute__((deprecated))
#else
# define DEPRECATED__g_arm_msgs__action__GoToPose_Goal __declspec(deprecated)
#endif

namespace g_arm_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct GoToPose_Goal_
{
  using Type = GoToPose_Goal_<ContainerAllocator>;

  explicit GoToPose_Goal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pos_tolerance_m = 0.0;
      this->ang_tolerance_rad = 0.0;
      this->timeout_sec = 0.0;
      this->allow_orientation = false;
      this->planner_frame = "";
      this->speed_scale = 0.0;
      this->max_joint_vel = 0.0;
      this->max_joint_acc = 0.0;
      this->electromagnet_on = false;
    }
  }

  explicit GoToPose_Goal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : target(_alloc, _init),
    planner_frame(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->pos_tolerance_m = 0.0;
      this->ang_tolerance_rad = 0.0;
      this->timeout_sec = 0.0;
      this->allow_orientation = false;
      this->planner_frame = "";
      this->speed_scale = 0.0;
      this->max_joint_vel = 0.0;
      this->max_joint_acc = 0.0;
      this->electromagnet_on = false;
    }
  }

  // field types and members
  using _target_type =
    geometry_msgs::msg::PoseStamped_<ContainerAllocator>;
  _target_type target;
  using _pos_tolerance_m_type =
    double;
  _pos_tolerance_m_type pos_tolerance_m;
  using _ang_tolerance_rad_type =
    double;
  _ang_tolerance_rad_type ang_tolerance_rad;
  using _timeout_sec_type =
    double;
  _timeout_sec_type timeout_sec;
  using _allow_orientation_type =
    bool;
  _allow_orientation_type allow_orientation;
  using _planner_frame_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _planner_frame_type planner_frame;
  using _speed_scale_type =
    double;
  _speed_scale_type speed_scale;
  using _max_joint_vel_type =
    double;
  _max_joint_vel_type max_joint_vel;
  using _max_joint_acc_type =
    double;
  _max_joint_acc_type max_joint_acc;
  using _electromagnet_on_type =
    bool;
  _electromagnet_on_type electromagnet_on;

  // setters for named parameter idiom
  Type & set__target(
    const geometry_msgs::msg::PoseStamped_<ContainerAllocator> & _arg)
  {
    this->target = _arg;
    return *this;
  }
  Type & set__pos_tolerance_m(
    const double & _arg)
  {
    this->pos_tolerance_m = _arg;
    return *this;
  }
  Type & set__ang_tolerance_rad(
    const double & _arg)
  {
    this->ang_tolerance_rad = _arg;
    return *this;
  }
  Type & set__timeout_sec(
    const double & _arg)
  {
    this->timeout_sec = _arg;
    return *this;
  }
  Type & set__allow_orientation(
    const bool & _arg)
  {
    this->allow_orientation = _arg;
    return *this;
  }
  Type & set__planner_frame(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->planner_frame = _arg;
    return *this;
  }
  Type & set__speed_scale(
    const double & _arg)
  {
    this->speed_scale = _arg;
    return *this;
  }
  Type & set__max_joint_vel(
    const double & _arg)
  {
    this->max_joint_vel = _arg;
    return *this;
  }
  Type & set__max_joint_acc(
    const double & _arg)
  {
    this->max_joint_acc = _arg;
    return *this;
  }
  Type & set__electromagnet_on(
    const bool & _arg)
  {
    this->electromagnet_on = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator> *;
  using ConstRawPtr =
    const g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_Goal
    std::shared_ptr<g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_Goal
    std::shared_ptr<g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoToPose_Goal_ & other) const
  {
    if (this->target != other.target) {
      return false;
    }
    if (this->pos_tolerance_m != other.pos_tolerance_m) {
      return false;
    }
    if (this->ang_tolerance_rad != other.ang_tolerance_rad) {
      return false;
    }
    if (this->timeout_sec != other.timeout_sec) {
      return false;
    }
    if (this->allow_orientation != other.allow_orientation) {
      return false;
    }
    if (this->planner_frame != other.planner_frame) {
      return false;
    }
    if (this->speed_scale != other.speed_scale) {
      return false;
    }
    if (this->max_joint_vel != other.max_joint_vel) {
      return false;
    }
    if (this->max_joint_acc != other.max_joint_acc) {
      return false;
    }
    if (this->electromagnet_on != other.electromagnet_on) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoToPose_Goal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoToPose_Goal_

// alias to use template instance with default allocator
using GoToPose_Goal =
  g_arm_msgs::action::GoToPose_Goal_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace g_arm_msgs


#ifndef _WIN32
# define DEPRECATED__g_arm_msgs__action__GoToPose_Result __attribute__((deprecated))
#else
# define DEPRECATED__g_arm_msgs__action__GoToPose_Result __declspec(deprecated)
#endif

namespace g_arm_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct GoToPose_Result_
{
  using Type = GoToPose_Result_<ContainerAllocator>;

  explicit GoToPose_Result_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0l;
      this->message = "";
      this->final_pos_error_m = 0.0;
      this->final_ang_error_rad = 0.0;
    }
  }

  explicit GoToPose_Result_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->error_code = 0l;
      this->message = "";
      this->final_pos_error_m = 0.0;
      this->final_ang_error_rad = 0.0;
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _error_code_type =
    int32_t;
  _error_code_type error_code;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;
  using _final_pos_error_m_type =
    double;
  _final_pos_error_m_type final_pos_error_m;
  using _final_ang_error_rad_type =
    double;
  _final_ang_error_rad_type final_ang_error_rad;
  using _final_joint_positions_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _final_joint_positions_type final_joint_positions;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__error_code(
    const int32_t & _arg)
  {
    this->error_code = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }
  Type & set__final_pos_error_m(
    const double & _arg)
  {
    this->final_pos_error_m = _arg;
    return *this;
  }
  Type & set__final_ang_error_rad(
    const double & _arg)
  {
    this->final_ang_error_rad = _arg;
    return *this;
  }
  Type & set__final_joint_positions(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->final_joint_positions = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    g_arm_msgs::action::GoToPose_Result_<ContainerAllocator> *;
  using ConstRawPtr =
    const g_arm_msgs::action::GoToPose_Result_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_Result_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_Result_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_Result_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_Result_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_Result_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_Result_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_Result_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_Result_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_Result
    std::shared_ptr<g_arm_msgs::action::GoToPose_Result_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_Result
    std::shared_ptr<g_arm_msgs::action::GoToPose_Result_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoToPose_Result_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->error_code != other.error_code) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    if (this->final_pos_error_m != other.final_pos_error_m) {
      return false;
    }
    if (this->final_ang_error_rad != other.final_ang_error_rad) {
      return false;
    }
    if (this->final_joint_positions != other.final_joint_positions) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoToPose_Result_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoToPose_Result_

// alias to use template instance with default allocator
using GoToPose_Result =
  g_arm_msgs::action::GoToPose_Result_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace g_arm_msgs


#ifndef _WIN32
# define DEPRECATED__g_arm_msgs__action__GoToPose_Feedback __attribute__((deprecated))
#else
# define DEPRECATED__g_arm_msgs__action__GoToPose_Feedback __declspec(deprecated)
#endif

namespace g_arm_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct GoToPose_Feedback_
{
  using Type = GoToPose_Feedback_<ContainerAllocator>;

  explicit GoToPose_Feedback_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = "";
      this->pos_error_m = 0.0;
      this->ang_error_rad = 0.0;
      this->progress = 0.0;
      this->detail = "";
    }
  }

  explicit GoToPose_Feedback_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : state(_alloc),
    detail(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->state = "";
      this->pos_error_m = 0.0;
      this->ang_error_rad = 0.0;
      this->progress = 0.0;
      this->detail = "";
    }
  }

  // field types and members
  using _state_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _state_type state;
  using _pos_error_m_type =
    double;
  _pos_error_m_type pos_error_m;
  using _ang_error_rad_type =
    double;
  _ang_error_rad_type ang_error_rad;
  using _progress_type =
    double;
  _progress_type progress;
  using _detail_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _detail_type detail;

  // setters for named parameter idiom
  Type & set__state(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->state = _arg;
    return *this;
  }
  Type & set__pos_error_m(
    const double & _arg)
  {
    this->pos_error_m = _arg;
    return *this;
  }
  Type & set__ang_error_rad(
    const double & _arg)
  {
    this->ang_error_rad = _arg;
    return *this;
  }
  Type & set__progress(
    const double & _arg)
  {
    this->progress = _arg;
    return *this;
  }
  Type & set__detail(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->detail = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator> *;
  using ConstRawPtr =
    const g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_Feedback
    std::shared_ptr<g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_Feedback
    std::shared_ptr<g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoToPose_Feedback_ & other) const
  {
    if (this->state != other.state) {
      return false;
    }
    if (this->pos_error_m != other.pos_error_m) {
      return false;
    }
    if (this->ang_error_rad != other.ang_error_rad) {
      return false;
    }
    if (this->progress != other.progress) {
      return false;
    }
    if (this->detail != other.detail) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoToPose_Feedback_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoToPose_Feedback_

// alias to use template instance with default allocator
using GoToPose_Feedback =
  g_arm_msgs::action::GoToPose_Feedback_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace g_arm_msgs


// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'goal'
#include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__g_arm_msgs__action__GoToPose_SendGoal_Request __attribute__((deprecated))
#else
# define DEPRECATED__g_arm_msgs__action__GoToPose_SendGoal_Request __declspec(deprecated)
#endif

namespace g_arm_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct GoToPose_SendGoal_Request_
{
  using Type = GoToPose_SendGoal_Request_<ContainerAllocator>;

  explicit GoToPose_SendGoal_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    goal(_init)
  {
    (void)_init;
  }

  explicit GoToPose_SendGoal_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    goal(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _goal_type =
    g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator>;
  _goal_type goal;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__goal(
    const g_arm_msgs::action::GoToPose_Goal_<ContainerAllocator> & _arg)
  {
    this->goal = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_SendGoal_Request
    std::shared_ptr<g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_SendGoal_Request
    std::shared_ptr<g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoToPose_SendGoal_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->goal != other.goal) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoToPose_SendGoal_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoToPose_SendGoal_Request_

// alias to use template instance with default allocator
using GoToPose_SendGoal_Request =
  g_arm_msgs::action::GoToPose_SendGoal_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace g_arm_msgs


// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__g_arm_msgs__action__GoToPose_SendGoal_Response __attribute__((deprecated))
#else
# define DEPRECATED__g_arm_msgs__action__GoToPose_SendGoal_Response __declspec(deprecated)
#endif

namespace g_arm_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct GoToPose_SendGoal_Response_
{
  using Type = GoToPose_SendGoal_Response_<ContainerAllocator>;

  explicit GoToPose_SendGoal_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  explicit GoToPose_SendGoal_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : stamp(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->accepted = false;
    }
  }

  // field types and members
  using _accepted_type =
    bool;
  _accepted_type accepted;
  using _stamp_type =
    builtin_interfaces::msg::Time_<ContainerAllocator>;
  _stamp_type stamp;

  // setters for named parameter idiom
  Type & set__accepted(
    const bool & _arg)
  {
    this->accepted = _arg;
    return *this;
  }
  Type & set__stamp(
    const builtin_interfaces::msg::Time_<ContainerAllocator> & _arg)
  {
    this->stamp = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_SendGoal_Response
    std::shared_ptr<g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_SendGoal_Response
    std::shared_ptr<g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoToPose_SendGoal_Response_ & other) const
  {
    if (this->accepted != other.accepted) {
      return false;
    }
    if (this->stamp != other.stamp) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoToPose_SendGoal_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoToPose_SendGoal_Response_

// alias to use template instance with default allocator
using GoToPose_SendGoal_Response =
  g_arm_msgs::action::GoToPose_SendGoal_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace g_arm_msgs


// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__g_arm_msgs__action__GoToPose_SendGoal_Event __attribute__((deprecated))
#else
# define DEPRECATED__g_arm_msgs__action__GoToPose_SendGoal_Event __declspec(deprecated)
#endif

namespace g_arm_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct GoToPose_SendGoal_Event_
{
  using Type = GoToPose_SendGoal_Event_<ContainerAllocator>;

  explicit GoToPose_SendGoal_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit GoToPose_SendGoal_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<g_arm_msgs::action::GoToPose_SendGoal_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<g_arm_msgs::action::GoToPose_SendGoal_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    g_arm_msgs::action::GoToPose_SendGoal_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const g_arm_msgs::action::GoToPose_SendGoal_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_SendGoal_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_SendGoal_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_SendGoal_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_SendGoal_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_SendGoal_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_SendGoal_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_SendGoal_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_SendGoal_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_SendGoal_Event
    std::shared_ptr<g_arm_msgs::action::GoToPose_SendGoal_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_SendGoal_Event
    std::shared_ptr<g_arm_msgs::action::GoToPose_SendGoal_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoToPose_SendGoal_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoToPose_SendGoal_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoToPose_SendGoal_Event_

// alias to use template instance with default allocator
using GoToPose_SendGoal_Event =
  g_arm_msgs::action::GoToPose_SendGoal_Event_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace g_arm_msgs

namespace g_arm_msgs
{

namespace action
{

struct GoToPose_SendGoal
{
  using Request = g_arm_msgs::action::GoToPose_SendGoal_Request;
  using Response = g_arm_msgs::action::GoToPose_SendGoal_Response;
  using Event = g_arm_msgs::action::GoToPose_SendGoal_Event;
};

}  // namespace action

}  // namespace g_arm_msgs


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__g_arm_msgs__action__GoToPose_GetResult_Request __attribute__((deprecated))
#else
# define DEPRECATED__g_arm_msgs__action__GoToPose_GetResult_Request __declspec(deprecated)
#endif

namespace g_arm_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct GoToPose_GetResult_Request_
{
  using Type = GoToPose_GetResult_Request_<ContainerAllocator>;

  explicit GoToPose_GetResult_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init)
  {
    (void)_init;
  }

  explicit GoToPose_GetResult_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_GetResult_Request
    std::shared_ptr<g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_GetResult_Request
    std::shared_ptr<g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoToPose_GetResult_Request_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoToPose_GetResult_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoToPose_GetResult_Request_

// alias to use template instance with default allocator
using GoToPose_GetResult_Request =
  g_arm_msgs::action::GoToPose_GetResult_Request_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace g_arm_msgs


// Include directives for member types
// Member 'result'
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__g_arm_msgs__action__GoToPose_GetResult_Response __attribute__((deprecated))
#else
# define DEPRECATED__g_arm_msgs__action__GoToPose_GetResult_Response __declspec(deprecated)
#endif

namespace g_arm_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct GoToPose_GetResult_Response_
{
  using Type = GoToPose_GetResult_Response_<ContainerAllocator>;

  explicit GoToPose_GetResult_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  explicit GoToPose_GetResult_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : result(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->status = 0;
    }
  }

  // field types and members
  using _status_type =
    int8_t;
  _status_type status;
  using _result_type =
    g_arm_msgs::action::GoToPose_Result_<ContainerAllocator>;
  _result_type result;

  // setters for named parameter idiom
  Type & set__status(
    const int8_t & _arg)
  {
    this->status = _arg;
    return *this;
  }
  Type & set__result(
    const g_arm_msgs::action::GoToPose_Result_<ContainerAllocator> & _arg)
  {
    this->result = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_GetResult_Response
    std::shared_ptr<g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_GetResult_Response
    std::shared_ptr<g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoToPose_GetResult_Response_ & other) const
  {
    if (this->status != other.status) {
      return false;
    }
    if (this->result != other.result) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoToPose_GetResult_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoToPose_GetResult_Response_

// alias to use template instance with default allocator
using GoToPose_GetResult_Response =
  g_arm_msgs::action::GoToPose_GetResult_Response_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace g_arm_msgs


// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__g_arm_msgs__action__GoToPose_GetResult_Event __attribute__((deprecated))
#else
# define DEPRECATED__g_arm_msgs__action__GoToPose_GetResult_Event __declspec(deprecated)
#endif

namespace g_arm_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct GoToPose_GetResult_Event_
{
  using Type = GoToPose_GetResult_Event_<ContainerAllocator>;

  explicit GoToPose_GetResult_Event_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_init)
  {
    (void)_init;
  }

  explicit GoToPose_GetResult_Event_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : info(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _info_type =
    service_msgs::msg::ServiceEventInfo_<ContainerAllocator>;
  _info_type info;
  using _request_type =
    rosidl_runtime_cpp::BoundedVector<g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator>>>;
  _request_type request;
  using _response_type =
    rosidl_runtime_cpp::BoundedVector<g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator>>>;
  _response_type response;

  // setters for named parameter idiom
  Type & set__info(
    const service_msgs::msg::ServiceEventInfo_<ContainerAllocator> & _arg)
  {
    this->info = _arg;
    return *this;
  }
  Type & set__request(
    const rosidl_runtime_cpp::BoundedVector<g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<g_arm_msgs::action::GoToPose_GetResult_Request_<ContainerAllocator>>> & _arg)
  {
    this->request = _arg;
    return *this;
  }
  Type & set__response(
    const rosidl_runtime_cpp::BoundedVector<g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator>, 1, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<g_arm_msgs::action::GoToPose_GetResult_Response_<ContainerAllocator>>> & _arg)
  {
    this->response = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    g_arm_msgs::action::GoToPose_GetResult_Event_<ContainerAllocator> *;
  using ConstRawPtr =
    const g_arm_msgs::action::GoToPose_GetResult_Event_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_GetResult_Event_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_GetResult_Event_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_GetResult_Event_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_GetResult_Event_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_GetResult_Event_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_GetResult_Event_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_GetResult_Event_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_GetResult_Event_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_GetResult_Event
    std::shared_ptr<g_arm_msgs::action::GoToPose_GetResult_Event_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_GetResult_Event
    std::shared_ptr<g_arm_msgs::action::GoToPose_GetResult_Event_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoToPose_GetResult_Event_ & other) const
  {
    if (this->info != other.info) {
      return false;
    }
    if (this->request != other.request) {
      return false;
    }
    if (this->response != other.response) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoToPose_GetResult_Event_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoToPose_GetResult_Event_

// alias to use template instance with default allocator
using GoToPose_GetResult_Event =
  g_arm_msgs::action::GoToPose_GetResult_Event_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace g_arm_msgs

namespace g_arm_msgs
{

namespace action
{

struct GoToPose_GetResult
{
  using Request = g_arm_msgs::action::GoToPose_GetResult_Request;
  using Response = g_arm_msgs::action::GoToPose_GetResult_Response;
  using Event = g_arm_msgs::action::GoToPose_GetResult_Event;
};

}  // namespace action

}  // namespace g_arm_msgs


// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.hpp"
// Member 'feedback'
// already included above
// #include "g_arm_msgs/action/detail/go_to_pose__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__g_arm_msgs__action__GoToPose_FeedbackMessage __attribute__((deprecated))
#else
# define DEPRECATED__g_arm_msgs__action__GoToPose_FeedbackMessage __declspec(deprecated)
#endif

namespace g_arm_msgs
{

namespace action
{

// message struct
template<class ContainerAllocator>
struct GoToPose_FeedbackMessage_
{
  using Type = GoToPose_FeedbackMessage_<ContainerAllocator>;

  explicit GoToPose_FeedbackMessage_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_init),
    feedback(_init)
  {
    (void)_init;
  }

  explicit GoToPose_FeedbackMessage_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : goal_id(_alloc, _init),
    feedback(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _goal_id_type =
    unique_identifier_msgs::msg::UUID_<ContainerAllocator>;
  _goal_id_type goal_id;
  using _feedback_type =
    g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator>;
  _feedback_type feedback;

  // setters for named parameter idiom
  Type & set__goal_id(
    const unique_identifier_msgs::msg::UUID_<ContainerAllocator> & _arg)
  {
    this->goal_id = _arg;
    return *this;
  }
  Type & set__feedback(
    const g_arm_msgs::action::GoToPose_Feedback_<ContainerAllocator> & _arg)
  {
    this->feedback = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    g_arm_msgs::action::GoToPose_FeedbackMessage_<ContainerAllocator> *;
  using ConstRawPtr =
    const g_arm_msgs::action::GoToPose_FeedbackMessage_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_FeedbackMessage_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<g_arm_msgs::action::GoToPose_FeedbackMessage_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_FeedbackMessage_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_FeedbackMessage_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      g_arm_msgs::action::GoToPose_FeedbackMessage_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<g_arm_msgs::action::GoToPose_FeedbackMessage_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_FeedbackMessage_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<g_arm_msgs::action::GoToPose_FeedbackMessage_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_FeedbackMessage
    std::shared_ptr<g_arm_msgs::action::GoToPose_FeedbackMessage_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__g_arm_msgs__action__GoToPose_FeedbackMessage
    std::shared_ptr<g_arm_msgs::action::GoToPose_FeedbackMessage_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const GoToPose_FeedbackMessage_ & other) const
  {
    if (this->goal_id != other.goal_id) {
      return false;
    }
    if (this->feedback != other.feedback) {
      return false;
    }
    return true;
  }
  bool operator!=(const GoToPose_FeedbackMessage_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct GoToPose_FeedbackMessage_

// alias to use template instance with default allocator
using GoToPose_FeedbackMessage =
  g_arm_msgs::action::GoToPose_FeedbackMessage_<std::allocator<void>>;

// constant definitions

}  // namespace action

}  // namespace g_arm_msgs

#include "action_msgs/srv/cancel_goal.hpp"
#include "action_msgs/msg/goal_info.hpp"
#include "action_msgs/msg/goal_status_array.hpp"

namespace g_arm_msgs
{

namespace action
{

struct GoToPose
{
  /// The goal message defined in the action definition.
  using Goal = g_arm_msgs::action::GoToPose_Goal;
  /// The result message defined in the action definition.
  using Result = g_arm_msgs::action::GoToPose_Result;
  /// The feedback message defined in the action definition.
  using Feedback = g_arm_msgs::action::GoToPose_Feedback;

  struct Impl
  {
    /// The send_goal service using a wrapped version of the goal message as a request.
    using SendGoalService = g_arm_msgs::action::GoToPose_SendGoal;
    /// The get_result service using a wrapped version of the result message as a response.
    using GetResultService = g_arm_msgs::action::GoToPose_GetResult;
    /// The feedback message with generic fields which wraps the feedback message.
    using FeedbackMessage = g_arm_msgs::action::GoToPose_FeedbackMessage;

    /// The generic service to cancel a goal.
    using CancelGoalService = action_msgs::srv::CancelGoal;
    /// The generic message for the status of a goal.
    using GoalStatusMessage = action_msgs::msg::GoalStatusArray;
  };
};

typedef struct GoToPose GoToPose;

}  // namespace action

}  // namespace g_arm_msgs

#endif  // G_ARM_MSGS__ACTION__DETAIL__GO_TO_POSE__STRUCT_HPP_
