// Google Test Framework
#include <gtest/gtest.h>
#include <cmath>

// Project code from the ../src directory
#include "../src/arena.h"
#include "src/arena_params.h"
#include "../src/light.h"
#include "../src/pose.h"
#include "../src/light_sensor.h"
#include "../src/robot.h"
#include "../src/params.h"
#include <math.h>

#ifdef SENSOR_LIGHT_TEST

/************************************************************************
* SETUP
*************************************************************************/

class SensorLightTest : public ::testing::Test {
 protected:
   virtual void SetUp() {
     // Initialize Arena for Collections of TESTS
     csci3081::arena_params aparams;
     arena = new csci3081::Arena(&aparams);
     arena->set_game_status(PLAYING);
     robot = arena->robot();
     light = arena->light();
     light_sensor = new csci3081::LightSensor();
   }
   csci3081::Arena * arena;
   csci3081::Robot * robot;
   csci3081::Light * light;
   csci3081::LightSensor * light_sensor;
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

// Tests are ordered sequentially in order to prove functionality
// of methods used in remaining tests

TEST_F(SensorLightTest, Reset) {};

TEST_F(SensorLightTest, Pose) {
  light_sensor->set_pose(0.0, 0.0);
  EXPECT_EQ(light_sensor->get_pose().x, 0.0) << "FAIL: Light Sensors x-coordinate incorrect.";
  EXPECT_EQ(light_sensor->get_pose().y, 0.0) << "FAIL: Light Sensors y-coordinate incorrect.";
};

TEST_F(SensorLightTest, ZeroReading) {
  light->set_position(0.0, 0.0);
  light_sensor->set_pose(0.0, 0.0);
  arena->UpdateEntitiesTimestep();
  light_sensor->ZeroReading();
  EXPECT_EQ(light_sensor->GetReading(), 0.0) << "FAIL: Light Sensor reading was not zeroed.";
};

// For this test the floor of the sensor reading had to be taken
// as the sensor reading was extremely close to 0 but had a small reading.
TEST_F(SensorLightTest, CalculateReading) {
  light->set_position(0.0, 0.0);
  light_sensor->set_pose(0.0, 0.0);
  light_sensor->CalculateReading(light->get_pose());
  EXPECT_EQ(light_sensor->GetReading(), 1000.0) << "FAIL: Light Sensor did not produce maximum reading.";
  light_sensor->ZeroReading();
  light_sensor->set_pose(1000.0, 1000.0);
  light_sensor->CalculateReading(light->get_pose());
  EXPECT_EQ(floor(light_sensor->GetReading()), 0.0) << "FAIL: Light Sensor did not produce minimum reading.";
};

// I chose not to include a test for GetReading() as this
// was clearly valid based upon CalculateReading tests.

#endif
