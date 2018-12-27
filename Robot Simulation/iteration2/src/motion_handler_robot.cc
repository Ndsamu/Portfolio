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
  RobotType type_, double hunger_,
  double left_light_data_, double right_light_data_,
  double left_food_data_, double right_food_data_) {
  /** The hunger ratio maintains a total potential velocity
  * based on the food and light sensor data. This ratio
  * ensures that initially food sensor data will be ignored
  * and eventually light sensor data will be ignored.
  **/
  double hunger_ratio = hunger_/100;
  double left_food_velocity_ = (hunger_ratio * left_food_data_)/100;
  double right_food_velocity_ = (hunger_ratio * right_food_data_)/100;
  double left_light_velocity_ = ((1 - hunger_ratio) * left_light_data_)/100;
  double right_light_velocity_ = ((1 - hunger_ratio) * right_light_data_)/100;


  switch (type_) {
  case (kCoward):  // Coward robot type
  set_velocity(left_light_velocity_ + right_food_velocity_,
   right_light_velocity_ + left_food_velocity_);
  break;
  case (kAggressive):  // Aggressive robot type
  set_velocity(right_light_velocity_ + right_food_velocity_,
   left_light_velocity_ + left_food_velocity_);
  break;
  case (kLove):  // Love robot type
  set_velocity(-left_light_velocity_ + right_food_velocity_,
   -right_light_velocity_ + left_food_velocity_);
  break;
  case (kExplore):  // Explore robot type
  set_velocity(-right_light_velocity_ + right_food_velocity_,
   -left_light_velocity_ + left_food_velocity_);
  break;
  default:
  {}
  }
} /* UpdateVelocity() */

double MotionHandlerRobot::clamp_vel(double vel) {
  double clamped = 0.0;
  if (vel > 0) {
    clamped = (vel > get_max_speed()) ?
              get_max_speed():
              vel;
  } else {
    clamped = (vel < get_min_speed()) ?
              get_min_speed():
              vel;
  }
  return clamped;
} /* clamp_vel() */

bool MotionHandlerRobot::UpdateState() {
  if (GetState() == 1 && avoid_time_ > 0) {
    set_velocity(AVOIDANCE_SPEED,
                                AVOIDANCE_SPEED);
    avoid_time_ -= 5;
    return true;
  } else {
    SetState(0);
    set_velocity(ACTIVE_SPEED, ACTIVE_SPEED);
    avoid_time_ = 50;
    return false;
  }
} /* UpdateState() */

NAMESPACE_END(csci3081);
