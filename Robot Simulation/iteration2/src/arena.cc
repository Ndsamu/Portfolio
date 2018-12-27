/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <iostream>

#include "src/arena.h"
#include "src/arena_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Arena::Arena(const struct arena_params *const params)
    : x_dim_(params->x_dim),
      y_dim_(params->y_dim),
      factory_(new EntityFactory),
      entities_(),
      mobile_entities_(),
      robot_entities_(),
      light_entities_(),
      food_entities_(),
      game_status_(PAUSED) {
  AddRobot(5, kCoward);
  AddRobot(5, kExplore);
  AddFood(4);
  AddLight(4);
} /* Arena() */

Arena::~Arena() {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
} /* ~Arena() */

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Arena::AddRobot(int quantity, RobotType rtype) {
  for (int i = 0; i < quantity; i++) {
    robot_ = dynamic_cast<Robot *>(factory_->CreateEntity(kRobot));
    robot_->set_robot_type(rtype);
    entities_.push_back(robot_);
    mobile_entities_.push_back(robot_);
    robot_entities_.push_back(robot_);
  }
} /* AddRobot() */

void Arena::AddLight(int quantity) {
  for (int i = 0; i < quantity; i++) {
    light_ = dynamic_cast<Light *>(factory_->CreateEntity(kLight));
    entities_.push_back(light_);
    mobile_entities_.push_back(light_);
    light_entities_.push_back(light_);
  }
} /* AddLight() */

void Arena::AddFood(int quantity) {
  for (int i = 0; i < quantity; i++) {
    food_ = dynamic_cast<Food *>(factory_->CreateEntity(kFood));
    entities_.push_back(food_);
    food_entities_.push_back(food_);
  }
} /* AddFood() */

void Arena::AddEntity(EntityType type, int quantity) {
  for (int i = 0; i < quantity; i++) {
    entities_.push_back(factory_->CreateEntity(type));
  }
} /* AddEntity() */

void Arena::Reset() {
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
  game_status_ = 2;
} /* Reset() */

// The primary driver of simulation movement. Called from the Controller
// but originated from the graphics viewer.
void Arena::AdvanceTime(double dt) {
  if (!(dt > 0) && game_status_ != 2) {
    return;
  }
  for (size_t i = 0; i < 1; ++i) {
    UpdateEntitiesTimestep();
  } /* for(i..) */
} /* AdvanceTime() */

void Arena::UpdateEntitiesTimestep() {
  /**
   * First, check if any robot has starved.
  **/
  for (auto robot : robot_entities_) {
    robot_ = dynamic_cast<Robot *>(robot);
    if (robot_->CheckStarvation() == true) {
     game_status_ = LOST;
     robot_->set_color(ROBOT_COLOR_LOST);
    }
  }

  /*
   * Next, update the position of all entities, according to their current
   * velocities.
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  }

  // Update readings for all sensors and robots actions accordingly
  for (auto robot : robot_entities_) {
    robot_ = dynamic_cast<Robot *>(robot);
    for (auto ent : light_entities_) {
      // Update robots light sensors based on reading
      robot_->NotifyLights(ent->get_pose());
    }
    for (auto ent : food_entities_) {
      // Update robots food sensors based on reading
      robot_->NotifyFood(ent->get_pose());
    }
  }

  // Determine if a robot has captured food
  for (auto &ent1 : robot_entities_) {
    for (auto &ent2 : food_entities_) {
      if (IsFoodCaptured(ent1, ent2)) {
        robot_ = dynamic_cast<Robot *>(ent1);
        robot_->ResetHunger();
      }
    }
  }

   /* Determine if any mobile entity is colliding with wall.
   * Adjust the position accordingly so it doesn't overlap.
   */
  for (auto &ent1 : mobile_entities_) {
    EntityType wall = GetCollisionWall(ent1);
    if (kUndefined != wall) {
      AdjustWallOverlap(ent1, wall);
      if (ent1->get_type() == kLight) {
        light_ = dynamic_cast<Light *>(ent1);
        light_->HandleCollision();
      } else {
        robot_ = dynamic_cast<Robot *>(ent1);
        robot_->HandleCollision();
      }
    }

    /* Determine if that mobile entity is colliding with any other entity.
    * Adjust the position accordingly so they don't overlap.
    */
    for (auto &ent2 : entities_) {
      if (ent2 == ent1) { continue; }
      if (IsColliding(ent1, ent2)) {
        if (ent1->get_type() == kRobot) {
          if (ent2->get_type() == kRobot) {
            AdjustEntityOverlap(ent1, ent2);
            robot_ = dynamic_cast<Robot *>(ent1);
            robot_->HandleCollision();
            robot_ = dynamic_cast<Robot *>(ent2);
            robot_->HandleCollision();
          }
        }
      }
    }
  }
} /* UpdateEntitiesTimestep() */


// Determine if the entity is colliding with a wall.
// Always returns an entity type. If not collision, returns kUndefined.
EntityType Arena::GetCollisionWall(ArenaMobileEntity *const ent) {
  if (ent->get_pose().x + ent->get_radius() >= x_dim_) {
    return kRightWall;  // at x = x_dim_
  } else if (ent->get_pose().x - ent->get_radius() <= 0) {
    return kLeftWall;  // at x = 0
  } else if (ent->get_pose().y + ent->get_radius() >= y_dim_) {
    return kBottomWall;  // at y = y_dim
  } else if (ent->get_pose().y - ent->get_radius() <= 0) {
    return kTopWall;  // at y = 0
  } else {
    return kUndefined;
  }
} /* GetCollisionWall() */

/* The entity type indicates which wall the entity is colliding with.
* This determines which way to move the entity to set it slightly off the wall. */
void Arena::AdjustWallOverlap(ArenaMobileEntity *const ent, EntityType object) {
  Pose entity_pos = ent->get_pose();
  switch (object) {
    case (kRightWall):  // at x = x_dim_
    ent->set_position(x_dim_-(ent->get_radius()+5), entity_pos.y);
    break;
    case (kLeftWall):  // at x = 0
    ent->set_position(ent->get_radius()+5, entity_pos.y);
    break;
    case (kTopWall):  // at y = 0
    ent->set_position(entity_pos.x, ent->get_radius()+5);
    break;
    case (kBottomWall):  // at y = y_dim_
    ent->set_position(entity_pos.x, y_dim_-(ent->get_radius()+5));
    break;
    default:
    {}
  }
} /* AdjustWallOverlap() */

/* Calculates the distance between the center points to determine overlap. */
bool Arena::IsColliding(
  ArenaMobileEntity * const mobile_e,
  ArenaEntity * const other_e) {
    double delta_x = other_e->get_pose().x - mobile_e->get_pose().x;
    double delta_y = other_e->get_pose().y - mobile_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    return
    (distance_between <= (mobile_e->get_radius() + other_e->get_radius()));
} /* IsColliding() */

/* Calculates the distance between the a robot and food + 5 pixels. */
bool Arena::IsFoodCaptured(
  ArenaMobileEntity * const mobile_e,
  ArenaEntity * const other_e) {
    double delta_x = other_e->get_pose().x - mobile_e->get_pose().x;
    double delta_y = other_e->get_pose().y - mobile_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    return
    (distance_between <= (mobile_e->get_radius() + other_e->get_radius() + 5));
} /* IsFoodCaptured() */

/* This is called when it is known that the two entities overlap.
* We determine by how much they overlap then move the mobile entity to
* the edge of the other
*/
void Arena::AdjustEntityOverlap(ArenaMobileEntity * const mobile_e,
  ArenaEntity *const other_e) {
    double delta_x = mobile_e->get_pose().x - other_e->get_pose().x;
    double delta_y = mobile_e->get_pose().y - other_e->get_pose().y;
    double distance_between = sqrt(delta_x*delta_x + delta_y*delta_y);
    double distance_to_move =
      mobile_e->get_radius() + other_e->get_radius() - distance_between + 5;
    double angle = atan2(delta_y, delta_x);
    mobile_e->set_position(
      mobile_e->get_pose().x+cos(angle)*distance_to_move,
      mobile_e->get_pose().y+sin(angle)*distance_to_move);
} /* AdjustEntityOverlap() */

// Accept communication from the controller. Dispatching as appropriate.
void Arena::AcceptCommand(Communication com) {
  switch (com) {
    case(kIncreaseSpeed):
      break;
    case(kDecreaseSpeed):
      break;
    case(kTurnLeft):
      break;
    case(kTurnRight):
      break;
    case(kPlay):
      set_game_status(PLAYING);
      break;
    case(kPause):
      set_game_status(PAUSED);
      break;
    case(kReset):
      Reset();
    case(kNone):
    default: break;
  }
} /* AcceptCommand */

NAMESPACE_END(csci3081);
