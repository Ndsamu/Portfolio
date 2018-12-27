/**
 * @file food.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_FOOD_H_
#define SRC_FOOD_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include <iostream>

#include "src/arena_immobile_entity.h"
#include "src/common.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing an immobile food object within the Arena.
 *
 * Food restores the hunger of a robot if it comes within 5 pixels
 * of the food object.
*/
class Food : public ArenaImmobileEntity {
 public:
  /**
   * @brief Constructor.
   *
   * @param params A base_params passed down from main.cc for the
   * initialization of the Food.
   */
  Food();

  /**
   * @brief Food's destructor. `delete` all entities created.
   */
  virtual ~Food();

  /**
   * @brief Reset the Food using the initialization parameters received
   * by the constructor.
   */
  void Reset() override;

  /**
   * @brief Get the name of the Food for visualization purposes, and to
   * aid in debugging.
   *
   * @return Name of the Food.
   */
  std::string get_name() const override { return "Food"; }
};

NAMESPACE_END(csci3081);

#endif  // SRC_FOOD_H_
