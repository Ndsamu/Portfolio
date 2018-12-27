/**
 * @file sensor.h
 *
 * @copyright 2018, All rights reserved.
 */

#ifndef SRC_SENSOR_H_
#define SRC_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <utility>
#include <vector>
#include <iostream>
#include "src/common.h"
#include "src/pose.h"
#include "src/entity_type.h"
#include "src/arena_entity.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
* @brief The sensor class which all other sensors inherit from.
*
* Currently, all of the sensor functionality for lights and food
* is handled in this header.
*
*/
class Sensor {
 public:
   /**
    * @brief Sensor's constructor.
    *
    * Initialize pose to the default pose.
    */
  Sensor() : pose_(DEFAULT_POSE) {}

  explicit Sensor(Pose pose) : pose_() {
    pose_ = pose;
  }

  /**
  * @brief Sensor's destructor. `delete` all members.
  */
  virtual ~Sensor() = default;

  /**
  * @brief Resets the pose and sensor reading.
  */
  void Reset() {
    pose_ = DEFAULT_POSE;
    reading_ = 0;
  }

  Pose get_pose() const { return pose_; }
  void set_pose(Pose pose) { pose_ = pose; }

  void set_pose(double x, double y) {
    pose_ = Pose(x, y);
  }

  /**
  * @brief Sets the sensor's reading back to 0 for fresh input.
  */
  void ZeroReading() { reading_ = 0; }

  double GetReading() {
    return reading_;
  }

  /**
   * @brief Checks for the presence of a light.
   *
   * *@param[in] location_ The pose of a light or food object.
   *
   * Calculates distance from the pose passed in before calculating
   * a reading relative to the distance.
  **/
  void CalculateReading(Pose location_) {
    double deltaX = (pose_.x - location_.x);
    double deltaY = (pose_.y - location_.y);
    double distance = pow(deltaX*deltaX + deltaY*deltaY, 0.5) - LIGHT_RADIUS;
    reading_ += 2000/pow(1.015, distance);
    if (reading_ > 1000) {
     reading_ = 1000;
    }
  }

 protected:
  // The sensors position and heading
  Pose pose_;
  // The reading stored to be used by a robot.
  double reading_{0};
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_H_
