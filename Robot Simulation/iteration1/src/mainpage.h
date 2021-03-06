/**
 *  @file mainpage.h
 *
 *  @copyright 2018 Nate Samuelson, All rights reserved.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/*! \mainpage Robot Simulation in Arena Environment
 *
 * \section intro_sec Project Summary
 *
 * This project implements a simple game where the user controls a robot
 * in attempting to evade obstacles while capturing all bases to win. All
 * gameplay occurs in the Arena class. This is where time is advanced and
 * all entity interaction is handled. Graphics simulation is generated from
 * the GraphicsArenaViewer class which passes user inputs through the
 * controller to the Arena. All entities are instantiated by the EntityFactory
 * class which sets each entity to its default parameters. These default
 * parameters vary by class but consist predominantly of a Pose
 * (position & heading angle) and radius. Entities exist as subclasses of
 * the ArenaEntity class. The entities consist of the ArenaMobileEntity
 * subclass and ArenaImmobileEntity subclass. At this point in the project,
 * the mobile entities consist of the robot and obstacles. The only
 * immobile entities are the bases of the base class. For the mobile entities,
 * motion is controlled by a MotionHandler class. Both robots and obstacles have
 * their own motion handler subclasses, MotionHandlerRobot and
 * MotionHandlerObstacle respectively. This is where velocity and heading angle
 * of entities are calculated. Upon interaction between entities, for example
 * an obstacle and wall, the Arena class will adjust the entity overlap in
 * order to ensure entities cannot escape the map or overlap each other
 * (there is a known bug which causes entities to “jump” over each other
 * at times). If the entity interacting with the environment is a robot,
 * then the robots HandleCollision method will be called which will decrement
 * the robots lives by one unless the second entity is a base in which the
 * base will be updated to captured (and change color to green) and the
 * robots number of bases captured will be incremented by one. The handle
 * collision method of the robot passes further information to the
 * ArenaMobileEntity subclass of SensorTouch which is used to calculate
 * the point of contact between entities. This is used to adjust the overlap
 * between entities. If the robot does lose a life then it is given a mercy
 * invincibility time of two seconds where further lives cannot be lost and
 * the robot’s color will flash. All of this interaction is handled in the
 * arena in the UpdateEntitiesTimestep method. When the user opens the
 * application the simulation will be paused, the user must select the
 * “Play” button in order for the arena to begin updating entities. The
 * user can pause the game at any time with the “Pause” button and
 * continue play, again with the “Play” button. Upon the robot’s lives
 * reaching zero or all bases being captured the robot’s color will change
 * and the game will halt further updates. The user will be allowed to select
 * the New Game which resets all entities by calling their reset method which
 * places them randomly in the arena (except robot which returns to its
 * origin). This also resets robots lives and captured bases. Any base
 * will be set back to uncaptured. 
 *
 */

#endif  // SRC_MAINPAGE_H_
