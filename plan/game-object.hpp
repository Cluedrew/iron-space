#ifndef GAME_OBJECT
#define GAME_OBJECT

/* So some thoughts on a posible rework on the GameObject. The current
 * container based design is having some issues. Most of this has to do
 * with comunication between the components.
 *
 * For instance if the Ai wants to tell the Graphics how to draw itself,
 * it will have to get a GraphicsComponent and then cast it down to the
 * type with the proper interface. Or it could store the pointer itself,
 * but at that point it is starting to take on the role of the GameObject.
 *
 * So I am thinking of discarding the "generic container" model and then
 * have a GameObject base class which you inherite from and then create the
 * exact object you want. Shouldn't be any slower, it just pushes the virtual
 * method look-ups up a layer and shouldn't slow things down.
 *
 * Components will still be a thing, especially for reuse, but they might be
 * direct members instead of pointers. That may or may not be a problem for
 * some optimization ideas I had, but I'm a long way from having to cross that
 * bridge.
 *
 * Further re-use will come from intermediate base classes. These handle
 * functions many (but not all) of the final game objects share.
 *
 * To switch to this current version (if I do) the best bet would probably
 * be to rename the existing GameObject to GameObject2D. Then introduce the
 * new GameObject as its parent, pull the features that will be a part of it.
 * Split off the widgets and then start refactoring.
 */

class GameObject : public sf::Drawable
/* Defines the general interface for all GameObjects. Most of this has to do
 * with the main loop (input, update (ai/physics/colition) and draw) and
 * probably a memory management tool.
 *
 * Should default implementations be included or use pure virtual?
 *
 * The swap of two GameObjects will have to be removed.
 *
 * What to do about messaging? Are there any messages we want to be able to
 * handle at the top level? Input is a likely candidate. However I don't think
 * we will need a general messaging system because we can use pointers to
 * the subtypes in this new system.
 */
{
  virtual bool handleInput (InputEvent const & input);
  // As current.

  virtual void update (sf::Time const & deltaT);
  // Main update step. Approximately the current updateAi;

  //virtual void swap ();
  /* If we have a buffer approch there will have to be a way to update the
   * buffer. Currently I don't think it is needed, but it would have to go
   * here, probably be called right before draw.
   */

  virtual void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* SFML drawable function.
   * Although not every GameObject will appear on screen I think enough of
   * them will it is worth adding them here.
   */
};

class GameObject2D : public GameObject, public sf::Transformable;
/* MapObject? PlaneObject? I like the idea of varing it by the first letter.
 * This takes all of the features of the GameObject but then makes it occur
 * in a space. GameObject2D then has a location in space, and probably a body
 * that can collide and overlap (well maybe not always, but I think at this
 * point it is reasonable to assume that) as well as move around.
 *
 * So in short it adds 2D location and physics to the GameObject.
 *
 * handleCollision should also be broken up. There is some timing issues with
 * the current set up. I think we need 3 handlers: begin->continue->end.
 * Begin is called the first frame of collision, continue ever frame of
 * collison there after and end the first frame after that. collision->overlap
 */
{

  void updatePhysics (sf::Time const & deltaT);
  /* Allow an object to move with time.
   * Not virtual, although probably dependant on some settings else where,
   * such as the update function setting the speed.
   */

protected:
  virtual void overlapBegin (GameObject2D const & with);
  virtual void overlapContinue (GameObject2D const & with); // <~name
  virtual void overlapEnd (GameObject2D const & with);

public:
  bool overlapCheck (GameObject2D const & with);
  /* Check to see if this object overlaps with the provided one.
   * Params: Regular reference?
   * Effect: If objects overlap, calls one of overlapBegin or overlapContinue
   * Return: True if there is an overlap, otherwise returns false.
   */

  void endOverlapStep ();
  /* Call to end the overlap step of this frame.
   * Effect: Resets the frame for overlaps and calls overlapEnd on all
   *   object that collided last frame but not this one.
   */
};

class Widget : public GameObject;
/* The "GuiObject". There might be some shared code with the GameObject2D but
 * really it is lacking the physics (except for collision with the mouse).
 * It might also have some nesting options, because widgets seem to be
 * orginized that way.
 */

class GameObject3D : public GameObject;
/* This isn't going to come along for a long time. But some day it might.
 * Maybe call it a SpaceObject?
 *
 * When that day comes, GameObject2D could actually be a 'decorator' for
 * GameObject3D that takes out the 3rd dimention for you.
 */

/* Memory Management:
 * OK, so currently memory management has not been an issue because I am not
 * creating new things or destroying only ones, so I suppose I should leave
 * this be for now.
 * Regardless I have thoughts on it. Within a single class I can manage memory
 * manually, but in the context of the larger program that is going to be hard
 * to do. So I was working on special pointers for the GameObject class to
 * help.
 * The first was the NullingPtr design, if an object is deleted sets all the
 * pointers pointing at it to null. This is relatively slow and I realize that
 * it might be havic is concurency is ever introduced. Hadn't thought of that.
 * But from a game prospective it was kind of nice. The theory was the game
 * logic would delete something and all the background reference would take
 * care of themselves.
 * Now I am convincing myself to throw out that work and instead use reference
 * counting. All the big engines I know of use it, its only real drawback is
 * cycles can break the system, so avoid that. I think adding an alive field
 * to the object would allow me to mimic the nulling ptr, in most cases.
 */

class PassivePhysics2D;
class ActivePhysics2D : public PassivePhysics2D;
/* Possible new form of physics. A PassivePhysics object stays in place and
 * does not move over time, if you want it do you do so manually. Its only
 * functionality is to detect collisions. This is for things like Widgets.
 *
 * An ActivePhysics object can have things like speed and will move itself
 * around every frame. It is for GameObject2D.
 *
 * The point of this is really to cut down on code duplication. Those two
 * objects have a lot of shared behaviour but I think the difference is also
 * enough that they can't share an additional ancestor. Using these as
 * components is a way around that.
 */

#endif//GAME_OBJECT
