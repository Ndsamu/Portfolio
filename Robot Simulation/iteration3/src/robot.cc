/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <tuple>
#include <cmath>
#include <iostream>
#include <string>
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
    type_(),
    motion_handler_(this),
    motion_behavior_(this),
    light_sensitivity_(1.0),
    left_light_sensor_(LightSensor()),
    right_light_sensor_(LightSensor()),
    left_food_sensor_(FoodSensor()),
    right_food_sensor_(FoodSensor()),
    hunger_(true),
    hunger_time_(100),
    hunger_level_(0),
    starvation_time_(100) {
  set_type(kRobot);
  set_color(ROBOT_COLOR);
  set_pose(ROBOT_INIT_POS);
  set_radius(ROBOT_RADIUS);
  left_light_sensor_.set_pose(SensorLocation(-40*M_PI/180));
  right_light_sensor_.set_pose(SensorLocation(40*M_PI/180));
  left_food_sensor_.set_pose(SensorLocation(-40*M_PI/180));
  right_food_sensor_.set_pose(SensorLocation(40*M_PI/180));
} /* Robot() */
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(unsigned int dt) {
  // Checks whether hunger is activated
  if (hunger_) {
    // Increments hunger of the robot after initial timer expires
    if (hunger_time_ > 0) {
      hunger_time_ -= 0.25;
    } else {
      if (hunger_level_ < 100) {
        hunger_level_ += 0.07;
      } else if (starvation_time_ > 0) {
        starvation_time_ -= 0.25;
      }
    }
    // Clamps hunger limit
    if (hunger_level_ > 100) { hunger_level_ = 100; }
  }

  // Updates the position of the sensors
  left_light_sensor_.set_pose(SensorLocation(-40*M_PI/180));
  right_light_sensor_.set_pose(SensorLocation(40*M_PI/180));
  left_food_sensor_.set_pose(SensorLocation(-40*M_PI/180));
  right_food_sensor_.set_pose(SensorLocation(40*M_PI/180));

  // If statement allows robot to ignore sensor data while in avoidance mode
  if (motion_handler_.UpdateState()) {
    // Updates active/avoidance mode and adjusts heading accordingly
    set_heading(get_heading()-10);
  } else {
  // Update heading as indicated by touch sensor
  motion_handler_.UpdateVelocity(type_,
    left_light_sensor_.GetReading(), right_light_sensor_.GetReading(),
    hunger_, hunger_level_,
    left_food_sensor_.GetReading(), right_food_sensor_.GetReading());

    // Use velocity and position to update position
    motion_behavior_.UpdatePose(dt, motion_handler_.get_velocity());

    // Reset Sensor for next cycle
    sensor_touch_->Reset();

    // Zero Sensors after utilizing data
    ZeroSensors();
  }
} /* TimestepUpdate() */

Pose Robot::SensorLocation(double angle_) {
  double theta = (M_PI*get_pose().theta/180) + angle_;
  double x = get_radius() * cos(theta) + get_pose().x;
  double y = get_radius() * sin(theta) + get_pose().y;
  Pose pose = Pose(x, y);
  return pose;
} /* SensorLocation() */

void Robot::NotifyLights(Pose pose) {
  left_light_sensor_.CalculateReading(pose);
  right_light_sensor_.CalculateReading(pose);
} /* NotifyLights() */

void Robot::NotifyFood(Pose pose) {
  left_food_sensor_.CalculateReading(pose);
  right_food_sensor_.CalculateReading(pose);
} /* NotifyFood() */

void Robot::ZeroSensors() {
  left_light_sensor_.ZeroReading();
  right_light_sensor_.ZeroReading();
  left_food_sensor_.ZeroReading();
  right_food_sensor_.ZeroReading();
} /* ZeroSensors() */

bool Robot::CheckStarvation() {
  return (starvation_time_ < 0.01);
} /* CheckStarvation() */

void Robot::Reset() {
  set_pose(set_pose_randomly());
  set_color(ROBOT_COLOR);
  hunger_level_ = 0;
  starvation_time_ = 100;
  motion_handler_.set_velocity(0.0, 0.0);
  motion_handler_.set_max_angle(ROBOT_MAX_ANGLE);
  sensor_touch_->Reset();
} /* Reset() */

void Robot::HandleCollision() {
  motion_handler_.SetState(true);
} /* HandleCollision() */


NAMESPACE_END(csci3081);
