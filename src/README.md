# src : Source Code Directory #
This directory contains all the code directories and directly contains
some of the high-level code itself.

## Engine & Main Loop ##
The main function exists only to create and start the main loop which is
implemented in the `Engine` class. Its construction, `runLoop` and
deconstruction create the set up, main loop and clean up of the entire
program. Furthermore we can break up the main loop like this:

1.  Poll Input
2.  Update
3.  Render
4.  Wait

The `Engine`'s runLoop controls the timing of these steps, the handling of
them is mostly handed off to the current `WorldState` which is used as a
state-machine within the `Engine`.

Poll Input step grabs all the inputs recived since the last iteration of the
loop. The runLoop function translates them to internal events and handles
the high level events before handing the rest of the events over to the
WorldState.

Update increments the worlds state by a given amount of time. This is
entirely handed over to the WorldState, although the time passed is figured
out but the Engine.

Render updates the image on screen. The original clear and final buffer update
is handled by the Engine, the drawing of the new image is handled by the
WorldState.

Wait just waits for the next frame. `LoopClock` handles that.

## GameObject ##
The `GameObject` class is used as a base to implement many classes that
repersent things in the game world.

The GameObject's design is in flux. Currently a container system is used. The
class itself never changes but its component parts can be swapped out to
change its behaviour.

The GameObject goes into the `Plane` which is used to search through them for
collisions, with each other and with a mouse click.
