/**
 * @file base.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/base.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Base::Base() : ArenaImmobileEntity(), captured_(false) {
  set_type(kBase);
  set_color(BASE_COLOR);
  set_pose(BASE_INIT_POS);
  set_radius(BASE_RADIUS);
}
Base::~Base() {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void Base::Reset() {
  set_pose(set_pose_randomly());
  set_color(BASE_COLOR);
  set_captured(false);
}

bool Base::IsCaptured() const {
  return captured_;
}

void Base::set_captured(bool state) {
  captured_ = state;
}

NAMESPACE_END(csci3081);
