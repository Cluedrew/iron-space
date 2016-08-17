#include "point-collider.hpp"

// Implementation of Point Collider

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>
#include "circle-collider.hpp"
#include "align-rect-collider.hpp"




PointCollider::PointCollider (float x, float y) :
  absX(x), absY(y), relX(x), relY(y)
{}

PointCollider::PointCollider (sf::Vector2f xy) :
  absX(xy.x), absY(xy.y), relX(xy.x), relY(xy.y)
{}

PointCollider::~PointCollider ()
{}

bool PointCollider::collides (ColliderLeaf const & other) const
{
  return other.collidesWith(*this);
}

bool PointCollider::collidesWith (CircleCollider const & other) const
{
  return other.collidesWith(*this);
}

bool PointCollider::collidesWith (PointCollider const & other) const
{
  return (absX == other.absX) && (absY == other.absY);
}

bool PointCollider::collidesWith (AlignRectCollider const & other) const
{
  return other.getWorldRect().contains(absX, absY);
}

sf::Vector2f PointCollider::getPoint () const
{
  return sf::Vector2f(absX, absY);
}
