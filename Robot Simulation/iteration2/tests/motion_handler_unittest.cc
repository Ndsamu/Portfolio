// Google Test Framework
#include <gtest/gtest.h>
#include <cmath>

// Project code from the ../src directory
#include "../src/arena.h"
#include "src/arena_params.h"
#include "../src/pose.h"
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
    // Initialize Arena for Collections of TESTS
    csci3081::arena_params aparams;
    arena = new csci3081::Arena(&aparams);
    arena->set_game_status(PLAYING);
    robot = arena->robot();
    *motion_handler = robot->get_motion_handler();
  }
  csci3081::Arena * arena;
  csci3081::Robot * robot;
  csci3081::MotionHandlerRobot * motion_handler;

};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(MotionHandlerTest, UpdateVelocity) {
  // Velocity of 0 will be consistent across robot types
  // so there is only one test included.
  motion_handler->UpdateVelocity(0, 0, 0);
  EXPECT_EQ(motion_handler->get_velocity().left, 0);
  EXPECT_EQ(motion_handler->get_velocity().right, 0);

  motion_handler->UpdateVelocity(0, 1000, 1000);
  EXPECT_EQ(motion_handler->get_velocity().left, 10);
  EXPECT_EQ(motion_handler->get_velocity().right, 10);
  motion_handler->UpdateVelocity(1, 1000, 1000);
  EXPECT_EQ(motion_handler->get_velocity().left, 10);
  EXPECT_EQ(motion_handler->get_velocity().right, 10);
  motion_handler->UpdateVelocity(2, 1000, 1000);
  EXPECT_EQ(motion_handler->get_velocity().left, -10);
  EXPECT_EQ(motion_handler->get_velocity().right, -10);
  motion_handler->UpdateVelocity(3, 1000, 1000);
  EXPECT_EQ(motion_handler->get_velocity().left, -10);
  EXPECT_EQ(motion_handler->get_velocity().right, -10);

  motion_handler->UpdateVelocity(0, 500, 1000);
  EXPECT_EQ(motion_handler->get_velocity().left, 5);
  EXPECT_EQ(motion_handler->get_velocity().right, 10);
  motion_handler->UpdateVelocity(1, 500, 1000);
  EXPECT_EQ(motion_handler->get_velocity().left, 10);
  EXPECT_EQ(motion_handler->get_velocity().right, 5);
  motion_handler->UpdateVelocity(2, 500, 1000);
  EXPECT_EQ(motion_handler->get_velocity().left, -5);
  EXPECT_EQ(motion_handler->get_velocity().right, -10);
  motion_handler->UpdateVelocity(3, 500, 1000);
  EXPECT_EQ(motion_handler->get_velocity().left, -10);
  EXPECT_EQ(motion_handler->get_velocity().right, -5);
};

#endif
