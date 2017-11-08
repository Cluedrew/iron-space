#ifndef GAME_OBJECT
#define GAME_OBJECT

/* I think I'm not going to have a stable GameObject design for a long time.
 * So this is going to be my giant todo list for slowly making them better.
 *
 * Issues:
 *
 *   General redesign going on right now. Trying to make the GameObjects do
 * more work for the instance classes. The old design was almost a less
 * effective way to implement virtual function overrides. I'm aiming to try
 * and create a layer of code that does all the shared work for the lower
 * classes. But "all shared work" is funny. If every class does it then it
 * is can go in easy. But most things aren't quite that clean.
 *
 *   OK, code re-use is great, but the component system is resulting in a lot
 * of "wiring" to get the components to speak together. Many of which require
 * particular other components. So it is more trouble than it is worth. "has
 * a" components might still be a thing, but will probably in line them and
 * use them on a case-by-case basis.
 *   As a bridge to that feature, the overridable functions replacing the
 * components might direct calls to the components until they are not used
 * in any base class.
 *
 *   Where to put physics? Parts of it make sense being universal across all
 * classes, mainly that the ideas of collision and space are the same for
 * Widgets and PlaneObjects. But other times it is a waste of code, Widgets
 * don't need a volocity in any sane situation for instance.
 *   The PhysicsComponent is a thin wrapper around Collider, it was originally
 * supposed to be there, with a active version that would handle velocity and
 * rotation. Although I might keep the Collider, that logic will probably move
 * up to the class. (Just a question of which class.)
 *   Putting it on the GameObject with a control flag might work. The cost of
 * that is some dead code and maybe some wasted space, maybe a bit of speed.
 * At my scale I can give up some of that, but I would like clean solution.
 *
 *   Input handling has been partially solved with the FatFunction callbacks.
 * There is still the matters of what preprocessing I can do, where I can do
 * it and the hook functions that recive the final input.
 *   Not to mention how do they access the subject to listen for inputs.
 *
 *   Collision handling has also gone to a weird place. Because all the child
 * types I am creating provide their own collision handling, but I still have
 * this required handleCollision on the main class.
 *   I could just tear that out and leave collision handling to the children
 * by their own rules. This would require either getting that functionality
 * out of the AiComponent or rewiring. Is there a shared solution that might
 * work better and prevent duplication of code.
 *
 *   At some point I should also think about a system to store children on
 * GameObjects. Not type children, but leaf nodes within the state. But that
 * is a bit further away.
 *
 *
 * Hirarchy:
 * A brief look at some of the higher level objects, the base GameObjects and
 * the intermediate object types. Very brief until I fillin the descriptions.
 *
 * - GameObject
 *   - Widget
 *   - PlaneObject
 */

class GameObject : public sf::Drawable
/* Defines the general interface for all GameObjects. Most of this has to do
 * with the main loop (input, update (ai/physics/colition) and draw) and
 * probably a memory management tool.
 *
 * What to do about messaging? Are there any messages we want to be able to
 * handle at the top level? Input is a likely candidate. However I don't think
 * we will need a general messaging system because we can use pointers to
 * the subtypes in this new system.
 *
 * And I think I have been thinking about this in the wrong way, we probably
 * need two layers of functions. First ones called by the system. Most of them
 * can probably be defined in GameObject and be left alone there after, maybe
 * with a few flags or protected variables that alter their behaviour. Or
 * maybe that is the goal, for simplicity and speed.
 *
 * The second group are those overriden by a particular subclass, the hooks if
 * you will. They can redirect to components, but more often I think that
 * having immediate access to the other aspects of the GameObject is more
 * important.
 *
 * Also I think I need some tools for distributing calls to sub-objects.
 * Particularly to ensure that each step gets handed out in the correct way.
 * Just having proper containers for mixing might help that.
 */
{
  // We can replace the PhysicsComponent with a straight Collider.
  Collider * body;

public:
  // Some examples:

  enum ControlFlags
  {
    RespondToMouse = 1,
    UpdatePhysics = 2,
  } control;

  bool mouseHoverCheck(sf::Vector2i mousePosition)
  {
    // Objects that don't respond to the mouse can skip the physics check.
    if (control & RespondToMouse)
      return body.collides(PointCollider(mousePosition));
    return false;
  }

  bool handleInput (InputEvent const & input);
  /* Top level input handler for a particular game object.
   * This might actually get changed seriously, as most input (except maybe
   * the mouse) will be going through the state before reaching a GameObject.
   */

  void updateStep (sf::Time const & deltaT)
  {
    // Call the overridable update for object behaviour.
    update(deltaT);
    // If the object has physics, update it according to volocity.
    if (control & UpdatePhysics)
      updatePhysics();
  }

  // GameObject itself will probably have nothing to add to the draw function,
  // but lower objects could probably do some stuff for the states, such as
  // calculating the transform.

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
  virtual void overlapNext (GameObject2D const & with);
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

class Widget : public GameObject
/* The "GuiObject". There might be some shared code with the GameObject2D but
 * really it is lacking the physics (except for collision with the mouse).
 * It might also have some nesting options, because widgets seem to be
 * orginized that way.
 */
{
  enum class MouseState : char {Free, Hover, Click} mouseState;

protected:
  virtual void hoverBegin (mouse?);
  virtual void hoverNext (mouse?);
  virtual void hoverEnd (mouse?);
  virtual void clickBegin (mouse?);
  virtual void clickNext (mouse?);
  virtual void clickEnd (mouse?);

public:
  enum class Interaction : char {Static, Interactable}

  Widget (Interaction interact);

  Interaction getInteraction ();
  void setInteraction (Interaction);
  /* Solution to the interactibility of the widget, set a flag. The flag
   * (or flags) determaine what sort of checks we do. So before checking if
   * the object was clicked, first check to see if the object can be clicked,
   * if not just say no. Currently I have just two modes, but more could be
   * added. To clean up names I might need some declarations like:
   * static Interaction const Static = Interaction::Static;
   */
};

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

#endif//GAME_OBJECT
