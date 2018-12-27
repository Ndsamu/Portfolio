/**
 * @file robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <iostream>
#include "src/light_sensor.h"
#include "src/food_sensor.h"
#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/motion_handler_robot.h"
#include "src/motion_behavior_differential.h"
#include "src/entity_type.h"
#include "src/robot_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class MotionBehaviorDifferential;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a robot within the arena.
 *
 * Robots are composed of a motion handler, motion behavior, and touch sensor.
 * These classes interact to maintain the pose (position and heading) of the
 * robot. At each time step, the wheel velocities are used to calculate the
 * next pose of the robot. The handler manages the pose and sensor data. The
 * behavior calculates the new pose based on wheel velocities.
 *
 * Robots are controlled by senor input, which modify wheel velocities.
 *
 * The touch sensor is activated when the robot collides with an object.
 * The heading is modified after a collision to move the robot away from the
 * other object.
 */
class Robot : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor using initialization values from params.h.
   */
  Robot();

  /**
   * @brief Robot's destructor. `delete` all members.
   */
  virtual ~Robot() {}

  /**
   * @brief Reset the Robot to a newly constructed state (needed for reset
   * button to work in GUI).
   */
  void Reset() override;

  /**
   * @brief Update the Robot's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
   * @brief Calculates the proper position of a sensor relative to a robot.
   *
   * @param angle_ The angle that a sensor will be placed at on a robot.
   * @return Returns the correct pose for the position of each sensor.
   */
  Pose SensorLocation(double angle_);

  /**
   * @brief Updates all of the robot's light sensor readings.
   */
  void NotifyLights(Pose pose);

  /**
   * @brief Updates all of the robot's food sensor readings.
   */
  void NotifyFood(Pose pose);

  /**
   * @brief Zeroes out all of the sensor's readings.
   */
  void ZeroSensors();

  /**
   * @brief Checks whether the starvation timer has reached 0.
   * @return Returns a boolean (true if starved, false otherwise).
   */
  bool CheckStarvation();

  /**
   * @brief Sets the robot in avoidance mode.
   */
  void HandleCollision();

  /**
   * @brief Returns status of hunger in robots.
   */
  bool GetHunger() { return hunger_; }
  void SetHunger(bool hunger) { hunger_ = hunger; }

  /**
   * @brief Resets the hunger level and hunger timer for the robot.
   */
  void ResetHunger() { hunger_level_ = 0; hunger_time_ = 100; }

  /**
   * @brief Get the name of the Robot for visualization and for debugging.
   */
  std::string get_name() const override { return "Robot"; }

  RobotType get_robot_type() { return type_; }
  void set_robot_type(RobotType rtype) { type_ = rtype; }

  double get_light_sensitivity() { return light_sensitivity_; }
  void set_light_sensitivity(double ls) {
    light_sensitivity_ = ls;
    left_light_sensor_.SetLightSensitivity(light_sensitivity_);
    right_light_sensor_.SetLightSensitivity(light_sensitivity_);
  }

  MotionHandlerRobot get_motion_handler() { return motion_handler_; }

  MotionBehaviorDifferential get_motion_behavior() { return motion_behavior_; }

  Pose get_left_sensor_pose() const { return left_light_sensor_.get_pose(); }
  Pose get_right_sensor_pose() const { return right_light_sensor_.get_pose(); }

 private:
  // Determines the type of robot
  RobotType type_;
  // Manages pose and wheel velocities that change with time and collisions.
  MotionHandlerRobot motion_handler_;
  // Calculates changes in pose based on elapsed time and wheel velocities.
  MotionBehaviorDifferential motion_behavior_;
  // Light sensitivity determines strength of robot reaction to light.
  double light_sensitivity_;
  // The two light sensors utilized by the robot.
  LightSensor left_light_sensor_;
  LightSensor right_light_sensor_;
  // The two light sensors utilized by the robot.
  FoodSensor left_food_sensor_;
  FoodSensor right_food_sensor_;
  // Toggle for existence of hunger.
  bool hunger_;
  // Determines the delay before hunger.
  double hunger_time_;
  // Determines hunger levels of the robot.
  double hunger_level_;
  // Serves as a timer to determine if a robot has starved.
  double starvation_time_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_H_
