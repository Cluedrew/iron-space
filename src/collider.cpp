#include "collider.hpp"

// Implementation of the temperary collider.
// Vector2 is actually included through Transformable.

#include "util/math.hpp"



// Constructors and Deconstructor:
Collider::Collider (float x, float y, float r) :
  pos(), r(r)
{
  pos.setPosition(x, y);
}

Collider::~Collider ()
{}



// Implementation Functions:
bool Collider::collides (Collider const & other) const
{
  // I use the squared values because (unless we start dealing with overflow)
  // that should be slightly more accurate.
  sf::Vector2f myPos = pos.getPosition();
  sf::Vector2f otherPos = other.pos.getPosition();
  float run = myPos.x - otherPos.x;
  float rise = myPos.y - otherPos.y;

  float distSqr = sqr<float>(run) + sqr<float>(rise);
  float combinedRSqr = sqr<float>(r + other.r);

  return (distSqr <= combinedRSqr);
}

void Collider::setPos (float x, float y)
{
  pos.setPosition(x, y);
}

void Collider::setPos (sf::Vector2f const & xy)
{
  pos.setPosition(xy);
}
