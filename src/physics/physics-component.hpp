#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

/* A physics component, determains if there was a collision and moves the
 * object forward through space.
 *
 * Unlike the other components it is not abstract. All the logic is identical
 * except for the part in the collider, and that part swaps out.
 * WIP Very Work in Progress. Will be an abstract base at some time but I
 * will probably try to figure out the standard for this component first.
 *
 * TODO I think I have confligated two parts into physics: collition and
 * kinimatics. They are connected (especially if you want to have something
 * move but stop when it hits something) but they are not the same thing.
 * The collider part can exist on its own. The kinimatics part should probably
 * exist around that.
 */

#include "collider.hpp"
namespace sf
{
  class Transformable;
}



class PhysicsComponent
{
private:
  Collider * collider;

protected:
public:
  PhysicsComponent (Collider * collider);
  /* Create a PhysicsComponent with the collider that reperents its body.
   * Params: Pointer to collider, the PhysicsComponent takes ownership.
   */
  virtual ~PhysicsComponent ();

  void updatePosition (sf::Transformable const & parent);
  /* Update the position of the internal collider.
   * WIP
   * Perhaps it should also be responsible for moving the object as well.
   */

  bool collides (PhysicsComponent const & other);
  bool collides (Collider const & other);
  /* Check for a collision between this class and another.
   * WIP
   */
};

#endif//PHYSICS_COMPONENT_HPP
