#ifndef PHYSICS_COMPONENT_HPP
#define PHYSICS_COMPONENT_HPP

/* A physics component.
 */



class PhysicsComponent
{
private:
  // Position is handled in the GameObject itself.
  float dx, dy;
  float spin;

  Shape collider;

protected:
public:
  PhysicsComponent ();
  virtual ~PhysicsComponent ();

  void update (GameObject &);

  bool collidesWith (PhysicsComponent &);
  // Does the component hold a perminate reference to its GameObject?
};

#endif//PHYSICS_COMPONENT_HPP
