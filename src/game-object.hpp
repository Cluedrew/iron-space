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
 *
 * If you are keeping a pointer (or reference) to a GameObject around for a
 * longer time, accross function calls or iterations of the main loop, use a
 * GameObjectPtr. (See its header.)
 */

#include <SFML/Graphics.hpp>
#include "collider.hpp"
class GameObjectPtr;



class GameObject : public sf::Transformable, public sf::Drawable
{
private:
  std::vector<GameObjectPtr *> ptrsToThis;
  friend class GameObjectPtr;

  //AiComponent * ai;
  //PhysicsComponent * physics;
  //GraphicsComponent * graphics;
  Collider collider;
  sf::CircleShape graphics;

protected:
public:
  GameObject ();
  //GameObject (AiComponent * ai,
  //            PhysicsComponent * physics,
  //            GraphicsComponent * graphics);
  /* Create a new GameObject from its list of components.
   * Params: Pointers to the components, ownership of them is taken.
   */

  GameObject(GameObject const & other) = delete;
  GameObject & operator= (GameObject const & other) = delete;
  GameObject & operator= (GameObject && other) = delete;
  // Copying and assignment are disabled.

  GameObject(GameObject && other);
  /* Move constructor, this new GameObject replaces the old one.
   * Params: Destroying reference to another GameObject.
   * Effect: Takes components, GameObjectPtrs move from the old GameObject
   *   to the new one.
   */

  virtual ~GameObject ();



  //bool handleInput (InputEvent const & input)
  /* Called during Input Step:
   * Resive and store a piece of input for this class.
   * Params: Reference to InputEvent.
   * Effect: Varies on AIComponent.
   * Return: True if the input was captured.
   */
  //{ return ai->handleInput(input); }

  //void updateAi (sf::Time const & deltaT)
  /* Called during AI Step:
   * Decide on actions to perform this turn.
   * Params: Time passed.
   * Effect: Varies with AIComponent.
   */
  //{ ai->update(deltaT); }

  //void handleMessage (MessageEvent const & msg)
  /* Called during AI Step (by other GameObjects):
   * Params: Message to be recived.
   * Effect: Varies with AIComponent.
   */
  //{ ai->handleMessage(msg); }

  //void updatePhysics (sf::Time const & deltaT)
  /* Called during Physics Step:
   * Move an object according to its internal physics.
   * Params: Time passed.
   * Effect: Moves the GameObject.
   */
  //{ physics->update(this, deltaT); }

  //void handleCollision (GameObjectPtr with)
  /* Called during Collision Step:
   * Resolve a collision with another GameObject.
   * Params: The other GameObject collided with.
   * Effect: Varies with AIComponent.
   */
  //{ ai->handleCollision(with); }

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw the GameObject, in its current state, to the target.
   * Params: The draw target
   * Effect: Draws to screen.
   */
};



void swap (GameObject & obj1, GameObject & obj2);
/* Swap two GameObjects, deep.
 * Params: Mutable references to GameObject.
 * Effect: Swaps the two GameObjects, dependant memory may or may not be
 *   moved but it will be accessable through the same object as before.
 */

#endif//GAME_OBJECT_HPP
