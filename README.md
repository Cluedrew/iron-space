# iron-space #
An outer space base building game. Created as a learning project.

#### Project Status ####
Clean-Up: Having completed the base of the engine itself I have already
discovered cracks in my old design. Those need to be addressed as well as
updating the plan (which is seriously out of date before addressing the
cracks) and cutting down on the number of outstanding TODO statements.

## Game ##
The game is a simple game. You find yourself in the depths of space and you
have to mine iron (you could also call it ore) to build more ships and mining
stations.

## Acknowledgments ##
Or, parts of this project I didn't do:

+   [SFML](http://www.sfml-dev.org/index.php "SFML Website"), input and
    output library. On more than just text.
+   [Catch](https://github.com/philsquared/Catch "Catch GitHub"), testing
    library. (v1.5.4: retrived 2016/05/18 15:25)
+   [bfxr](http://www.bfxr.net/ "bfxr.net"), website used to generate sound
    effects for the game.
+   [incompetech](https://incompetech.com/music/royalty-free/music.html
    "incompetech music"), source of the background music.

## Code ##
Some stuff you might want to look at before diving into the code base.

I have tried to keep an updated overview of the code around, however I am
changing my plans so much that they tent to be vague in a effort not to be
wrong. Most comments in the source files should be up to date.

### Directories ###
First a bit about the layout of the code base.
+   *src* is the top level code directory and contains files that run the core
    code and tie the codebase together.
+   *plan* the other top level directory, it is for work in progress things
    that are not yet part of the project.
+   *object* contains the base GameObject types.
+   *input* contains code that handles input from the user.
+   *states* has the WorldState base class and it's subclasses that define the
    game's global state.
+   *physics* is for code that runs the physics simulation part of the game.
    Things moving over time, resolving colitions and similar.
+   *graphics* is for image loading and rendering code.
+   *audio* is for sound loading and playing code.
+   *inst* contains instances of different GameObjects used in the game.
+   *util* is for other files, those that don't have a particlar place, are
    used accross the code base but are not core.

### Testing ###

As mentioned previously testing for this project is done by *Catch.hpp*, with
all tests and extra testing code put in *.tst* files (which goes before the
file type extention).

Tags:
+   [object], [util], [input], [states], [physics], [graphics], [audio]: Tags
    that show which sub-directory the test came from.
+   [@lib], [sfml]: Tags for marking tests on external dependances. [@lib]
    refers to all of them. The others refer to a particular library. These are
    not ment to be complete, but rather to check assumptions.
+   [testing]: Tag for tests on extra code writen for testing. If these are
    not working than some other tests are invalid.
