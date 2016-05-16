#include "circle.hpp"

// Implements a circlular shape.



Circle::Circle(float radius_) :
  Shape(), radius(radius_)
{}

Circle::~Circle ()
{}

// see header
bool Circle::overlaps (Shape const & other) const
{
  return other.overlaps(*this);
}

// Shapes don't store their own coordinates right now.
bool Circle::overlaps (Circle const & other) const
{
  float xDist = other.x - x;
  float yDist = other.y - y;
  float distSqr = xDist * xDist + yDist * yDist;
  float sumR = other.radius + radius;
  return distSqr < sumR * sumR;
}
