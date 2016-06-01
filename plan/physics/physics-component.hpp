#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

/* A physics component, determains if there was a collision and moves the
 * object forward through space.
 */



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

#endif//PHYSICS_COMPONENT_HPP
