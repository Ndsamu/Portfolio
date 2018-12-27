/**
 * @file obstacle.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_OBSTACLE_H_
#define SRC_OBSTACLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/motion_handler_obstacle.h"
#include "src/motion_behavior_differential.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class MotionbehaviorDifferential;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a robot within the arena.
 *
 * Robots are composed of a motion handler, motion behavior, and touch sensor.
 * These classes interact to maintain the pose (position and heading) of the
 * robot. At each time step, the wheel velocities are used to calculate the
 * next pose of the robot. The handler manages the pose and user requests. The
 * behavior calculates the new pose based on wheel velocities.
 *
 * Robots can be controlled through keypress, which modify wheel velocities.
 *
 * The touch sensor is activated when the robot collides with an object.
 * The heading is modified after a collision to move the robot away from the
 * other object.
 */
class Obstacle : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor.
   */
  Obstacle();

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
   * @brief Handles the collision by setting the sensor to activated.
   */
  void HandleCollision();

  /**
   * @brief Get the name of the Obstacle for visualization purposes, and to
   * aid in debugging.
   */
  std::string get_name() const override {
    return "Obstacle" + std::to_string(get_id());
  }

  MotionHandlerObstacle get_motion_handler() { return motion_handler_; }

  MotionBehaviorDifferential get_motion_behavior() { return motion_behavior_; }

  void set_state(int state) { state_ = state; }

  int get_state() { return state_; }

 private:
  // Manages pose and wheel velocities that change with time and collisions.
  MotionHandlerObstacle motion_handler_;
  // Calculates changes in pose based on elapsed time and wheel velocities.
  MotionBehaviorDifferential motion_behavior_;
  // Used to determine if the obstacle is moving forward or reversing in an arc.
  int state_;
  int avoid_time_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_OBSTACLE_H_
