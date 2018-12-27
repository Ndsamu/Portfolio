/**
 * @file motion_handler_obstacle.h
 *
 * @copyright 2018 Nate Samuelson, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_OBSTACLE_H_
#define SRC_MOTION_HANDLER_OBSTACLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cassert>
#include <iostream>

#include "src/common.h"
#include "src/motion_handler.h"
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
 * @brief Class managing a Obstacle's speed and heading angle based
 * on collisions and user inputs.
 *
 * Currently, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class MotionHandlerObstacle : public MotionHandler {
 public:
  explicit MotionHandlerObstacle(ArenaMobileEntity * ent)
      : MotionHandler(ent) {}

  MotionHandlerObstacle(const MotionHandlerObstacle& other) = default;
  MotionHandlerObstacle& operator=
    (const MotionHandlerObstacle& other) = default;

  /**
  * @brief Update the speed and the pose angle according to the sensor readings.
  *
  * Currently does not change speed.
  *
  * @param[in] pose The current pose.
  * @param[in] st A SensorTouch to be read.
  */
  void UpdateVelocity() override;
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_OBSTACLE_H_
