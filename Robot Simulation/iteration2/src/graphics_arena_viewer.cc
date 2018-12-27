/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <iostream>

#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/robot.h"
#include "src/rgb_color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
GraphicsArenaViewer::GraphicsArenaViewer(
    const struct arena_params *const params,
    Arena * arena, Controller * controller) :
    GraphicsApp(
        params->x_dim + GUI_MENU_WIDTH + GUI_MENU_GAP * 2,
        params->y_dim,
        "Robot Simulation"),
    controller_(controller),
    arena_(arena) {
  auto *gui = new nanogui::FormHelper(screen());
  nanogui::ref<nanogui::Window> window =
      gui->addWindow(
          Eigen::Vector2i(10 + GUI_MENU_GAP, 10),
          "Menu");

  gui->addGroup("Simulation Control");
  playing_button_ =
    gui->addButton(
      "Play",
      std::bind(&GraphicsArenaViewer::OnPlayingBtnPressed, this));
  new_game_button_ =
    gui->addButton(
      "New Game",
      std::bind(&GraphicsArenaViewer::OnNewGameBtnPressed, this));
  screen()->setSize({X_DIM, Y_DIM});
  screen()->performLayout();
} /* GraphicsArenaViewer() */

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (!paused_ &&
    arena_->get_game_status() != WON &&
    arena_->get_game_status() != LOST &&
    arena_->get_game_status() != PAUSED) {
    controller_->AdvanceTime(dt);
  }
} /* UpdateSimulation() */

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnPlayingBtnPressed() {
  // Not implemented. Sample code provided to show how to implement.
  if (!paused_) {
    controller_->AcceptCommunication(kPause);
    paused_ = true;
    playing_button_->setCaption("Play");
  } else {
    controller_->AcceptCommunication(kPlay);
    paused_ = false;
    playing_button_->setCaption("Pause");
  }
} /* OnPlayingBtnPressed() */

void GraphicsArenaViewer::OnNewGameBtnPressed() {
  controller_->AcceptCommunication(kNewGame);
} /* OnNewGameBtnPressed() */

/**
  * OnSpecialKeyDown is called when the user presses down on one of the
  * special keys (e.g. the arrow keys).
  */
void GraphicsArenaViewer::OnSpecialKeyDown(int key,
  __unused int scancode, __unused int modifiers) {
    Communication key_value = kNone;
    switch (key) {
      case GLFW_KEY_UP:
        key_value = kKeyUp;
        break;
      case GLFW_KEY_DOWN:
        key_value = kKeyDown;
        break;
      case GLFW_KEY_LEFT:
        key_value = kKeyLeft;
        break;
      case GLFW_KEY_RIGHT:
        key_value = kKeyRight;
        break;
      default: {}
    }
  controller_->AcceptCommunication(key_value);
} /* OnSpecialKeyDown() */

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
/**
  * There is a known bug where the sensors lag behind the robot when being drawn
  * However, the actual position of sensors has been tested and is accurate.
*/
void GraphicsArenaViewer::DrawSensors(NVGcontext *ctx,
                                     const Robot *const robot) {
  nvgSave(ctx);
  nvgTranslate(ctx,
    static_cast<float>(robot->get_left_sensor_pose().x),
    static_cast<float>(robot->get_left_sensor_pose().y));
  // Sensor circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, robot->get_radius()/2);
  nvgFillColor(ctx,
              nvgRGBA(255, 255, 0, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);
  nvgRestore(ctx);
  nvgRestore(ctx);

  nvgSave(ctx);
  nvgTranslate(ctx,
   static_cast<float>(robot->get_right_sensor_pose().x),
   static_cast<float>(robot->get_right_sensor_pose().y));
  // Sensor circle
  nvgBeginPath(ctx);
  nvgCircle(ctx, 0.0, 0.0, robot->get_radius()/2);
  nvgFillColor(ctx,
               nvgRGBA(255, 255, 0, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);
  nvgRestore(ctx);
  nvgRestore(ctx);
} /* DrawSensors() */

void GraphicsArenaViewer::DrawArena(NVGcontext *ctx) {
  nvgBeginPath(ctx);
  // Creates new rectangle shaped sub-path.
  nvgRect(ctx, 0, 0, arena_->get_x_dim(), arena_->get_y_dim());
  nvgStrokeColor(ctx, nvgRGBA(255, 255, 255, 255));
  nvgStroke(ctx);
} /* DrawArena() */

void GraphicsArenaViewer::DrawEntity(NVGcontext *ctx,
                                       const ArenaEntity *const entity) {
  // light's circle
  nvgBeginPath(ctx);
  nvgCircle(ctx,
            static_cast<float>(entity->get_pose().x),
            static_cast<float>(entity->get_pose().y),
            static_cast<float>(entity->get_radius()));
  nvgFillColor(ctx,
               nvgRGBA(entity->get_color().r, entity->get_color().g,
                       entity->get_color().b, 255));
  nvgFill(ctx);
  nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgStroke(ctx);

  // light id text label
  nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
  nvgText(ctx,
          static_cast<float>(entity->get_pose().x),
          static_cast<float>(entity->get_pose().y),
          entity->get_name().c_str(), nullptr);
} /* DrawEntity() */

void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 12.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);
  DrawArena(ctx);
  std::vector<ArenaEntity *> entities = arena_->get_entities();
  for (auto &entity : entities) {
    if (entity->get_type() == kRobot) {
      DrawSensors(ctx, dynamic_cast<Robot *>(entity));
    }
    DrawEntity(ctx, entity);
  } /* for(i..) */
} /* DrawUsingNanoVG() */

NAMESPACE_END(csci3081);
