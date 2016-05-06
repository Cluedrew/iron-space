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
be divided into four parts:

1. Input
2. Update
3. Output
4. Timing

Again it is the step 2 that needs the most attention. But the others are
hardly simple so I will talk about them all.

1. Input - A polling loop that searches for input events. Some important
system events may be handled in place, however most are sent out and handled
elsewhere.
2. Update - Calls to update the state of all objects. This will take into
account both the input and the time passed, plus and decitions that come from
within individual code blocks.

    OK I think I have to break this one up. I think I will go with 3 parts:
    1. Update AI - Use inputs (and the changing situation) to update what a
GameObject wants to do this frame.
    2. Update Physics - Use the goals from the AI stage to move things that
have to be moved.
    3. Respond to Collisions - If things bumped into each other tell them they
did and see what they want to do about it.
3. Output - After the world has changed, show those changes. Draw to the
screen, play sounds and... I think that is it. I got no rumble going on. The
logic of deciding what should be outputted mostly happens during update,
this just spits things to the screen and resolves sounds.
4. Timing - Frame rate limiter. Keeps things from going too fast. This may be
nothing more than a call to sf::Window::setFramerateLimit(limit).

Besides simply calling code the main loop is incharge of managing tempral
orginiation. Other things can define what happens but you always have to
return to the main loop to determain exactly when they happen.

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
world as well as the gui.

The main thing the GameObject consists of its transform (its location in the
world) and a set of components that create the rest of the components.

GameObjects should not be deleted directly, instead they que themselves up
to be deleted at the end of the update frame. This way they can destroy
themselves and it should prevent some conflicts.

##### Hierarcy
Sub-classes of GameObject implement what components are wired into the object.
The actual behaviour should come from the components themselves.

Right now I have two types of Sub-GameObjects:
+ *MapObject* is used to repersent object that appear on the map. Which also
  means in the world, so they interact with the physics engine. Has AI,
  graphical and physics components.
+ *GuiObject* is used for items that appear on the screen as part of the
  interface. Has AI and graphical.

The other way is just creating slots and filling in the needed ones.

I know deep class hierarcies can cause problems, but I think 2 deep is not
enough to cause the fragility issues of deep hierarcies while allowing me some
inheratince advantages. Similarly, I'm aware of the advantages of composition,
so the inherated classes should be built like packages of components.

The main reason there is not a single GameObject class with a unified
interface is tempral orginiation. If all GameObjects have a single update than
they have to do everything all at once, which is does not allow things (as
an example) react to changes around them.

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
