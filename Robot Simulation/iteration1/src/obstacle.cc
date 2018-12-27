/**
 * @file obstacle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/obstacle.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Obstacle::Obstacle() :
    motion_handler_(this),
    motion_behavior_(this),
    state_(0),
    avoid_time_(80) {
  set_type(kObstacle);
  set_color(OBSTACLE_COLOR);
  set_pose(OBSTACLE_INIT_POS);
  set_radius(OBSTACLE_RADIUS);
  sensor_touch_->Reset();
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Obstacle::Reset() {
  set_pose(set_pose_randomly());
  set_heading(OBSTACLE_HEADING);
} /* Reset */

void Obstacle::TimestepUpdate(unsigned int dt) {
  if (get_state() == 1 && avoid_time_ > 0) {
    motion_handler_.set_velocity(OBSTACLE_AVOIDANCE_SPEED,
                                OBSTACLE_AVOIDANCE_SPEED);
    set_heading(get_heading()-10);
    avoid_time_ -= 5;
  } else {
    set_state(0);
    motion_handler_.set_velocity(OBSTACLE_ACTIVE_SPEED, OBSTACLE_ACTIVE_SPEED);
    avoid_time_ = 50;
  }
  // Update heading as indicated by touch sensor
  motion_handler_.UpdateVelocity();

  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  sensor_touch_->Reset();
} /* TimestepUpdate() */

void Obstacle::HandleCollision() {
  set_state(1);
}

NAMESPACE_END(csci3081);
