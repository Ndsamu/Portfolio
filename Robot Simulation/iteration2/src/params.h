/**
 * @file params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PARAMS_H_
#define SRC_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Macros
 ******************************************************************************/
/*
 * @file. Constructors for classes should use reasonable default values as
 * defined here. An exception might be if the value is 0.
 */

// graphics
#define X_DIM 1024
#define Y_DIM 768
#define TEXT_BOX_WIDTH 50
#define GUI_MENU_WIDTH 180
#define GUI_MENU_GAP 10

// arena
#define N_LIGHTS 6
#define TOTAL_LIGHTS 8
#define ARENA_X_DIM X_DIM
#define ARENA_Y_DIM Y_DIM

// game status
#define WON 1
#define LOST 0
#define PLAYING 2
#define PAUSED 3

// entity
#define DEFAULT_POSE \
  { 200, 200, 0}
#define DEFAULT_COLOR \
  { 255, 255, 255 }
#define DEFAULT_RADIUS 20

// mobile entity
#define STARTING_VELOCITY 0.0
#define ACTIVE_SPEED 5
#define AVOIDANCE_SPEED -5

// robot
#define ROBOT_ANGLE_DELTA 1
#define ROBOT_SPEED_DELTA 1
#define ROBOT_COLLISION_DELTA 1
#define ROBOT_RADIUS (random()%6)+8
#define ROBOT_INIT_POS \
  { 500, 500 , 0}
#define ROBOT_COLOR \
  { 0, 0, 255 }
#define ROBOT_COLOR_WON \
  { 0, 255, 0 }
#define ROBOT_COLOR_LOST \
  { 255, 0, 0 }

#define ROBOT_HEADING 270
#define ROBOT_INIT_SPEED 5
#define ROBOT_MAX_SPEED 10
#define ROBOT_MIN_SPEED 0
#define ROBOT_MAX_ANGLE 360
#define ROBOT_LIVES 9

// food
#define N_FOODS 3
#define FOOD_RADIUS 20
#define FOOD_COLLISION_DELTA 1
#define FOOD_INIT_POS \
  { 400, 400 }
#define FOOD_COLOR \
  { 0, 255, 0 }

// light
#define LIGHT_INIT_POS \
  { 200, 200, 0 }
#define LIGHT_RADIUS 15
#define LIGHT_MIN_RADIUS 10
#define LIGHT_MAX_RADIUS 50
#define LIGHT_COLOR \
  { 255, 255, 255 }

#define LIGHT_HEADING (random()%360)

#endif  // SRC_PARAMS_H_
