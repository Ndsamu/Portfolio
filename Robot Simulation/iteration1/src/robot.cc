/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot() :
    motion_handler_(this),
    motion_behavior_(this),
    lives_(9),
    captured_(0),
    mercy_switch_(false),
    mercy_timer_(40),
    mercy_flash_(false) {
  set_type(kRobot);
  set_color(ROBOT_COLOR);
  set_pose(ROBOT_INIT_POS);
  set_radius(ROBOT_RADIUS);
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(unsigned int dt) {
  if (mercy_switch_ && mercy_timer_ > 0) {
    if (mercy_flash_) {
      mercy_flash_ = false;
      set_color({ 0, 0, 150 });
    } else {
      mercy_flash_ = true;
      set_color(ROBOT_COLOR);
    }
    mercy_timer_ -= dt;
  } else {
    set_color(ROBOT_COLOR);
    mercy_switch_ = false;
    mercy_timer_ = 40;
  }

  // Update heading as indicated by touch sensor
  motion_handler_.UpdateVelocity();

  // Use velocity and position to update position
  motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

  // Reset Sensor for next cycle
  sensor_touch_->Reset();
} /* TimestepUpdate() */

void Robot::Reset() {
  set_pose(ROBOT_INIT_POS);
  set_color(ROBOT_COLOR);
  set_lives(ROBOT_LIVES);
  motion_handler_.set_velocity(0.0, 0.0);
  set_captured_bases(0);
  motion_handler_.set_max_speed(ROBOT_MAX_SPEED);
//  motion_handler_.set_min_speed(ROBOT_MIN_SPEED);
  motion_handler_.set_max_angle(ROBOT_MAX_ANGLE);
  sensor_touch_->Reset();
} /* Reset() */

int Robot::get_lives() const {
  return lives_;
}
void Robot::set_lives(int l) {
  lives_ = l;
}
int Robot::get_captured_bases() {
  return captured_;
}
void Robot::set_captured_bases(int c) {
  captured_ = c;
}

void Robot::HandleCollision(EntityType object_type, ArenaEntity * object) {
  sensor_touch_->HandleCollision(object_type, object);
  motion_handler_.set_velocity(0.0, 0.0);
  switch (object_type) {
    case(kRobot):
      break;
    case(kObstacle):
      if (!mercy_switch_) {
        if (get_lives() > 0) {
          set_lives(get_lives()-1);
          mercy_switch_ = true;
        }
      }
      break;
    case(kBase):
      set_captured_bases(get_captured_bases() + 1);
      break;
    case(kEntity):
      break;
    case(kRightWall):
      if (!mercy_switch_) {
        if (get_lives() > 0) {
          set_lives(get_lives()-1);
          mercy_switch_ = true;
        }
      }
      break;
    case(kLeftWall):
      if (!mercy_switch_) {
        if (get_lives() > 0) {
          set_lives(get_lives()-1);
          mercy_switch_ = true;
        }
      }
      break;
    case(kTopWall):
      if (!mercy_switch_) {
        if (get_lives() > 0) {
          set_lives(get_lives()-1);
          mercy_switch_ = true;
        }
      }
      break;
    case(kBottomWall):
      if (!mercy_switch_) {
        if (get_lives() > 0) {
          set_lives(get_lives()-1);
          mercy_switch_ = true;
        }
      }
      break;
    case(kUndefined):
    default: break;
  }
}

void Robot::IncreaseSpeed() {
  motion_handler_.IncreaseSpeed();
}
void Robot::DecreaseSpeed() {
  motion_handler_.DecreaseSpeed();
}
void Robot::TurnRight() {
  motion_handler_.TurnRight();
}
void Robot::TurnLeft() {
  motion_handler_.TurnLeft();
}


NAMESPACE_END(csci3081);
