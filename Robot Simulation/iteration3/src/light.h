/**
 * @file light.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_LIGHT_H_
#define SRC_LIGHT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/arena_mobile_entity.h"
#include "src/common.h"
#include "src/motion_handler_light.h"
#include "src/motion_behavior_differential.h"
#include "src/entity_type.h"
#include "src/pose.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class MotionbehaviorDifferential;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a light within the arena.
 *
 * Lights are composed of a motion handler, motion behavior, and touch sensor.
 * These classes interact to maintain the pose (position and heading) of the
 * light. At each time step, the wheel velocities are used to calculate the
 * next pose of the light. The handler manages the pose and user requests. The
 * behavior calculates the new pose based on wheel velocities.
 *
 * The touch sensor is activated when the light collides with an object.
 * Upon collision, the lights reverse in an arc before continuing forward.
 */
class Light : public ArenaMobileEntity {
 public:
  /**
   * @brief Constructor.
   */
  Light();

  /**
   * @brief Reset the Light to a newly constructed state (needed for reset
   * button to work in GUI).
   */
  void Reset() override;

  /**
   * @brief Update the Light's position and velocity after the specified
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
   * @brief Get the name of the Light for visualization purposes, and to
   * aid in debugging.
   */
  std::string get_name() const override {
    return "Light" + std::to_string(get_id());
  }

  MotionHandlerLight get_motion_handler() { return motion_handler_; }

  MotionBehaviorDifferential get_motion_behavior() { return motion_behavior_; }

  void SetState(bool state) { state_ = state; }
  bool GetState() { return state_; }

 private:
  // Manages pose and wheel velocities that change with time and collisions.
  MotionHandlerLight motion_handler_;
  // Calculates changes in pose based on elapsed time and wheel velocities.
  MotionBehaviorDifferential motion_behavior_;
  // Used to determine if the light is moving forward or reversing in an arc.
  bool state_;
  // Amount of time that a light reverses in an arc.
  int avoid_time_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_H_
