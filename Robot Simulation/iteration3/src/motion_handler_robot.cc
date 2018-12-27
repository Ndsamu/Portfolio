/**
 * @file motion_handler_robot.cc
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_robot.h"
#include "src/motion_behavior_differential.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void MotionHandlerRobot::UpdateVelocity(
  RobotType type_,
  double left_light_data_, double right_light_data_,
  bool hunger_, double hunger_level_,
  double left_food_data_, double right_food_data_) {
  /** The hunger ratio maintains a total potential velocity
   * based on the food and light sensor data. This ratio
   * ensures that initially food sensor data will be ignored
   * and eventually light sensor data will be ignored.
   **/
  double hunger_ratio_;
  if (hunger_) {
    hunger_ratio_ = hunger_level_/100;
  } else {
    hunger_ratio_ = 0.0;
  }

  double left_food_velocity_ = (hunger_ratio_ * left_food_data_)/100;
  double right_food_velocity_ = (hunger_ratio_ * right_food_data_)/100;
  double left_light_velocity_ = ((1 - hunger_ratio_) * left_light_data_)/100;
  double right_light_velocity_ = ((1 - hunger_ratio_) * right_light_data_)/100;

  switch (type_) {
  case (kCoward):  // Coward robot type
  set_velocity(ClampVelocity(left_light_velocity_ + right_food_velocity_),
   ClampVelocity(right_light_velocity_ + left_food_velocity_));
  break;
  case (kAggressive):  // Aggressive robot type
  set_velocity(ClampVelocity(right_light_velocity_ + right_food_velocity_),
   ClampVelocity(left_light_velocity_ + left_food_velocity_));
  break;
  case (kLove):  // Love robot type
  set_velocity(ClampVelocity(-left_light_velocity_ + right_food_velocity_),
   ClampVelocity(-right_light_velocity_ + left_food_velocity_));
  break;
  case (kExplore):  // Explore robot type
  set_velocity(ClampVelocity(-right_light_velocity_ + right_food_velocity_),
   ClampVelocity(-left_light_velocity_ + left_food_velocity_));
  break;
  default:
  {}
  }
} /* UpdateVelocity() */

double MotionHandlerRobot::ClampVelocity(double velocity) {
  if (velocity > MAX_VELOCITY) {
    return MAX_VELOCITY;
  }
  if (velocity < MIN_VELOCITY) {
    return MIN_VELOCITY;
  }
  return velocity;
} /* ClampVelocity() */

bool MotionHandlerRobot::UpdateState() {
  if (GetState() && avoid_time_ > 0) {
    set_velocity(AVOIDANCE_VELOCITY,
                                AVOIDANCE_VELOCITY);
    avoid_time_ -= 5;
    return true;
  }
  SetState(false);
  set_velocity(ACTIVE_VELOCITY, ACTIVE_VELOCITY);
  avoid_time_ = 50;
  return false;
} /* UpdateState() */

NAMESPACE_END(csci3081);
