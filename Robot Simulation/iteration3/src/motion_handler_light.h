/**
 * @file motion_handler_light.h
 *
 * @copyright 2018 Nate Samuelson, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_LIGHT_H_
#define SRC_MOTION_HANDLER_LIGHT_H_

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
 * @brief Class managing a Light's speed and heading angle based
 * on collisions and user inputs.
 *
 * Currently, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class MotionHandlerLight : public MotionHandler {
 public:
  explicit MotionHandlerLight(ArenaMobileEntity * ent)
      : MotionHandler(ent) {}

  MotionHandlerLight(const MotionHandlerLight& other) = default;
  MotionHandlerLight& operator=
    (const MotionHandlerLight& other) = default;

  /**
  * @brief Update the speed and the pose angle according to the sensor readings.
  *
  * Simply travels in a straight line.
  */
  void UpdateVelocity() override;
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_LIGHT_H_
