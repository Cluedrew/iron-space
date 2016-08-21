#include "physics-component.hpp"

// Implementation of the base PhysicsComponent

#include <SFML/Graphics/Transformable.hpp>
#include "circle-collider.hpp"



// see header
PhysicsComponent::PhysicsComponent () :
//  dx(0), dy(0), spin(0)
  collider(new CircleCollider(0, 0, 25))
{}

PhysicsComponent::~PhysicsComponent ()
{
  delete collider;
}

void PhysicsComponent::updatePosition (sf::Transformable const & parent)
{
  collider->update(parent.getTransform());
}

bool PhysicsComponent::collides (PhysicsComponent const & other)
{
  return collider->collides(*other.collider);
}

bool PhysicsComponent::collides (Collider const & other)
{
  return other.collides(*collider);
}
