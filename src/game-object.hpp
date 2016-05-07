#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

/* The centeral GameObject for the system. It is based off of the Unity
 * GameObject with a few important changes, mostly specializing it for the
 * given game. Although the GameObject is supposed to be component base,
 * there is actually no room for components here. Inherated sub-classes are
 * responsible for added components.
 *
 * GameObject contains the position of the object in, which is essental data
 * accross almost all components.
 */

#include "game-object-ptr.hpp"
class GameObjectPtr;

class GameObject
{
private:
  sf::Transfrom/*able*/ transform;
  std::vector<GameObjectPtr*> ptrsToThis;

  AiComponent * ai;
  PhysicsComponent * physics;
  GraphicsComponent * graphics;

protected:
public:
  GameObject (AiComponent * ai,
              PhysicsComponent * physics,
              GraphicsComponent * graphics);
  /* Create a new GameObject from its list of components.
   * Params: Pointers to the components, ownership of them is taken.
   */

  virtual ~GameObject ();

  template<typename T>
  virtual T * getComponent ();
  template<typename T>
  virtual T const * getComponent () const;
  /* Get the component from this object of type T if it exists.
   * Return: NULL, sub-classes override to provide access to components they
   *   have and want to show.
   *
   * This one is still an idea, part of the reason for this is then I can
   * access interfaces in components from elsewhere. Sort of a comunication
   * thing, below is the other option.
   */

  virtual void giveMessage (MessageEvent const & msg);
  /* Send a message to this GameObject and have it resolve it.
   * Params: A reference to a message event.
   * Effect: Varies with message and sub-class.
   */

  bool handleInput (InputEvent const & input)
  /* Called during Input Step:
   * Resive and store a piece of input for this class.
   * Params: Reference to InputEvent.
   * Effect: Varies on AIComponent.
   * Return: True if the input was captured.
   */
  { return ai->handleInput(input); }

  void updateAi (sf::Time const & deltaT)
  /* Called during AI Step:
   * Decide on actions to perform this turn.
   * Params: Time passed.
   * Effect: Varies with AIComponent.
   */
  { ai->update(deltaT); }

  void handleMessage (MessageEvent const & msg)
  /* Called during AI Step (by other GameObjects):
   * Params: Message to be recived.
   * Effect: Varies with AIComponent.
   */
  { ai->handleMessage(msg); }

  void updatePhysics (sf::Time const & deltaT)
  /* Called during Physics Step:
   * Move an object according to its internal physics.
   * Params: Time passed.
   * Effect: Moves the GameObject.
   */
  { physics->update(deltaT); }

  void handleCollision (GameObjectPtr with)
  /* Called during Collision Step:
   * Resolve a collision with another GameObject.
   * Params: The other GameObject collided with.
   * Effect: Varies with AIComponent.
   */
  { ai->handleCollision(with); }

  void render (/*Maybe some view data.*/)
  /* Called during Render Step:
   * Move and re-draw the object on the screen.
   * Params:
   * Effect: Draws to screen.
   */
  { graphics->render(/*view data*/); }
};



void swap (GameObject & obj1, GameObject & obj2);
/* Swap two GameObjects, deep.
 * Params: Mutable references to GameObject.
 * Effect: Swaps the two GameObjects, dependant memory may or may not be
 *   moved but it will be accessable through the same object as before.
 */

#endif//GAME_OBJECT_HPP
