/**
 * @file robot_type.h
 *
 * @copyright 2018 Nate Samuelson, all rights reserved.
 */

#ifndef SRC_ROBOT_TYPE_H_
#define SRC_ROBOT_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

enum RobotType {
  kCoward, kAggressive, kLove, kExplore
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_TYPE_H_
