#include "null-physics.hpp"

// Implementation of the do nothing PhysicsComponent.

#include "collider.hpp"



/* The NullCollider is no-where and never collides.
 */
struct NullCollider : public Collider
{
  void update (sf::Transform const & root)
  {}

  bool collides (Collider const & other) const
  {
    return false;
  }

  bool collides (ColliderLeaf const & other) const
  {
    return false;
  }
};



NullPhysics::NullPhysics () :
  PhysicsComponent(new NullCollider())
{}
