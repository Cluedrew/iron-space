#include "game-object.hpp"

// Implementation of GameObject.

#include "game-object-ptr.hpp"


GameObject::GameObject (AiComponent * ai, PhysicsComponent * physics,
                        GraphicsComponent * graphics) :
  ptrsToThis(), ai(ai), physics(physics), graphics(graphics)
{}

GameObject::GameObject (GameObject && other) :
  ptrsToThis(other.ptrsToThis), ai(other.ai),
  physics(other.physics), graphics(other.graphics)
{
  // Make sure the other's pointer list is empty (depending on if the
  // MIL does move or copy, it might already be).
  other.ptrsToThis.clear();

  // Null the other's pointers.
  other.ai = nullptr;
  other.physics = nullptr;
  other.graphics = nullptr;

  // Adjust pointers.
  std::vector<GameObjectPtr>::iterator it;
  for (it = ptrsToThis.begin() ; it != ptrsToThis.end() ; ++it)
  {
     it->ptr = this;
  }
}

GameObject::~GameObject ()
{
  // Manually clear this object from all the GameObjectPtrs that point at it.
  std::vector<GameObjectPtr>::iterator it;
  for (it = ptrsToThis.begin() ; it != ptrsToThis.end() ; ++it)
  {
     it->ptr = nullptr;
  }

  // Destroy all the components that make up the GameObject.
  delete ai;
  delete physics;
  delete graphics;
}
