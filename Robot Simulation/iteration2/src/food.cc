/**
 * @file foodcc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/food.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Food::Food() : ArenaImmobileEntity() {
  set_type(kFood);
  set_color(FOOD_COLOR);
  set_pose(FOOD_INIT_POS);
  set_radius(FOOD_RADIUS);
} /* Food() */
Food::~Food() {}  /* ~Food() */

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void Food::Reset() {
  set_pose(set_pose_randomly());
  set_color(FOOD_COLOR);
} /* Reset() */

NAMESPACE_END(csci3081);
