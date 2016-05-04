# iron-space
An outer space base building game. Created as a learning project.

The project uses the [SFML](http://www.sfml-dev.org/index.php "Find it here.")
library for interacting with the system.

### Project Status ###
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

### Systems ###
Overarching systems that cut accross the code base.

##### Main Loop
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
3. Output - After the world has changed, show those changes. Draw to the
screen, play sounds and... I think that is it. I got no rumble going on. The
logic of deciding what should be outputted mostly happens during update,
this just spits things to the screen and resolves sounds.
4. Timing - Frame rate limiter. Keeps things from going too fast. This may be
nothing more than a call to sf::Window::setFramerateLimit(limit).

Besides simply calling code the main loop is incharge of managing tempral
orginiation. Other things can define what happens but you always have to
return to the main loop to determain exactly when they happen.

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

### GameObject Hierarcy ###
There is a GameObject class that implements the code for a thing in the game.
However the actual game objects don't inherite directly from that, instead
there are some intermetiate classes.
+ *MapObject* is used to repersent object that appear on the map. Which also
  means in the world, so they interact with the physics engine.
+ *GuiObject* is used for items that appear on the screen as part of the
  interface.

I know deep class hierarcies can cause problems, but I think 2 deep is not
enough to cause the fragility issues of deep hierarcies while allowing me some
inheratince advantages. Similarly, I'm aware of the advantages of composition,
so the inherated classes should be built like packages of components.

The main reason there is not a single GameObject class with a unified
interface is tempral orginiation. If all GameObjects have a single update than
they have to do everything all at once, which is does not allow things (as
an example) react to changes around them.

GameObjects (and the various specializations) are stored in collections that
allow the mass dispatches to reach them all automatically. Adding and
removing objects from these collections should be folded into the constructors
and deconstructors. Similarly, as it is simpler if objects are destroyed at
a given point in the loop, so there may be a method to regester them for
deletion later.

The GameObjectPtr is a special smart pointer that points at GameObjects. It is
smart in that it is also an observer for the GameObject it points at and will
go null if that object is destroyed. This does mean that whatever owns the
pointer will have to handle it suddendly going null, but that is better than
a stale pointer.

### Map ###
The map is its own system, but not quite in the same way as the other systems
that are dedicated to a particular domain. Instead the map is both a container
for MapObjects and a cammra, that handles screen-world coordinate
translations, a sf::View should handle that.

### Gui ###
Similar to the map for GuiObjects. However it cuts out some extra parts that
the more static Gui elements. For instance they are locked to the screen and
do not update according to physics.

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
