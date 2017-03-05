# src : Source Code Directory #
This directory contains all the code directories and directly contains
some of the high-level code itself.

## Main Loop ##
The main function exists only to create and start the main loop which is
implemented in the `Engine` class. Its construction, `runLoop` and
deconstruction create the set up, main loop and clean up of the entire
program. Furthermore we can break up the main loop like this:

1.  Poll Input
2.  Update
3.  Render
4.  Wait

The standard game loop. The work is divided between the Engine itself and
the `WorldState` class. The Engine is a state machine for the WorldState
which implements the situational code in the loop. Most of the actual game
logic.

## GameObject ##
The `GameObject` class is used as a base to implement many classes that
repersent things in the game world.

The GameObject's design is in flux. Currently a container system is used. The
class itself never changes but its component parts can be swapped out to
change its behaviour.

The GameObject goes into the `Plane` which is used to search through them for
collisions, with each other and an outside entity, such as the mouse.
