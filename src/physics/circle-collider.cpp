#include "circle-collider.hpp"

// Implementation of the temperary collider.
// Vector2 is actually included through Transformable.

#include <iostream>
#include "../util/math.hpp"



// Constructors and Deconstructor:
CircleCollider::CircleCollider (float x, float y, float r) :
  relativePosition(), absolutePosition(), radius(r)
{
  relativePosition.setPosition(x, y);
}

CircleCollider::~CircleCollider ()
{}



// Implementation Functions:

bool CircleCollider::collides (Collider const & other) const
{
  CircleCollider const * othis = dynamic_cast<const CircleCollider*>(&other);
  if (nullptr == othis)
    return other.collides(*this);
  else
    return collidesWith(*othis);
}

// see header
bool CircleCollider::collidesWith (CircleCollider const & other) const
{
  // I use the squared values because (unless we start dealing with overflow)
  // that should be slightly more accurate.
  sf::Vector2f myPos = absolutePosition.getPosition();
  sf::Vector2f otherPos = other.absolutePosition.getPosition();
  float run = myPos.x - otherPos.x;
  float rise = myPos.y - otherPos.y;

  float distSqr = sqr<float>(run) + sqr<float>(rise);
  float combinedRSqr = sqr<float>(radius + other.radius);

  /*
  std::cout << "CircleCollider: myPos(" << myPos.x << "," << myPos.y << ") otherPos("
            << otherPos.x << "," << otherPos.y << ")\n"
            << "CircleCollider: " << distSqr << " <= " << combinedRSqr << std::endl;
  */

  return (distSqr <= combinedRSqr);
}

// see header file
void CircleCollider::setPos (float x, float y)
{
  relativePosition.setPosition(x, y);
}

// see header file
void CircleCollider::setPos (sf::Vector2f const & xy)
{
  relativePosition.setPosition(xy);
}

void CircleCollider::update(sf::Transformable const & root)
{
  // I'm not sure how to handle origin.

  absolutePosition.setPosition(root.getPosition());
  absolutePosition.setRotation(root.getRotation());
  absolutePosition.setScale(root.getScale());

  absolutePosition.move(relativePosition.getPosition());
  absolutePosition.rotate(relativePosition.getRotation());
  absolutePosition.scale(relativePosition.getScale());
}
