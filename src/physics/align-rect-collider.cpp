#include "align-rect-collider.hpp"

// Implementation of the Aligned Rectangle Collider

#include <SFML/Graphics/Transform.hpp>
#include "circle-collider.hpp"
#include "point-collider.hpp"



AlignRectCollider::AlignRectCollider
    (float left, float top, float width, float height) :
  absRect(left, top, width, height),
  left(left), top(top), width(width), height(height)
{}

AlignRectCollider::AlignRectCollider (sf::FloatRect const & rect) :
  absRect(rect), left(rect.left), top(rect.top),
  width(rect.width), height(rect.height)
{}

AlignRectCollider::~AlignRectCollider ()
{}

bool AlignRectCollider::collides (ColliderLeaf const & other) const
{
  return other.collidesWith(*this);
}

bool AlignRectCollider::collidesWith (CircleCollider const & other) const
{
  return other.collidesWith(*this);
}

bool AlignRectCollider::collidesWith (PointCollider const & other) const
{
  return absRect.contains(other.getWorldPoint());
}

bool AlignRectCollider::collidesWith (AlignRectCollider const & other) const
{
  return absRect.intersects(other.absRect);
}

void AlignRectCollider::update (sf::Transform const & parent)
{
  sf::Vector2f origin = parent.transformPoint(left, top);
  absRect.left = origin.x;
  absRect.top = origin.y;
  absRect.width = width;
  absRect.height = height;
}

sf::FloatRect AlignRectCollider::getWorldRect () const
{
  return absRect;
}
