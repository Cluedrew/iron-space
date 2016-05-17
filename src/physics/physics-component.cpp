#include "physics-component.hpp"

// Implementation of the base PhysicsComponent



// see header
PhysicsComponent::PhysicsComponent () :
  dx(0), dy(0), spin(0)
{}

PhysicsComponent::~PhysicsComponent ()
{}

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
