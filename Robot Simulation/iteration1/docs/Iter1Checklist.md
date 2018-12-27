### CSCI3081W: Iteration 1 Submission Checklist

> The iteration 1 code and documentation is due on TUESDAY, Mar 06 at 11:55pm

Please copy this file into your /docs folder. Place an 'x' in each of the `[ ]` boxes for items that are complete. Push this completed checklist to github. When it displays on Github, it will show an actual checkbox with a check mark.

### Compilation and Execution

- [X] I cloned **fresh** from github onto a cselabs machine to test compilation
- [X] Submission is on the master branch of the my project repo "project-<username>"
- [X] _/iteration1_ folder exists
- [X] _/build_ is not in the repo
- [X] _/html_ is not in _docs_
- [X] **__`make` from src completes without error.__**
- [X] `doxygen docs/Doxyfile` compiles
- [X] `cpplint.py *.cc` reports no errors
- [X] `cpplint.py --root=.. *.h` reports no errors
- [X] `./../build/bin/arenaviewer` executes without assert or a seg fault

### Primary Functionality

> To make grading easier, we ask that you provide the status of each of the requirements. Do not lie about the status!! It makes us grumpy -- you want your grader to be happy when s/he grades! We will be inspecting the code to confirm,
but this status report can make it faster for us.

**__Please place an 'X' in the appropriate box for each requirement.__**
- Good = Fully Implemented. No _known_ bugs. No _obvious_ bugs.
- Okay = Works but some bugs (recorded in bug report).
- Help = Attempted but not working.
- Time = No to Little Progress

| Functionality | Good | Okay | Help | Time |
| -------- | -------- | -------- | -------- | --------- |
| **__Priority Level 1__** |
| _Enitities_ are generated and placed according to the requirements | X |  |  |  |
| _Robot_ adjusts wheel velocities when pressing the arrow keys | X |  |  |  |
| _Robot_ stops when colliding with an object | X |  |  |  |
| _Robot_ loses a life when colliding with an obstacle or wall | X |  |  |  |
| _Base_ changes color when captured by _Robot_ | X |  |  |  |
| Game is won if robot captures all bases | X |  |  |  |
| Game is lost if the robot loses all its lives | X |  |  |  |
| Obvious visual indication of winning or losing game | X |  |  |  |
| Game stops and waits for the user upon a win or loss | X |  |  |   |
| **__Priority Level 2__** |
| _Obstacles_ are mobile with two same-speed wheels and moves straight | X |  |  |   |
| _Obstacles_ move in a reverse arc for a fixed time after collision | X |  |  |   |
| All entities are stationary before the "Play" button is pushed | X |  |  |   |
| Pressing the button changes button state from "Play" to "Pause" | X |  |  |   |
| Pressing the button changes the game state from playing to paused (or back) |  X|  |  |  |
| "New Game" button is available to user | X |  |  |  |
| Pressing "New Game" begins a new game | X |  |  |  |
| Number of lives remaining is depicted within the body of the robot | X |  |  |   |
| **__Priority Level 3__** |
| Even more obstacles | X |  |  |   |
| Mercy invincibility is implemented | X |  |  |   |
| For Fun |
| King of the Hill is implemented |  |  |  | X |

### Documentation
> Documentation should be in good _draft_ form.

- [X] _UML_ file for the iteration 1 exists in _docs_
- [X] The _UML_ reflects the current state of the code
- [X] _mainpage.h_ exists in _src_
- [X] Front page (mainpage) has a project description for programmer audience (1 to 2 pages)
- [X] I inspected index.html in _docs/html_ folder
- [X] Classes are documented in the doxygen web page class list
- [X] _Classes_ list has documentation for each class, including members and methods
- [X] I perused other classes to spot check documentation
- [X] I commented my code where necessary

### Unit Tests, Linter, and Git
- [X] The code passes all the unit tests WITHOUT modification to the provided tests.
- [X] The code complies with naming conventions for classes, methods, and members.
- [X] There exists a history of git commit messages to show effort.

### BugReport
- [X] BugReport.md is in the /docs folder.
- [X] The report includes a list of known bugs (or states "no known bugs") for each file.
  > If you report _minor_ bugs, you will lose few to no points for that functionality.
  > If you try to hide some obvious bugs and not report them, you will lose all the points for that functionality.

## Ready For Submission

When everything above is as you want it or it is 11:55pm on Tuesday, it is time to submit!

- [X] I pushed this file and any changes resulting from this checklist.

_One more thing -- check that what you think you pushed was really pushed to github. If you can see it, we can see it. If you can't, we can't._

Congratulations on your submission!
