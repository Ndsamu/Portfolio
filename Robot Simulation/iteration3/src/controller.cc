/**
 * @file controller.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>

#include "src/arena_params.h"
#include "src/common.h"
#include "src/controller.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

Controller::Controller() : last_dt(0) {
  // Initialize default properties for various arena entities
  arena_params aparams;
  aparams.n_robots = N_ROBOTS;
  aparams.n_lights = N_LIGHTS;
  aparams.n_foods = N_FOODS;
  aparams.x_dim = ARENA_X_DIM;
  aparams.y_dim = ARENA_Y_DIM;

  arena_ = new Arena(&aparams);

  // Start up the graphics (which creates the arena).
  // Run() will enter the nanogui::mainloop().
  viewer_ = new GraphicsArenaViewer(&aparams, arena_, this);
} /* Controller() */

void Controller::Run() { viewer_->Run(); }  /* Run() */

void Controller::AdvanceTime(double dt) {
  if ((last_dt + dt) <= .05) {
    last_dt += dt;
    return;
  }
  last_dt = 0;
  arena_->AdvanceTime(dt);
} /* AdvanceTime() */

void Controller::AcceptCommunication(Communication com) {
  arena_->AcceptCommand(ConvertComm(com));
} /* AcceptCommunication() */

/**
 * Converts communication from one source to appropriate communication to
 * the other source. For example, the viewer sends a kKeyUp communication,
 * and this translates to a kIncreaseSpeed communication to Arena.
 */
Communication Controller::ConvertComm(Communication com) {
  int cowards;
  int explorers;
  switch (com) {
    case (kRobots) :
      explorers = static_cast<int>(viewer_->robot_ratio_*viewer_->robot_count_);
      cowards = viewer_->robot_count_ - explorers;
      arena_->AddRobot(cowards, kCoward);
      arena_->AddRobot(explorers, kExplore);
      return kRobots;
    case (kLights) :
      arena_->AddLight(viewer_->light_count_);
      return kLights;
    case (kFoodOn) :
      arena_->AddFood(viewer_->food_count_);
      return kFoodOn;
    case (kFoodOff) :
      return kFoodOff;
    case (kLightSensitivity) :
      arena_->set_light_sensitivity(viewer_->light_sensitivity_);
      return kLightSensitivity;
    case (kPlay) :
      return kPlay;
    case (kPause) :
      return kPause;
    case (kNewGame) :
      return kNewGame;
    default: return kNone;
  }
} /* ConvertComm() */

NAMESPACE_END(csci3081);
