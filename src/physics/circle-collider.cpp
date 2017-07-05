#include "circle-collider.hpp"

// Implementation of the temperary collider.
// Vector2 is actually included through Transformable.

#include <cmath>
#include <SFML/Graphics/Transform.hpp>
#include "util/math.hpp"
#include "point-collider.hpp"
#include "align-rect-collider.hpp"



// Constructors and Deconstructor:
// see header
CircleCollider::CircleCollider (float x, float y, float r) :
  localCenter(x, y), worldCenter(x, y), localRadius(r), worldRadius(r)
{}

CircleCollider::~CircleCollider ()
{}



bool CircleCollider::collides (ColliderLeaf const & other) const
{
  return other.collidesWith(*this);
}

static float distSquared(sf::Vector2f const & lhs, sf::Vector2f const & rhs)
/* Calculate the square distance between two points.
 *   This saves us the more complex square root operation.
 * Params: Two 2d points, order does not matter.
 * Return: The distance between them squared.
 */
{
  return sqr<float>(lhs.x - rhs.x) + sqr<float>(lhs.y - rhs.y);
}

// see header
bool CircleCollider::collidesWith (CircleCollider const & other) const
{
  float distSqr = distSquared(worldCenter, other.worldCenter);
  float combinedRSqr = sqr<float>(worldRadius + other.worldRadius);

  return (distSqr < combinedRSqr);
}

bool CircleCollider::collidesWith (PointCollider const & other) const
{
  float distSqr = distSquared(worldCenter, other.getWorldPoint());
  float combinedRSqr = sqr<float>(worldRadius);

  return (distSqr < combinedRSqr);
}

bool CircleCollider::collidesWith (AlignRectCollider const & other) const
{
  sf::Vector2f center = worldCenter;
  sf::FloatRect rect = other.getWorldRect();
  sf::Vector2f closest(
      limitValue<float>(rect.left, center.x, rect.left + rect.width),
      limitValue<float>(rect.top,  center.y, rect.top + rect.height));

  float distSqr = distSquared(center, closest);
  float combinedRSqr = sqr<float>(worldRadius);

  return (distSqr < combinedRSqr);
}


// see header file
void CircleCollider::setPos (float x, float y)
{
  localCenter.x = x;
  localCenter.y = y;
}

// see header file
void CircleCollider::setPos (sf::Vector2f const & xy)
{
  localCenter = xy;
}

void CircleCollider::update(sf::Transform const & root)
{
  worldCenter = root.transformPoint(localCenter);

  sf::Vector2f localEdge(localCenter.x + localRadius, localCenter.y);
  sf::Vector2f worldEdge = root.transformPoint(localEdge);

  float wRSqr = distSquared(worldCenter, worldEdge);
  worldRadius = sqrt(wRSqr);
}
