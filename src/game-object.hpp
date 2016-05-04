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
  std::vector<GameObjectPtr*> ptrsToThis;

protected:
public:
  GameObject ();
  virtual ~GameObject () =0;
};

#endif//GAME_OBJECT_HPP
