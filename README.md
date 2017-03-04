# iron-space #
An outer space base building game. Created as a learning project.

#### Project Status ####
Engine Implementation - Implement the basic code for everything and get a bit
of everything running.

+ Get some GameObjects in the gui and map Planes.
+ The GameObjects should render (a solid circles of colour is enough for now).
+ The GameObjects should be clickable.
+ Between the GameObjects, the Interface and Physics at least one GameObject
  should be orderable to move around the screen.
+ There should be collisions between GameObjects, and some noticable reaction
  to the collisions.
+ At least one sound effect and one piece of music should be played.
+ Have at least two WorldStates and the ability to transition between them.
+ Select and install a test harness, get some basic tests up.

All 8 of these points have to be completed before moving on (a few other
points may join this list). This should ensure that all parts of the engine
have some working base. It should not actually resemple a game in this stage.

I am also in the process of cleaning up and updating my "plan", as the code
has evolved out from underneath it.

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

## Plan ##
Move everything to do with the actual code into other README files or into
comments at the top of a file. Stuff that has been implemented should be
covered in *src* (in README files or comments) and actual plans for the future
should go to *plan*.

### Directories ###
First a bit about the layout of the code base.
+ *src* is the top level code directory and contains files that run the core
  code and tie the codebase together.
+ *util* is for other files, those that don't have a particlar place, are used
  accross the code base but are not core.
+ *input* contains code that handles input from the user.
+ *states* has the WorldState base class and it's subclasses that define the
  game's global state.
+ *physics* is for code that runs the physics simulation part of the game.
  Things moving over time, resolving colitions and similar.
+ *graphics* is for image loading and rendering code.
+ *audio* is for sound loading and playing code.

### Testing ###

As mentioned previously testing for this project is done by *Catch.hpp*, with
all tests and extra testing code put in *.tst* files (which goes before the
file type extention).

Tags:
+   [util], [input], [states], [physics], [graphics], [audio]: Tags that show
    which sub-directory the test came from.
+   [@lib], [sfml]: Tags for marking tests on external dependances. [@lib]
    refers to all of them. The others refer to a particular library. These are
    not ment to be complete, but rather to check assumptions.
+   [testing]: Tag for tests on extra code writen for testing. If these are
    not working than some other tests are invalid.

### Services ###
Services are systems that cut accross the code base. They generally exist to
provide a single tool to the entire code base.

##### Logging
Error messages and printing data. Unlike most other parts of the code this
isn't for the game, it's for me. To help with debugging I would like a system
built in that makes it easier to add and remove debugging messages in the
code.

The service is actually a collection of loggers. Each of which will accept
messages of different types. The loggers will have modes that say which types
of messages they print. For instance VERBOSE prints everything while QUIET
prints only error messages.

##### Graphics
The loading and desplay of images. This is based around an image library
that loads and stores images. These are mostly sprite sheets. It also includes
components that turns the textures into sprites and will display them on draw.

##### Audio
The loading and play of noises. Similar set up to the above, centered around
a sound library with little component classes.

The major difference (structurally) between this and the graphics set up is
there probably will be a bit more overhead to unify playing the sounds that
are similar. However I've never actually done audio before so this is new
territory for me, I only know some therory.

### GameObject Class ###
There is a GameObject class that implements the code for a thing in the game.
In the game means actually part of the game, things that move around in the
world as well as the gui, as apposed to the engine code that supports all
of these.

GameObjects have a set of interface functions, there is one for each step of
the main loop (minus wait), plus a few for messaging.

The GameObject is made out of a set of components. The transform is inlined
as part of the GameObject container itself, the others will be stored by
pointers so they can be swapped out (however I believe only AI will vary in
the early versions).

##### GameObject Allocation

So GameObjects interact between each other a lot. (Or they probably will.)
Which means that when they are updating is actually a bad time to delete them
as they are comunicating back and forth. To further complicate matters each
GameObject's internals will effect when it is supposed to be deleted.

A 'toDelete' predicate on each GameObject would be one way to solve the
problem. However a better solution came to mind as I tried to think of a
shorter way of putting 'GameObject Construction and Destruction'. And that
is the allocator parameters to containers. If I can wrap up the allocation
and deallocation rules in an allocator then I can put them in any class. The
GameObjects might have to have an extra field to reach back to the allocator,
or possibly not. (New territory for me here.)

##### GameObject Messaging
Now besides the regular updates there are a few ways to get information
to a GameObject out of that ordering.

There are three comunication functions on the GameObject. They all act in the
same way (allowing for pushing events to the AIComponent) but they repersent
different types of inputs.
+ `handleInput` gets called from the input polling of the main loop and is
  used to repersent user inputs. There will probably be a union/enum class to
  repersent the different type of input messages, although there shouldn't be
  many that need to be sent to the individual GameObjects.
+ `handleMessage` gets called from other GameObjects and can repersent any
  comunication between them. I think this will be repersented by a shallow
  hierarcy of classes to allow for all the possible messages that will be
  coming through.
+ `handleCollision` gets called from the collision detection system (from
  the Plane class), repersents two GameObjects overlapping and will generally
  be called in pairs. The main piece of information needed is the other object
  it collided with plus maybe a collision type {Start, Continue, Finished}.

Of these `handleMessage` is really a catch all, rooting a highway through a
pinhole. The other two are much more specialized.

##### GameObject Pointer
The GameObjectPtr is a special smart pointer that points at GameObjects. It is
smart in that it is also an observer for the GameObject it points at and will
go null if that object is destroyed. This does mean that whatever owns the
pointer will have to handle it suddendly going null, but that is better than
a stale pointer.

This is for holding onto references to GameObjects for longer times, although
it can be used for short times as well. References can be used for functions
and other short term things where the object will not be deleted.

### Planes ###
A Plane object repersents a layer of reality. Currently there are two, the Map
which repersents the game world and the Gui which is between that and the
user.

Currently Planes are the highest level of coordinate space, so each defines
its own world space. Objects within that space may further define there own
local coordinates. Also the Plane may define how its world space differs from
the screen space, if at all.

Each maintains the collection of objects within its world space. It is
responsible for finding collisions between objects within that space and
checking what shapes are in a given area. This is for checking for clicks
on screen and so on.

The PlaneDrawable class also adds a draw function. The both Plane classes
(should) maintain the draw order of their contents.

Movement is on a 2d plane, so it can be handled with x, y & rotation.
Collition on the other hand requires a bit more detail, a shape is required on
both ends so they can hit each other.

### Components ###
The GameObjects are collections of components, I am considering if there is
some base I can give to the components. For instance if I wanted to have
variable components for a given object I would have to give them a super
class that acts as their interface. But that has some other issues,
primarally that I would have to have a standard interface for all of them.
But the seperate interfaces are kind of important, I could cram a all the
code I need into update but then making sure it happens in the correct order
is a problem.

Another wishlist feature is an abstract/template object pool for components.
Besides general data fragmentation, if components do end up with different
functions that activate at different stages in the loop, then grouping
components like this would help with data locality.

Taking it a step further, a couple of components have to be activated every
frame and it doesn't matter the order between them. Hence we could activate
them down the pool.

##### Transform
I will probaly just re-purpose the sf::Transform (or sf::Transformable) to
create the repersentation of the GameObject's position in 2d Space.

I am considering expanding this to a "Body" that also holds information about
the GameObject's shape as well.

##### AI
Controls how the GameObject acts. Most will have to be custom built for each
type of GameObject. Duplication might be able to be cut down with a State
Class system or similar code sharing stratagies but that will wait for a while
yet.

##### Graphics
Draws the graphical repersentation of the GameObject onto screen. Pretty
simple, some special instances may have to be made for special graphical
effects, but those will not come into effect for a while.

##### Physics
Defines the collidable (and clickable) area of the object. Is also responable
for moving the object forward in time. Hence they have to main features,
an `update` function that moves them forward in time and `collides` pedicate.

For now all physics bodies are circles. At this point it would be trivial to
fold it up into the GameObject but I will leave this open for expanstion for
now. But even then only the collidable area changes.

##### Audio
May not actually need an audio component, the interface around the audio
service may be enough. However some block of code to act as a reference
counter may be useful. Or not, this is not going to be in the first wave.

### Input Interface ###
This interface is only for handling input. It will contain or at least be
bound to the input loop. It is responsible for distributing input and keeping
track of the state of the user interface.

For instance it should track which units are selected so that when commands
are entered it knows which units to distribut them to.

Later it should also map keyboard shortcuts and perhaps notify GameObjects
as to their state, so they can highlight themselves if they are selected. But
that is for later.
