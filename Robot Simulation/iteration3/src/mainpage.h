/**
 *  @file mainpage.h
 *
 *  @copyright 2018 Nate Samuelson, All rights reserved.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/*! \mainpage Robot Simulation in Arena Environment
 *
 * \section intro_sec User Guide
 *
 * \htmlonly <style>div.image img[src="Arena.png"]{width:1000px;}</style> \endhtmlonly
 * \image html Arena.png "Arena Simulation Screenshot"
 *
 * \subsection introduction Introduction
 *
 * This project represents a simple user-configured Robot simulation in which
 * Robot entities react to two other types of entities using specialized sensors,
 * Light and Food.
 * The user can specify the quantity of each entity as well as various
 * other parameters to effect the simulation. Robots exhibit three different
 * types of behavior: Fear, Exploratory, and Aggresive (when hungry).
 * The Fear and Exploratory behaviors are reactions to lights and can be
 * configured by the user, however the Aggressive behavior is only exhibited
 * when the Robot experiences hunger. Robot behavior is calculated by the
 * connection of a Robot's left and right Sensors (Light/Food) and the
 * velocities of its left and right wheels.
 * After 30 second without a Robot coming into contact with a Food entity,
 * it will begin to act increasingly aggressive. After a total of two minutes,
 * the Robot will ignore lights altogether in favor of Food.
 * If a Robot has not come into contact with Food after a total of two
 * minutes and 30 seconds, the Robot will starve and the simulation will end
 * with the game being paused.
 * At this point, the user must click New Game to reset the Arena. Upon a new
 * game, the user is allowed to once again Configure the Arena which will take
 * effect after clicking the Play button. A user can also begin a new game
 * whenever they please by clicking the New Game button. If any Robot comes
 * into contact with another Robot, a wall, or a Food entity it will reverse
 * in an arc momentarily before continuing as usual. The same behavior is
 * exhibited by lights except that a Light will only collide with walls because
 * they hover above the Arena and other entities. The simulation will continue
 * indefinitely so long as none of the Robots have starved.
 *
 * \subsection non_technical General User
 *
 * <B>Play/Pause Button</B>
 *
 * As mentioned previously, a user can pause the simulation at their
 * convenience by clicking the Pause button. When the simulation begins,
 * it will default to being paused and the user is required to click the Play
 * button upon which the Arena Configurations will take effect.
 *
 * <B>New Game Button</B>
 *
 * The New Game button will reset the Arena by removing all entities and
 * pausing the simulation. At this point a user can adjust the Arena
 * configurations and click the Play button for the configurations to take
 * effect as the simulation begins.
 *
 * <B>Robot Quantity Slider</B>
 *
 * This slider is somewhat self-explanatory and allows the user to configure
 * the number of Robots in a range of 0-10. With a selection of 0, the
 * simulation will continue indefinitely.
 *
 * <B>Robot Ratio Slider (Fear vs Exploratory)</B>
 *
 * The Robot ratio controls the number of Robots that exhibit Fear behavior
 * versus the number of Robots that exhibit Exploratory behavior (explanations
 * follow). The ratio is, of course, relative to the number of Robots
 * configured by the user.
 *
 * <B>Fear Behavior</B>
 *
 * A Robot exhibiting Fear behavior will actively avoid lights by steering
 * the other direction. This is accomplished by connecting the left LightSensor
 * to the left wheel's velocity and the right LightSensor to the right wheel's
 * velocity. For example, a Robot will accelerate away from a Light on its
 * left because the left Sensor reading is greater than the right Sensor reading
 * so the Robot naturally turns to the right away from the Light. The only
 * situation in which a Robot will not avoid a Light is if it senses the Light
 * as it is directly in front of the Robot because the left and right Sensor
 * readings will be equal, thus accelerating straight towards the Light.
 *
 * <B>Exploratory Behavior</B>
 *
 * A Robot exhibiting Exploratory behavior will "explore" whichever Light
 * is closest to the Robot. This is accomplished by connecting the left LightSensor
 * reading to the right wheel's velocity with an inverted connection and the
 * right LightSensor reading to the left wheel's velocity with an inverted connection.
 * For example, if a Light is on the left side of a Robot, the the left Sensor's
 * reading will be greater than the right Sensor's reading as stated before.
 * However, because the left Sensor is connected to the right wheel's velocity,
 * it will increase it's right wheel's velocity until the left and right
 * Sensors reach and equilibrium and the Robot accelerates directly backwards
 * toward the Light. The backwards acceleration results from the inverted connections
 * which gives a negative velocity to the left and right wheel velocities.
 *
 * <B>Aggressive Behavior</B>
 *
 * This behavior is simply the Exploratory behavior backwards. Rather than an
 * inverted connection between sensors and wheel velocities, the Robot has
 * a direct connection between the left LightSensor and the right wheel's velocity
 * as well as the right LightSensor and the left wheel's velocity. Thus,
 * the Robot demonstrates the Exploratory behavior while accelerating directly
 * towards a Light rather than backwards towards it.
 *
 * <B>Light Quantity Slider</B>
 *
 * The Light Quantity slider allows the user to configure the number of lights
 * in the Arena within a range of 0-5.
 *
 * <B>Light Sensitivity Slider</B>
 *
 * The Light Sensitivity slider allows the user to configure the Sensitivity
 * of all Robot's Light sensors in a range from 0-100%. At 0%, the Robots will
 * ignore lights completely. At 100% Light sensitivity the Robots will react
 * to lights if they are within a distance of roughly one third of the length
 * of the Arena.
 *
 * <B>Food Quantity Slider</B>
 *
 * The Food Quantity slider allows the user to configure the number of food
 * entities in the Arena within a range of 0-5.
 *
 * <B>Food Button (ON/OFF)</B>
 *
 * The Food Button allows the user to toggle on or off the presence of Food.
 * This is the only Arena configuration that takes effect without the need
 * to start a new game. While it will default to ON, the user can turn off
 * Food at any point by clicking the Food (ON) button which will then switch
 * to Food (OFF). Upon Food being turned off, all Food entities will disappear
 * and Robots will not experience hunger. Thus, the simulation will continue
 * indefinitely without starvation of Robots. When Food is turned back on, the
 * Food entities will appear randomly placed in the Arena and Robots will begin
 * to experience hunger once again (with a reset hunger countdown).
 *
 * \subsection technical Technical User
 *
 * <B>Flow of Control</B>
 *
 * For the technical user, a more detailed explantion follows.
 *
 * The structure of the simulation begins with the main.cc file which instantiates
 * a Controller and executes its Run() method. This class instantiates
 * an Arena and GraphicsArenaViewer upon construction and calls the GraphicsArenaViewer's
 * Run method which begins the simulation. The Arena is left empty until the
 * user clicks Play where the GraphicsArenaViewer calls the appropriate methods
 * through the controller to initialize the Arena with the given parameters.
 * The controller calls the Arena's methods for each entity with the appropriate
 * quantity (set by the user) which in turn calls the EntityFactory's methods
 * for instantiation of each entity. Entities are then stored in various respective
 * vectors within the Arena class. The Robot Ratio is used in the controller
 * to instantiate the proper quantity of each Robot Type in the Arena.
 * The Light Sensitivity is passed with the Robot Type to each parameter
 * which sets each Robot's member variable for Light Sensitivity.
 * Each robot has a left and right Sensor for both Food and Lights.
 * These sensors connect with the wheel velocities via a method within
 * the Robot's MotionHandlerRobot called UpdateVelocity. UpdateVelocity is
 * effectively where the behavior of a Robot is determined. A switch statement
 * within this method calculates the appropriate velocity given the Robot type.
 *
 * Due to poor time management, this is where the technical user guide will reach
 * its conclusion. Thank you for your time. Have a great summer!
 *
 */

#endif  // SRC_MAINPAGE_H_
