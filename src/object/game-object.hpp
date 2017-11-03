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
 *
 * TODO In the process of being refactored.
 *      Or will be once I have the curage to throw out so much old code.
 * The top of the GameObject hierarcy. The GameObject provides some simple
 * memory management tools and hooks for the game loop to latch onto.
 * This may be expanded to include a messaging system and others as the
 * project progresses.
 */

#include <bitset>
#include <SFML/Graphics.hpp>
class Collider;
#include "game-object-ptr.hpp"
class InputEvent;
class AiComponent;
class PhysicsComponent;
class GraphicsComponent;



class GameObject :
    public sf::Transformable,
    public sf::Drawable
{
public:
  enum ControlFlags
  {
    UpdatePhysics,

    ControlFlagCap,
  };

private:
  GameObjectPtr::back_ptr_container ptrsToThis;
  friend class GameObjectPtr;

  std::bitset<ControlFlagCap> controlFlagSet;

  AiComponent * ai;
  PhysicsComponent * physics;
  GraphicsComponent * graphics;

protected:
public:
  GameObject (AiComponent * ai,
              PhysicsComponent * physics,
              GraphicsComponent * graphics);
  /* Create a new GameObject from its components.
   * Params: Pointers to the components, ownership of them is taken.
   */

  GameObject (sf::Transformable const & start,
              AiComponent * ai,
              PhysicsComponent * physics,
              GraphicsComponent * graphics);
  /* Create a new GameObject from its starting transform and components.
   * Params: A reference to the starting transform (which is copied) and
   *   pointers to the components, ownership of them is taken.
   */

  GameObject (GameObject const & other) = delete;
  GameObject & operator= (GameObject const & other) = delete;
  GameObject & operator= (GameObject && other) = delete;
  // Copying and assignment are disabled.

  GameObject (GameObject && other);
  /* Move constructor, this new GameObject replaces the old one.
   * Params: Destroying reference to another GameObject.
   * Effect: Takes components, GameObjectPtrs move from the old GameObject
   *   to the new one.
   */

  virtual ~GameObject ();



  bool receiveInput (InputEvent const & input);
  /* Called during Input Step:
   * Resive and store a piece of input for this class.
   * Params: Reference to InputEvent.
   * Effect: Varies on AIComponent.
   * Return: True if the input was captured.
   */

  bool collides (GameObject const & other) const;
  bool collides (Collider const & other) const;
  /* Possibly will have to be overhaulted.
   * Check if this object collides with another.
   */

  void updateStep (sf::Time const & deltaT);
  /* Main update function, update AI and Physics.
   * Params: Time to move the object forward by.
   * Effect: Calls update and updatePhysics.
   */

  GraphicsComponent * getGraphics();
  /* Get the GraphicsComponent for this object.
   * Return: A pointer to the graphics component. DO NOT FREE.
   */

  template<typename T>
  T * getCastGraphics()
  /* Get the GraphicsComponent dynamic_cast to the given type.
   * Return: A possibly null pointer the the graphics component. DO NOT FREE.
   */
  {
    return dynamic_cast<T *>(getGraphics());
  }

  //void handleMessage (MessageEvent const & msg)
  /* Called during AI Step (by other GameObjects):
   * Params: Message to be recived.
   * Effect: Varies with AIComponent.
   */

  //void updatePhysics (sf::Time const & deltaT)
  /* Called during Physics Step:
   * Move an object according to its internal physics.
   * Params: Time passed.
   * Effect: Moves the GameObject.
   */

  void handleCollision (GameObjectPtr & with);
  /* Called during Collision Step:
   * Resolve a collision with another GameObject.
   * Params: The other GameObject collided with.
   * Effect: Varies with AIComponent.
   */

  virtual void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw the GameObject, in its current state, to the target.
   * Params: The draw target
   * Effect: Draws to screen.
   */

protected:
  void setFlag (ControlFlags flag) { controlFlagSet.set(flag, true); }
  void unsetFlag (ControlFlags flag) { controlFlagSet.set(flag, false); }
  bool getFlag (ControlFlags flag) { return controlFlagSet.test(flag); }
  /* Getters and setters for the control flag.
   * I think some might have effects when you change them, otherwise the
   * ControlFlags could have direct access.
   */

  // The rest are hooks to override.
  virtual void update (sf::Time const & deltaT);
  /* Move the object forward in time.
   * Params: The amount of time by which to move forword.
   * Effect: Default, delagates to ai.update.
   */
};

#endif//GAME_OBJECT_HPP
