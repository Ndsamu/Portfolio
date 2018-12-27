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
          Eigen::Vector2i(1034 + GUI_MENU_GAP, 25),
          "Menu");

  window->setLayout(new nanogui::GroupLayout());

  gui->addGroup("Simulation Control");
  playing_button_ =
    gui->addButton(
      "Play",
      std::bind(&GraphicsArenaViewer::OnPlayingBtnPressed, this));
  playing_button_->setFixedWidth(100);
  new_game_button_ =
    gui->addButton(
      "New Game",
      std::bind(&GraphicsArenaViewer::OnNewGameBtnPressed, this));
  new_game_button_->setFixedWidth(100);

  // vvvvvvvvvv  ADDED BELOW HERE (from nanogui example1.cc)   vvvvvvvvvvvvvvvv

  gui->addGroup("Arena Configuration");

  // Creating a panel impacts the layout. Widgets, sliders, buttons can be
  // assigned to either the window or the panel.
  nanogui::Widget *panel = new nanogui::Widget(window);

  food_button_ =
    gui->addButton(
      "Food (ON)",
      std::bind(&GraphicsArenaViewer::OnFoodBtnPressed, this));
  food_button_->setFixedWidth(100);

  // *************** SLIDER 1 ************************//
  new nanogui::Label(panel, "Robot Quantity", "sans-bold");
  nanogui::Slider *slider = new nanogui::Slider(panel);
  // The starting value (range is from 0 to 1)
  // Note that below the displayed value is 10* slider value.
  slider->setValue(0.5f);
  slider->setFixedWidth(100);

  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *text_box = new nanogui::TextBox(panel);
  text_box->setFixedSize(nanogui::Vector2i(60, 25));
  text_box->setFontSize(20);
  text_box->setValue("5");

  // This is the lambda function called while the user is moving the slider
  slider->setCallback(
    [text_box](float value) {
      text_box->setValue(std::to_string(static_cast<int>(value*10)));
    });
  // This is the lambda function called once the user is no longer manipulating
  // the slider.
  slider->setFinalCallback(
    [&](float value) {
      robot_count_ = static_cast<int>(value*10);
      std::cout << "Final slider value: " << value;
      std::cout << " robot " << robot_count_ << std::endl;
    });

  // *************** SLIDER 3 ************************//
  new nanogui::Label(panel, "Robot Ratio (Fear vs Exploratory)", "sans-bold");
  nanogui::Slider *slider3 = new nanogui::Slider(panel);
  slider3->setValue(0.5f);
  slider3->setFixedWidth(100);


  nanogui::TextBox *text_box3 = new nanogui::TextBox(panel);
  text_box3->setFixedSize(nanogui::Vector2i(60, 25));
  text_box3->setFontSize(20);
  text_box3->setValue("50");
  text_box3->setUnits("%");

  slider3->setCallback(
    [text_box3](float value) {
      text_box3->setValue(std::to_string(static_cast<int>(value*100)));
    });

  slider3->setFinalCallback(
    [&](float value) {
      robot_ratio_ = value;
      std::cout << "Final slider3 value: " << value;
      std::cout << " robot ratio " << robot_ratio_ << std::endl;
    });

  // *************** SLIDER 2 ************************//
  new nanogui::Label(panel, "Light Quantity", "sans-bold");
  nanogui::Slider *slider2 = new nanogui::Slider(panel);
  slider2->setValue(0.5f);
  slider2->setFixedWidth(100);

  nanogui::TextBox *text_box2 = new nanogui::TextBox(panel);
  text_box2->setFixedSize(nanogui::Vector2i(60, 25));
  text_box2->setFontSize(20);
  text_box2->setValue("3");

  slider2->setCallback(
    [text_box2](float value) {
      text_box2->setValue(std::to_string(static_cast<int>(value*5)));
    });

  slider2->setFinalCallback(
    [&](float value) {
      light_count_ = static_cast<int>(value*5);
      std::cout << "Final slider2 value: " << value;
      std::cout << " light " << light_count_ << std::endl;
    });

  // *************** SLIDER 4 ************************//
  new nanogui::Label(panel, "Light Sensitivity: ", "sans-bold");
  nanogui::Slider *slider4 = new nanogui::Slider(panel);
  slider4->setValue(1.0f);
  slider4->setFixedWidth(100);


  nanogui::TextBox *text_box4 = new nanogui::TextBox(panel);
  text_box4->setFixedSize(nanogui::Vector2i(60, 25));
  text_box4->setFontSize(20);
  text_box4->setValue("100");
  text_box4->setUnits("%");

  slider4->setCallback(
    [text_box4](float value) {
      text_box4->setValue(std::to_string(static_cast<int>(value*100)));
    });

  slider4->setFinalCallback(
    [&](float value) {
      light_sensitivity_ = value;
      std::cout << "Final slider4 value: " << value;
      std::cout << " light sensitivity " << light_sensitivity_ << std::endl;
    });

  // *************** SLIDER 5 ************************//
  new nanogui::Label(panel, "Food Quantity", "sans-bold");
  nanogui::Slider *slider5 = new nanogui::Slider(panel);
  // The starting value (range is from 0 to 1)
  // Note that below the displayed value is 10* slider value.
  slider5->setValue(0.5f);
  slider5->setFixedWidth(100);

  // Display the corresponding value of the slider in this textbox
  nanogui::TextBox *text_box5 = new nanogui::TextBox(panel);
  text_box5->setFixedSize(nanogui::Vector2i(60, 25));
  text_box5->setFontSize(20);
  text_box5->setValue("3");

  // This is the lambda function called while the user is moving the slider
  slider5->setCallback(
    [text_box5](float value) {
      text_box5->setValue(std::to_string(static_cast<int>(value*5)));
    });
  // This is the lambda function called once the user is no longer manipulating
  // the slider.
  slider5->setFinalCallback(
    [&](float value) {
      food_count_ = static_cast<int>(value*5);
      std::cout << "Final slider value: " << value;
      std::cout << " food " << food_count_ << std::endl;
    });

  // Lays out all the components with "15" units of inbetween spacing
  panel->setLayout(new nanogui::BoxLayout(
    nanogui::Orientation::Vertical, nanogui::Alignment::Middle, 0, 15));

  // ^^^^^^^^    ADDED TO HERE (modification of nanogui example1.cc)  ^^^^^^^^

  screen()->setSize({X_DIM + 270, Y_DIM});
  screen()->performLayout();
} /* GraphicsArenaViewer() */

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (!paused_ &&
    arena_->get_game_status() == PLAYING) {
    controller_->AdvanceTime(dt);
  }
} /* UpdateSimulation() */

void GraphicsArenaViewer::Initialize() {
  controller_->AcceptCommunication(kLightSensitivity);
  controller_->AcceptCommunication(kRobots);
  controller_->AcceptCommunication(kLights);
  if (food_) {
    controller_->AcceptCommunication(kFoodOn);
  } else {
    controller_->AcceptCommunication(kFoodOff);
  }
  initialized_ = true;
} /* Initialize() */

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnPlayingBtnPressed() {
  if (!paused_) {
    controller_->AcceptCommunication(kPause);
    paused_ = true;
    playing_button_->setCaption("Play");
  } else {
    if (!initialized_) {
      Initialize();
    }
    controller_->AcceptCommunication(kPlay);
    paused_ = false;
    playing_button_->setCaption("Pause");
  }
} /* OnPlayingBtnPressed() */

void GraphicsArenaViewer::OnNewGameBtnPressed() {
  controller_->AcceptCommunication(kNewGame);
  initialized_ = false;
  paused_ = true;
  playing_button_->setCaption("Play");
} /* OnNewGameBtnPressed() */

void GraphicsArenaViewer::OnFoodBtnPressed() {
  if (food_) {
    controller_->AcceptCommunication(kFoodOff);
    food_button_->setCaption("Food (OFF)");
    food_ = false;
  } else {
    controller_->AcceptCommunication(kFoodOn);
    food_button_->setCaption("Food (ON)");
    food_ = true;
  }
} /* OnFoodBtnPressed() */

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
