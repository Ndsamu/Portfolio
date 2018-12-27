/**
 * @file food_sensor.h
 *
 * @copyright 2018, All rights reserved.
 */

#ifndef SRC_FOOD_SENSOR_H_
#define SRC_FOOD_SENSOR_H_

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
  * @brief Food sensor used by robots in order to detect presence of food.
  *
  * Inherits from Sensor where the relevant functionality resides.
  */
class FoodSensor : public Sensor {
 public:
   /**
    * @brief FoodSensor constructor.
    *
    */
  FoodSensor() {}

  /**
   * @brief FoodSensor constructor with pose parameter.
   *
   */
  explicit FoodSensor(Pose pose) {
    pose_ = pose;
  }
};

NAMESPACE_END(csci3081);

#endif  // SRC_FOOD_SENSOR_H_
