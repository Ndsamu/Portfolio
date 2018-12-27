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
    * @brief FoodSensor constructor.
    *
    */
  LightSensor() {}
};

NAMESPACE_END(csci3081);

#endif  // SRC_LIGHT_SENSOR_H_
