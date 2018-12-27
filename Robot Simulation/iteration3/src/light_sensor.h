/**
 * @file light_sensor.h
 *
 * @copyright 2018, All rights reserved.
 */

#ifndef SRC_LIGHT_SENSOR_H_
#define SRC_LIGHT_SENSOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/params.h"
#include "src/sensor.h"
#include "src/common.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief Light sensor used by robots in order to detect presence of lights.
  *
  * Inherits from Sensor where the relevant functionality resides.
  */
class LightSensor : public Sensor {
 public:
   /**
    * @brief LightSensor constructor.
    *
    */
  LightSensor() {}

  /**
   * @brief LightSensor constructor with pose parameter.
   *
   */
  explicit LightSensor(Pose pose) {
    pose_ = pose;
  }

  /**
   * @brief LightSensor constructor with light sensitivity parameter.
   *
   */
  explicit LightSensor(double light_sensitivity) {
    light_sensitivity_ = 2000 * light_sensitivity;
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
    reading_ += light_sensitivity_/pow(1.015, distance);
    if (reading_ > 1000) {
     reading_ = 1000;
    }
  }

  double GetLightSensitivity() { return light_sensitivity_/2000; }
  void SetLightSensitivity(double ls) { light_sensitivity_ = 2000 * ls; }

 private:
  double light_sensitivity_{2000};
};

NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_SENSOR_H_
