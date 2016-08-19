#include "circle-collider.hpp"

// Implementation of the temperary collider.
// Vector2 is actually included through Transformable.

#include "../util/math.hpp"
#include "point-collider.hpp"
#include "align-rect-collider.hpp"



// Constructors and Deconstructor:
CircleCollider::CircleCollider (float x, float y, float r) :
  relativePosition(), absolutePosition(), radius(r)
{
  relativePosition.setPosition(x, y);
}

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
  sf::Vector2f myPos = absolutePosition.getPosition();
  sf::Vector2f otherPos = other.absolutePosition.getPosition();

  float distSqr = distSquared(myPos, otherPos);
  float combinedRSqr = sqr<float>(radius + other.radius);

  return (distSqr < combinedRSqr);
}

bool CircleCollider::collidesWith (PointCollider const & other) const
{
  float distSqr = distSquared(absolutePosition.getPosition(),
                              other.getPoint());
  float combinedRSqr = sqr<float>(radius);

  return (distSqr < combinedRSqr);
}

bool CircleCollider::collidesWith (AlignRectCollider const & other) const
{
  sf::Vector2f center = absolutePosition.getPosition();
  sf::FloatRect rect = other.getWorldRect();
  sf::Vector2f closest(
      limitValue<float>(rect.left, center.x, rect.left + rect.width),
      limitValue<float>(rect.top,  center.y, rect.top + rect.height));

  float distSqr = distSquared(center, closest);
  float combinedRSqr = sqr<float>(radius);

  return (distSqr < combinedRSqr);
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
