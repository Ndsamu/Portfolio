/**
 * @file graphics_arena_viewer.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_GRAPHICS_ARENA_VIEWER_H_
#define SRC_GRAPHICS_ARENA_VIEWER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <MinGfx-1.0/mingfx.h>

#include "src/arena.h"
#include "src/controller.h"
#include "src/common.h"
#include "src/communication.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class Controller;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 *  @brief An application that uses the MinGfx library to open up a window that
 *  includes a few buttons for controlling the simulation and can be used to
 *  draw circles and other computer graphics.
 *
 *  After constructing a new GraphicsArenaViewer, call Run to start and run the
 *  application. Run will not return until the application window is closed.
 *  Example:
 *
 *  ```
 *  int main(int argc, char **argv) {
 *      RobotViewer *app = new RobotViewer();
 *      app->Run();
 *      return 0;
 *  }
 *  ```
 *
 *  While the window is open UpdateSimulation will be called repeatedly,
 *  once per frame.
 */
class GraphicsArenaViewer : public GraphicsApp {
 public:
  /**
   * @brief Constructor.
   *
   * @param params A arena_params passed down from main.cc for the
   * initialization of the Arena and the entities therein.
   */
  explicit GraphicsArenaViewer(const struct arena_params *const params,
                               Arena *arena, Controller *controller);

  /**
   * @brief Destructor.
   *
   * `delete` the contained Arena.
   */
  ~GraphicsArenaViewer() override { delete arena_; }

  /**
   * @brief Informs the Arena of the new time, so that it can update.
   *
   * @param dt The new timestep.
   */
  void UpdateSimulation(double dt) override;

  /**
   * @brief Configures the parameters of the Arena based on user input.
   *
   * Function is called upon user pressing the Play button in a New Game.
   */
  void Initialize();

  /**
   * @brief Handle the user pressing the pause button on the GUI.
   *
   * This will freeze the graphics--no update, until the pause button is
   * pressed again.
   */
  void OnPlayingBtnPressed();

  /**
   * @brief Handle the user pressing the new game button on the GUI.
   *
   * This will start a new game.
   */
  void OnNewGameBtnPressed();

  /**
   * @brief Toggle presence of food/hunger on or off.
   *
   * Food entities will not be present and Robots will not starve.
   */
  void OnFoodBtnPressed();

  /**
   * @brief Called each time the mouse moves on the screen within the GUI
   * window.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   * @param[in] delta How far the mouse has moved.
   */
  void OnMouseMove(__unused const Point2& pos,
                   __unused const Vector2& delta) override {};

  /**
   * @brief Called each time the left mouse button is clicked.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnLeftMouseDown(__unused const Point2& pos) override {};

  /**
   * @brief Called each time the left mouse button is released.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnLeftMouseUp(__unused const Point2& pos) override {};

  /**
   * @brief Called each time the right mouse button is clicked.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnRightMouseDown(__unused const Point2& pos) override {};

  /**
   * @brief Called each time the right mouse button is released.
   *
   * Origin is at the lower left of the window. This function is a stub.
   *
   * @param[in] pos The position of the release.
   */
  void OnRightMouseUp(__unused const Point2& pos) override {};

  /**
   * @brief Called each time a character key is pressed.
   *
   * @param[in] c Character representing a key that was pressed.
   * @param[in] modifiers Any modifier keys that were also pressed.
   */
  void OnKeyDown(__unused const char *c, __unused int modifiers) override {};

  /**
   * @brief Called each time a character key is released.
   *
   * @param[in] c Character representing a key that was released.
   * @param[in] modifiers Any modifier keys that were held with the key.
   */
  void OnKeyUp(__unused const char *c, __unused int modifiers) override {};

  /**
   * @brief Draw the Arena with all of its entities using `nanogui`.
   *
   * This is the primary driver for drawing all entities in the Arena. It is
   * called at each iteration of `nanogui::mainloop()`.
   *
   * @param[in] ctx Context for nanogui.
   */
  void DrawUsingNanoVG(NVGcontext *ctx) override;

  /**
   * @brief Draw using `OpenGL`. This method is unimplemented, as currently
   * we are doing all drawing with `nanovg` in this application, so it is empty.
   */
  void DrawUsingOpenGL() override {}

  /**
   * @brief Under certain circumstance, the compiler requires that the
   * assignment operator is not defined. This `deletes` the default
   * assignment operator.
   */
  GraphicsArenaViewer &operator=(const GraphicsArenaViewer &other) = delete;

  /**
   * @brief Under certain circumstance, the compiler requires that the copy
   * constructor is not defined. This `deletes` the default copy constructor.
   */
  GraphicsArenaViewer(const GraphicsArenaViewer &other) = delete;

  // Paramaters specified by user's slider choice
  int robot_count_{5};
  int light_count_{3};
  int food_count_{3};
  double robot_ratio_{0.5};
  // Boolean for presence of food and hunger in the arena.
  bool food_{true};
  // Determines light sensitivity for robots
  double light_sensitivity_{1.0};

 private:
   /**
    * @brief Draw the Arena using `nanogui`.
    *
    * This function requires an active `nanovg` drawing context (`ctx`), so it
    * should probably only be called from with DrawUsingNanoVG.
    *
    * @param[in] ctx The `nanovg` context.
    */
  void DrawArena(NVGcontext *ctx);

  /**
   * @brief Draw a Robot's sensors using `nanogui`.
   *
   * This function requires an active `nanovg` drawing context (`ctx`), so it
   * should probably only be called from with DrawUsingNanoVG.
   *
   * @param[in] ctx The `nanovg` context.
   * @param[in] robot The specific Robot handle.
   */
  void DrawSensors(NVGcontext *ctx, const class Robot *const robot);

  /**
   * @brief Draw any entity using `nanogui`.
   *
   * This function requires an active `nanovg` drawing context (`ctx`), so it
   * should probably only be called from with DrawUsingNanoVG.
   *
   * @param[in] ctx The `nanovg` context.
   * @param[in] entity The entity's handle.
   */
  void DrawEntity(NVGcontext *ctx, const class ArenaEntity *const entity);

  // Controller pointer used to access controller methods.
  Controller *controller_;
  // Arena pointer used to access arena methods.
  Arena *arena_;
  // Determines whether or not GraphicsArenaViewer continues to update.
  bool paused_{true};
  // Boolean for whether or not the entities have been initialized
  bool initialized_{false};

  // buttons
  nanogui::Button *playing_button_{nullptr};
  nanogui::Button *new_game_button_{nullptr};
  nanogui::Button *food_button_{nullptr};
};

NAMESPACE_END(csci3081);

#endif  // SRC_GRAPHICS_ARENA_VIEWER_H_