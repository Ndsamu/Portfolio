/**
 * @file motion_behavior.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>

#include "src/motion_behavior.h"
#include "src/arena_mobile_entity.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
MotionBehavior::MotionBehavior(ArenaMobileEntity * ent)
    : entity_(ent) {} /* MotionBehavior() */

void MotionBehavior::UpdatePose(double dt, WheelVelocity vel) {
  Pose pose = entity_->get_pose();

  // Movement is always along the heading_angle (i.e. the hypotenuse)
  double new_x =
    pose.x + std::cos(pose.theta * M_PI / 180.0)
      * std::abs(vel.left + vel.right)/2 * dt;
  double new_y =
    pose.y + std::sin(pose.theta * M_PI / 180.0)
      * std::abs(vel.left + vel.right)/2 * dt;

  /* Heading angle remaings the same */
  pose.x = new_x;
  pose.y = new_y;
  entity_->set_pose(pose);
} /* UpdatePose() */

NAMESPACE_END(csci3081);
