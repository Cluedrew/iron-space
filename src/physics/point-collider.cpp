#include "point-collider.hpp"

// Implementation of Point Collider

#include <SFML/Graphics/Transform.hpp>
#include "circle-collider.hpp"
#include "align-rect-collider.hpp"




PointCollider::PointCollider (float x, float y) :
  localPos(x, y), worldPos(x, y)
{}

PointCollider::PointCollider (sf::Vector2f xy) :
  localPos(xy), worldPos(xy)
{}

PointCollider::~PointCollider ()
{}

void PointCollider::update (sf::Transform const & root)
{
  worldPos = root.transformPoint(localPos);
}

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
  return worldPos == other.worldPos;
}

bool PointCollider::collidesWith (AlignRectCollider const & other) const
{
  return other.getWorldRect().contains(worldPos);
}

sf::Vector2f PointCollider::getWorldPoint () const
{
  return worldPos;
}
