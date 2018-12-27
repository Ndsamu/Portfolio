/**
 * @file motion_handler_obstacle.cc
 *
 * @copyright 2018 Nate Samuelson, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/motion_handler_obstacle.h"
#include "src/motion_behavior_differential.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void MotionHandlerObstacle::UpdateVelocity() {
  if (entity_->get_touch_sensor()->get_output()) {
    entity_->RelativeChangeHeading(+180);
  }
}

NAMESPACE_END(csci3081);
