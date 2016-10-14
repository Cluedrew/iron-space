#ifndef NULL_PHYSICS_HPP
#define NULL_PHYSICS_HPP

/* Null Object for the PhysicsComponent.
 *
 * Never collides, all update operations are really no-ops.
 */

#include "physics-component.hpp"



struct NullPhysics : public PhysicsComponent
{
  NullPhysics ();
  /* Create a NullPhysics object.
   */

  virtual ~NullPhysics () {}
};

#endif//NULL_PHYSICS_HPP
