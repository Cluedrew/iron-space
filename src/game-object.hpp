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

protected:
public:
  GameObject ();
  /* Default constructor to be used by child classes.
   */

  virtual ~GameObject () =0;

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
};



void swap (GameObject & obj1, GameObject & obj2);
/* Swap two GameObjects, deep.
 * Params: Mutable references to GameObject.
 * Effect: Swaps the two GameObjects, dependant memory may or may not be
 *   moved but it will be accessable through the same object as before.
 */

#endif//GAME_OBJECT_HPP
