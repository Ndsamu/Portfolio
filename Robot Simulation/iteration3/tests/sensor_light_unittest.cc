// Google Test Framework
#include <gtest/gtest.h>
#include <cmath>

// Project code from the ../src directory
#include "../src/arena.h"
#include "../src/arena_params.h"
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
     light_sensor = new csci3081::LightSensor();
   }
   csci3081::LightSensor * light_sensor;
   csci3081::Pose origin = csci3081::Pose(0, 0);
   csci3081::Pose close = csci3081::Pose(50, 50);
   csci3081::Pose middle = csci3081::Pose(500, 500);
   csci3081::Pose distant = csci3081::Pose(1000, 1000);
};


/*******************************************************************************
 * Test Cases
 ******************************************************************************/

// Tests are ordered sequentially in order to prove functionality
// of methods used in remaining tests

TEST_F(SensorLightTest, Constructors) {
  csci3081::LightSensor * pose_constructor = new csci3081::LightSensor(distant);
  EXPECT_EQ(pose_constructor->get_pose().x, 1000.0) << "FAIL: Constructors - Light Sensors x-coordinate incorrect.";
  EXPECT_EQ(pose_constructor->get_pose().y, 1000.0) << "FAIL: Constructors - Light Sensors y-coordinate incorrect.";
  csci3081::LightSensor * sens_constructor = new csci3081::LightSensor(0.5);
  EXPECT_EQ(sens_constructor->GetLightSensitivity(), 0.5) << "FAIL: Constructors - Light Sensitivity was not 0.5.";
};

TEST_F(SensorLightTest, SetPose) {
  light_sensor->set_pose(0.0, 0.0);
  EXPECT_EQ(light_sensor->get_pose().x, 0.0) << "FAIL: SetPose - Light Sensors x-coordinate incorrect.";
  EXPECT_EQ(light_sensor->get_pose().y, 0.0) << "FAIL: SetPose - Light Sensors y-coordinate incorrect.";
};

TEST_F(SensorLightTest, LightSensitivity) {
  light_sensor->SetLightSensitivity(0.0);
  EXPECT_EQ(light_sensor->GetLightSensitivity(), 0.0) << "FAIL: LightSensitivity - Set to 0.";
  light_sensor->SetLightSensitivity(1.0);
  EXPECT_EQ(light_sensor->GetLightSensitivity(), 1.0) << "FAIL: LightSensitivity - Set to 1.";
};

TEST_F(SensorLightTest, ZeroReading) {
  light_sensor->CalculateReading(origin);
  light_sensor->ZeroReading();
  EXPECT_EQ(light_sensor->GetReading(), 0.0) << "FAIL: ZeroReading - Light Sensor reading was not zeroed.";
};

// For this test the floor of the sensor reading had to be taken
// as the sensor reading was extremely close to 0 but had a small reading.
TEST_F(SensorLightTest, CalculateReading) {
  light_sensor->set_pose(origin);
  light_sensor->CalculateReading(origin);
  EXPECT_EQ(light_sensor->GetReading(), 1000.0) << "FAIL: CalculateReading - Light Sensor did not produce maximum reading.";
  light_sensor->ZeroReading();
  light_sensor->CalculateReading(distant);
  EXPECT_EQ(floor(light_sensor->GetReading()), 0.0) << "FAIL: CalculateReading - Light Sensor did not produce minimum reading.";
};

TEST_F(SensorLightTest, LightSensMax) {
  light_sensor->set_pose(origin);
  light_sensor->SetLightSensitivity(1.0);
  light_sensor->CalculateReading(origin);
  EXPECT_EQ(light_sensor->GetReading(), 1000.0) << "FAIL: LightSensMax - Light Sensor did not produce maximum reading.";
};

TEST_F(SensorLightTest, LightSensMin) {
  light_sensor->set_pose(origin);
  light_sensor->SetLightSensitivity(0.0);
  light_sensor->CalculateReading(origin);
  EXPECT_EQ(light_sensor->GetReading(), 0.0) << "FAIL: LightSensMin - Light Sensor did not produce minimum reading.";
};

TEST_F(SensorLightTest, TwoLightsBoundary) {
  light_sensor->set_pose(origin);
  light_sensor->SetLightSensitivity(1.0);
  // Calculates Reading twice which is effectively placing two lights
  light_sensor->CalculateReading(close);
  light_sensor->CalculateReading(close);
  EXPECT_EQ(light_sensor->GetReading(), 1000.0) << "FAIL: CalculateReading - Light Sensor did not produce maximum reading.";
  light_sensor->ZeroReading();
  light_sensor->CalculateReading(distant);
  light_sensor->CalculateReading(distant);
  EXPECT_EQ(floor(light_sensor->GetReading()), 0.0) << "FAIL: CalculateReading - Light Sensor did not produce minimum reading.";
};

TEST_F(SensorLightTest, TwoLightsEquivalence) {
  light_sensor->ZeroReading();
  light_sensor->CalculateReading(middle);
  light_sensor->CalculateReading(middle);
  EXPECT_GT(light_sensor->GetReading(), 0.0) << "FAIL: TwoLightsEquivalence - Light Sensor was not greater than zero.";
  EXPECT_LT(light_sensor->GetReading(), 1000.0) << "FAIL: TwoLightsEquivalence - Light Sensor was not less than 1000.";
};

// I chose not to include a test for GetReading() as this
// was clearly valid based upon CalculateReading tests.

#endif
