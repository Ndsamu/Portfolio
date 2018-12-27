/**
 * @file motion_handler_robot.h
 *
 * @copyright 2018 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_ROBOT_H_
#define SRC_MOTION_HANDLER_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cassert>
#include <iostream>

#include "src/common.h"
#include "src/params.h"
#include "src/motion_handler.h"
#include "src/robot_type.h"
#include "src/sensor_touch.h"
#include "src/communication.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/

/**
 * @brief Class managing a Robot's speed and heading angle based
 * on collisions and user inputs.
 *
 * Currently, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class MotionHandlerRobot : public MotionHandler {
 public:
  using csci3081::MotionHandler::UpdateVelocity;
  explicit MotionHandlerRobot(ArenaMobileEntity * ent)
      : MotionHandler(ent), state_(0), avoid_time_(80) {}

  MotionHandlerRobot(const MotionHandlerRobot& other) = default;
  MotionHandlerRobot& operator=(const MotionHandlerRobot& other) = default;

  /**
   * @brief MotionHandlerRobot's destructor. `delete` all entities created.
   */
  virtual ~MotionHandlerRobot() {}

  /**
  * @brief Update the speed and the pose angle according to the sensor readings.
  *
  * Calculates velocity as a ratio between light sensor data and food sensor
  * data measured by the hunger_ratio calculated from hunger levels.
  *
  * @param[in] type_ The type of robot: determines how sensor data is used.
  * @param[in] hunger_ The hunger level of a robot used in hunger_ratio.
  * @param[in] left_light_data_ Last sensor reading from left light sensor.
  * @param[in] right_light_data_ Last sensor reading from right light sensor.
  * @param[in] left_food_data_ Last sensor reading from left food sensor.
  * @param[in] right_food_data_ Last sensor reading from right food sensor.
  */
  void UpdateVelocity(
    RobotType type_, double hunger_,
    double left_light_data_, double right_light_data_,
    double left_food_data_, double right_food_data_);

  int GetState() { return state_; }
  void SetState(int state) { state_ = state; }

  /**
  * @brief Updates robot state as either avoidance or active mode.
  *
  * @return A boolean which determines whether or not robot is in
  * avoidance mode where a robot will ignore sensor input.
  */
  bool UpdateState();

 private:
  // State is used to determine if a robot is an avoidance mode
  int state_;
  // Amount of time that a robot reverses in an arc.
  int avoid_time_;
  // Method used to limit velocity to a reasonable range.
  double clamp_vel(double vel);
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_ROBOT_H_
