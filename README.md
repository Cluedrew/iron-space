# iron-space
An outer space base building game. Created as a learning project.

The project uses the [SFML](http://www.sfml-dev.org/index.php "Find it here.")
library for interacting with the system.

#### Project Status ####
Planning - I am creating the plan. The plan means the general layout of the
code and the interdependance between systems. As well as writing out headers.

## Game ##
The game is a simple game. You find yourself in the depths of space and you
have to mine iron (you could also call it ore) to build more ships and mining
stations.

## Plan ##
My internal map of how the program works. Consider this a text UML diagram.

Also note all of this is subject to change.

### Directories ###
First a bit about the layout of the code base.
+ *src* is the top level code directory and contains files that run the core
  code and tie the codebase together.
+ *util* is for other files, those that don't have a particlar place, are used
  accross the code base but are not core.
+ *physics* is for code that runs the physics simulation part of the game.
  Things moving over time, resolving colitions and similar.
+ *graphics* is for image loading and rendering code.
+ *audio* is for sound loading and playing code.
+ *objects* is planned, holds code that manages individual GameObjects.

### Main Loop ###
The main loop is the heart of the program, with each iteration of the loop
another beat. The highest level of the game looks like this:

1. Set Up
2. Main Loop
3. Clean Up

And comparitively, not a lot happens in steps 1 & 3. The main loop itself can
be divided into several parts:

1. Poll Input
2. Update AI
3. Update Physics
4. Collisions
5. Render
6. Wait

Input is distributed at the time of polling, but any serious computation
from it should be resolved during AI.

AI is where most of the thinking occures, given the input and the time passed
(that is, internal changes) each GameObject decides what it is going to do.

AI is seperated from Physics for two reasons: first they are going in
different components, secondly it creates a pesudo-double buffer as all AI
looks at the physical world of the last frame before the physics updates.

Physics is when all of the transforms get updated.

Collisions scans for things that are overlapping and tells them about that.
Because we are in space things can move over and under each other, but
reaching each other may repersent something.

Render simply goes through all the GameObjects (in draw order) and gets
them to draw themselves on screen. Also here the audio service resolves any
requests that have been made to it over the frame.

Wait causes the program to rest for the remaining time in this frame.

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

##### Physics
How things move in space. This system moves things around and handles the
fallout from that. The fallout being collitions, because the game takes place
in space I plan to have a lot of moving over and under each other. This is to
avoid having to move things around to resolve collitions. In turn, that is
because I don't want to write that code.

Movement is on a 2d plane, so it can be handled with x, y & rotation.
Collition on the other hand requires a bit more detail, a shape is required on
both ends so they can hit each other.

Clicks are collitions as well, a click is a point that collides with things
on screen.

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

GameObjects should not be deleted directly, instead they que themselves up
to be deleted at the end of the update frame. This way they can destroy
themselves and it should prevent some conflicts.

##### GameObject Messaging
There has to be a way of giving general messages to GameObjects. Most
GameObjects need to comunicate with each other and they have to do this is
a very general way that is outside the scope of the generic GameObject.

I have two ideas for this:
+ The *getComponent* method, a templated member function that generally
  returns null, but sub-classes can override it to provide access to its
  components. These components then act as an interface.
+ The *sendMessage* method, send messages to an virtual function which the
  sub-classes can override to react to differently. (Visitor Pattern)

This is primarily for comunication between GameObjects, as that is the hardest
one to generalize. Two other types of messages are Inputs and Collisions,
which come from the InputHandler and the Physics Engine respectively. These
may or may not be seperate.

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

Each maintains the collection of objects within it, finds collisions between
those objects (collisions to not occur between objects in different planes)
and distributs input to them. Or mouse actions at least, as those have to
be translated from screen coordinates to the coordinates of the plane. The
planes also maintain the draw order of objects within them (between planes
must be handled by outside code) and maintains the view into the plane that
appears on screen.

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

For now all physics bodies are circles.

##### Audio
May not actually need an audio component, the interface around the audio
service may be enough. However some block of code to act as a reference
counter may be useful. Or not, this is not going to be in the first wave.
