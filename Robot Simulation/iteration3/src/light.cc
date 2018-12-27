/**
 * @file light.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/light.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Light::Light() :
    motion_handler_(this),
    motion_behavior_(this),
    state_(false),
    avoid_time_(80) {
  set_type(kLight);
  set_color(LIGHT_COLOR);
  set_pose(LIGHT_INIT_POS);
  set_radius(LIGHT_RADIUS);
  sensor_touch_->Reset();
} /* Light() */
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Light::Reset() {
  set_pose(set_pose_randomly());
  set_heading(LIGHT_HEADING);
} /* Reset() */

void Light::TimestepUpdate(unsigned int dt) {
  if (GetState() && avoid_time_ > 0) {
    motion_handler_.set_velocity(AVOIDANCE_VELOCITY,
                                AVOIDANCE_VELOCITY);
    set_heading(get_heading()-10);
    avoid_time_ -= 5;
  } else {
    SetState(false);
    motion_handler_.set_velocity(ACTIVE_VELOCITY, ACTIVE_VELOCITY);
    avoid_time_ = 50;
  }
  // Update heading as indicated by touch sensor
  motion_handler_.UpdateVelocity();

  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  sensor_touch_->Reset();
} /* TimestepUpdate() */

void Light::HandleCollision() {
  SetState(true);
} /* HandleCollision() */

NAMESPACE_END(csci3081);
