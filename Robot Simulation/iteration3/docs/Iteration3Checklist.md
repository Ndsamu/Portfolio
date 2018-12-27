### CSCI3081W: Iteration 3 Submission Checklist

> The iteration 3 code and documentation is due on THURSDAY, May 3 at 11:55pm

**__Please copy this file into your /docs folder in iteration3__**. Place an 'x' in each of the `[ ]` boxes for items that are complete. Push this completed checklist to github. When it displays on Github, it will show an actual checkbox with a check mark.

### Compilation and Execution

- [X] I cloned **fresh** from github onto a cselabs machine to test compilation
- [X] Submission is on the master branch of the my project repo "project-<username>"
- [X] _/iteration3_ folder exists
- [X] _/build_ is not in the repo
- [X] _/html_ is not in _docs_
- [X] **__`make` from src completes without error.__**
- [X] `./../build/bin/arenaviewer` executes without assert or a seg fault
- [X] `cpplint.py *.cc` reports no errors
- [X] `cpplint.py --root=.. *.h` reports no errors
- [X] `doxygen docs/Doxyfile` compiles

### Primary Functionality

> To make grading easier, we ask that you provide the status of each of the requirements. Do not lie about the status!! It makes us grumpy -- you want your grader to be happy when s/he grades! We will be inspecting the code to confirm,
but this status report can make it faster for us.

**__Please place an 'X' in the appropriate box for each requirement.__**
- Good = Fully Implemented. No _known_ bugs. No _obvious_ bugs.
- Okay = Works but some bugs (recorded as a bug/issue on github).
- Help = Attempted but not working.
- Time = No to Little Progress

| Functionality | Good | Okay | Help | Time |
| -------- | -------- | -------- | -------- | --------- |
| **__GUI__** |
| User can configure # of robots. | X |  |  |  |
| User can configure # of lights. | X |  |  |  |
| User can choose to not include food. | X |  |  |  |
| User can configure # of food. | X |  |  |  |
| User can pause simulation. | X |  |  |  |
| User can create new simulation (new game). | X |  |  |  |
| **__TESTS__** |
| Tests for light sensor functionality exist. | X |  |  |  |
| Tests for light sensor compile. | X |  |  |  |
| Tests for light sensor pass. | X |  |  |  |
| Tests for wheel velocity functionality exist. | X |  |  |  |
| Tests for wheel velocity compile. | X |  |  |  |
| Tests for wheel velocity pass. | X |  |  |  | |

<hr>

For the table below, please identify which aspects were fixed. You should put an "x" in one of the three columns. We will restore points only for those elements that are complete and correct.

### THIS IS ESSENTIAL FOR RESTORING POINTS FOR FUNCTIONALITY.
*You can potentially get back 50% of the lost functionality points from iteration 2, but we have to know what to look for. We will not spend time tracking down what didn't work in iteration 2 and trying to see if it is working in iteration 3. We need you to tell us what to look for. We will be comparing this to your iteration 2 checklist to confirm.*


| Functionality | Complete in it2 | | Fixed in it3 | Still Buggy |
| -------- | -------- |-| -------- | -------- |
| **__Priority Level 2__** |
| _Lights_ are visually distinct and moving. | X ||  |   |
| _Lights_ have avoidance behavior when colliding with a wall. | X ||  |   |
| _Lights_ have avoidance behavior when colliding with a light. | X ||  |   |
| _Lights_ pass through non-light entities. | X ||  |   |
| _Robots_ are visually distinct and moving (when appropriate<sup> [1] </sup>). | X ||  |   |
| Robot sensors are displaying properly. | X ||  |   |
| _Robots_ have avoidance behavior when colliding with a wall. | X ||  |   |
| _Robots_ have avoidance behavior when colliding with a robot. | X ||  |   |
| _Robots_ pass through non-robot entities. | X ||  |   |
| Half the robots fear lights. | X ||  |   |
| Half the robots "explore" for lights. | X ||  |   |
| User can toggle between pausing and playing. | X ||  |   |
| User can start a new game/simulation. | X ||  |   | |

[1] Robot behavior emerges from the sensor-actuator connections. It might not always reflect reasonable behavior with respect to the intended reaction. For example, a fearful robot might not always run away from a light due to various forces acting upon it. We are not grading the robot behavior that emerges -- only the implementation of the sensor reading calculation, of the sensor-actuator connections, and of the calculated wheel velocity as a function of sensor readings.

**__The list below is relevant when the user chooses to include Food in simulation.__**

| Functionality | Complete in it2 || Fixed in it3 | Still Buggy |
| -------- | -------- |-| -------- | -------- |
| **__Priority Level 3__** |
| _Food_ is visually distinct and immobile. | X ||  |   |
| _Robots_ are aggressive towards food. | X ||  |   |
| _Robots_ get hungry after ~30 seconds after eating. | X ||  |   |
| _Robots_ consume food when ~5 units away. | X ||  |   |
| _Robots_ are no longer hungry after eating. | X ||  |   |
| **__Priority Level 4__** |
| After not eating for ~2 mins, _Robots_ ignore lights. | X ||  |   |
| After not eating for ~2.5m mins, _Robots_ starve death. Game over. | X ||  |   |
| Simulation starts with 10 robots, 4 lights, 4 food. | X ||  |   | |


### Documentation

- [X] The UML document &lt;username&gt;_UML.pdf file for the iteration 3 exists in _docs_.
- [X] The UML document reflects the requirements of iteration 3.
- [X] _mainpage.h_ or _mainpage.md_ is in the /src folder.
- [X] I have compiled doxygen and looked at the generated mainpage.
- [X] The mainpage includes a user guide for technical users.
- [X] The mainpage includes a user guide for non-technical users.
- [X] I commented my code where necessary.

### Linter and Git
- [X] The code complies with naming conventions for classes, methods, and members.
- [X] There exists a history of git commit messages to show effort.
- [X] There exists a history of issues and branches to show effort.

### Reporting of Bugs
- [X] Viewing issues on my repo and selecting _bug_ label shows all the known bugs in my code.
- [X] All resolved issues have been _closed_ (including bugs).


## Ready For Submission

When everything above is as you want it or it is 11:55pm on Tuesday, it is time to submit!

- [X] I pushed this file and any changes resulting from this checklist.
- [X] Everything is in the **__master__** branch.

_One more thing -- check that what you think you pushed was really pushed to github on the master branch. If you can see it, we can see it. If you can't, we can't._

Congratulations on your submission!
