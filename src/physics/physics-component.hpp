#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

/* A physics component, determains if there was a collision and moves the
 * object forward through space.
 *
 * WIP Very Work in Progress. Will be an abstract base at some time but I
 * will probably try to figure out the standard for this component first.
 */

#include "circle-collider.hpp"
namespace sf
{
  class Transformable;
}



class PhysicsComponent
{
private:
//  Collider collider;
  CircleCollider collider;

protected:
public:
  PhysicsComponent ();
  virtual ~PhysicsComponent ();

  void updatePosition (sf::Transformable const & parent);
  /* Update the position of the internal collider.
   * WIP
   */

  bool collides (PhysicsComponent const & other);
  bool collides (Collider const & other);
  /* Check for a collision between this class and another.
   * WIP
   */
};



#if 0
// OK, I ported over my planed version but it is going to get hacked appart.
class PhysicsComponent
{
private:
  // Position is handled in the GameObject itself.
  float dx, dy;
  float spin;

  Shape body;

protected:
public:
  PhysicsComponent ();
  virtual ~PhysicsComponent ();

  void update (GameObject & obj, sf::Time const & deltaT);
  /* Move the GameObject through space.
   * Params: Mutable reference to the GameObject and time that passed during
   *   this update.
   * Effect: Modifies the GameObject's transform.
   */

  bool collidesWith (PhysicsComponent const & other);
  /* Check for a collision between the this component's body and the other
   *   component's body.
   * Params: Reference to the other physics component.
   * Return: True if there was a collision, false otherwise.
   *
   * ! Still can't get positional data.
   */
};
#endif

#endif//PHYSICS_COMPONENT_HPP
