// Google Test Framework
#include <gtest/gtest.h>
#include <cmath>

// Project code from the ../src directory
#include "../src/motion_handler_robot.h"
#include "../src/robot_type.h"
#include "../src/robot.h"
#include "../src/params.h"
#include <math.h>

#ifdef MOTION_HANDLER_TEST

/************************************************************************
* SETUP
*************************************************************************/

class MotionHandlerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    robot = new csci3081::Robot();
    motion_handler = new csci3081::MotionHandlerRobot(robot);
  }
  csci3081::Robot * robot;
  csci3081::MotionHandlerRobot * motion_handler;

};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST_F(MotionHandlerTest, State) {
  motion_handler->SetState(true);
  EXPECT_EQ(motion_handler->GetState(), true) << "FAIL: State - State was not set to true.";
  motion_handler->SetState(false);
  EXPECT_EQ(motion_handler->GetState(), false) << "FAIL: State - State was not set to false.";
};

TEST_F(MotionHandlerTest, FearBehavior) {
  // Tests max sensor input
  motion_handler->UpdateVelocity(csci3081::kCoward, 1000, 1000, false, 0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, MAX_VELOCITY) << "FAIL: FearBehavior - Left max velocity was not reached.";
  EXPECT_EQ(motion_handler->get_velocity().right, MAX_VELOCITY) << "FAIL: FearBehavior - Right max velocity was not reached.";
  // Tests min sensor input
  motion_handler->UpdateVelocity(csci3081::kCoward, 0, 0, false, 0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, 0) << "FAIL: FearBehavior - Left min velocity was not reached.";
  EXPECT_EQ(motion_handler->get_velocity().right, 0) << "FAIL: FearBehavior - Right min velocity was not reached.";
  // Tests equivalence partition
  motion_handler->UpdateVelocity(csci3081::kCoward, 500, 500, false, 0, 0, 0);
  EXPECT_GT(motion_handler->get_velocity().left, 0) << "FAIL: FearBehavior - Left velocity was not greater than 0.";
  EXPECT_GT(motion_handler->get_velocity().right, 0) << "FAIL: FearBehavior - Right velocity was not greater than 0.";
  EXPECT_LT(motion_handler->get_velocity().left, MAX_VELOCITY) << "FAIL: FearBehavior - Left velocity was not less than 10.";
  EXPECT_LT(motion_handler->get_velocity().right, MAX_VELOCITY) << "FAIL: FearBehavior - Right velocity was not less than 10.";
  // Tests behavior of robot
  motion_handler->UpdateVelocity(csci3081::kCoward, 0, 1000, false, 0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, 0) << "FAIL: FearBehavior - Left velocity was not connected to proper sensor.";
  EXPECT_EQ(motion_handler->get_velocity().right, MAX_VELOCITY) << "FAIL: FearBehavior - Right velocity was not connected to proper sensor.";
  // Tests behavior of robot
  motion_handler->UpdateVelocity(csci3081::kCoward, 1000, 0, false, 0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, MAX_VELOCITY) << "FAIL: FearBehavior - Left velocity was not connected to proper sensor.";
  EXPECT_EQ(motion_handler->get_velocity().right, 0) << "FAIL: FearBehavior - Right velocity was not connected to proper sensor.";
  // Tests velocity range
  motion_handler->UpdateVelocity(csci3081::kCoward, 10000, 10000, false, 0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, MAX_VELOCITY) << "FAIL: FearBehavior - Clamping left velocity to MAX_VELOCITY failed.";
  EXPECT_EQ(motion_handler->get_velocity().right, MAX_VELOCITY) << "FAIL: FearBehavior - Clamping right velocity to MAX_VELOCITY failed.";
  // Tests velocity range
  motion_handler->UpdateVelocity(csci3081::kCoward, -10000, -10000, false, 0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, MIN_VELOCITY) << "FAIL: FearBehavior - Clamping left velocity to MIN_VELOCITY failed.";
  EXPECT_EQ(motion_handler->get_velocity().right, MIN_VELOCITY) << "FAIL: FearBehavior - Clamping right velocity to MIN_VELOCITY failed.";
};

TEST_F(MotionHandlerTest, ExploreBehavior) {
  // Tests max sensor input
  motion_handler->UpdateVelocity(csci3081::kExplore, 1000, 1000, false, 0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, MIN_VELOCITY) << "FAIL: ExploreBehavior - Left max velocity was not reached.";
  EXPECT_EQ(motion_handler->get_velocity().right, MIN_VELOCITY) << "FAIL: ExploreBehavior - Right max velocity was not reached.";
  // Tests min sensor input
  motion_handler->UpdateVelocity(csci3081::kExplore, 0, 0, false, 0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, 0) << "FAIL: ExploreBehavior - Left min velocity was not reached.";
  EXPECT_EQ(motion_handler->get_velocity().right, 0) << "FAIL: ExploreBehavior - Right min velocity was not reached.";
  // Tests equivalence partition
  motion_handler->UpdateVelocity(csci3081::kExplore, 500, 500, false, 0, 0, 0);
  EXPECT_GT(motion_handler->get_velocity().left, MIN_VELOCITY) << "FAIL: ExploreBehavior - Left velocity was not greater than 0.";
  EXPECT_GT(motion_handler->get_velocity().right, MIN_VELOCITY) << "FAIL: ExploreBehavior - Right velocity was not greater than 0.";
  EXPECT_LT(motion_handler->get_velocity().left, 0) << "FAIL: ExploreBehavior - Left velocity was not less than 10.";
  EXPECT_LT(motion_handler->get_velocity().right, 0) << "FAIL: ExploreBehavior - Right velocity was not less than 10.";
  // Tests behavior of robot
  motion_handler->UpdateVelocity(csci3081::kExplore, 0, 1000, false, 0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, MIN_VELOCITY) << "FAIL: ExploreBehavior - Left velocity was not connected to proper sensor.";
  EXPECT_EQ(motion_handler->get_velocity().right, 0) << "FAIL: ExploreBehavior - Right velocity was not connected to proper sensor.";
  // Tests behavior of robot
  motion_handler->UpdateVelocity(csci3081::kExplore, 1000, 0, false, 0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, 0) << "FAIL: ExploreBehavior - Left velocity was not connected to proper sensor.";
  EXPECT_EQ(motion_handler->get_velocity().right, MIN_VELOCITY) << "FAIL: ExploreBehavior - Right velocity was not connected to proper sensor.";
  // Tests velocity range min
  motion_handler->UpdateVelocity(csci3081::kExplore, 10000, 10000, false, 0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, MIN_VELOCITY) << "FAIL: ExploreBehavior - Clamping left velocity to MIN_VELOCITY failed.";
  EXPECT_EQ(motion_handler->get_velocity().right, MIN_VELOCITY) << "FAIL: ExploreBehavior - Clamping right velocity to MIN_VELOCITY failed.";
  // Tests velocity range max
  motion_handler->UpdateVelocity(csci3081::kExplore, -10000, -10000, false, 0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, MAX_VELOCITY) << "FAIL: ExploreBehavior - Clamping left velocity to MAX_VELOCITY failed.";
  EXPECT_EQ(motion_handler->get_velocity().right, MAX_VELOCITY) << "FAIL: ExploreBehavior - Clamping right velocity to MAX_VELOCITY failed.";
};

#endif
