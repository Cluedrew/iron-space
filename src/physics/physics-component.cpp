#include "physics-component.hpp"

// Implementation of the base PhysicsComponent

#include <SFML/Graphics/Transformable.hpp>



// see header
PhysicsComponent::PhysicsComponent () :
//  dx(0), dy(0), spin(0)
  collider(0, 0, 25)
{}

PhysicsComponent::~PhysicsComponent ()
{}

void PhysicsComponent::updatePosition (sf::Transformable const & parent)
{
  collider.update(parent.getTransform());
}

bool PhysicsComponent::collides (PhysicsComponent const & other)
{
  return collider.collidesWith(other.collider);
}

bool PhysicsComponent::collides (Collider const & other)
{
  return other.collides(collider);
}



#if 0
// see header
void PhysicsComponent::update (GameObject & obj, sf::Time const & deltaT)
{
  float dt = deltaT.asSeconds();
  obj.move(dx * dt, dy * dt);
  obj.rotate(spin * dt);
}

// see header
bool PhysicsComponent::collidesWith (PhysicsComponent &)
{
  return body.overlaps(other.body);
}
#endif
