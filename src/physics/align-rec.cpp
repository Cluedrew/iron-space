#include "align-rec.hpp"

// Implements the Aligned Rectangle shape.

#include "../util/math.hpp"



AlignRect::AlignRect(float halfWidth_, float halfHeight_) :
  halfWidth(halfWidth_), halfHeight(halfHeight_)
{}

AlignRect::~AlignRect ()
{}

// see header
bool AlignRect::overlaps (Shape const & other)
{
  return other.overlaps(*this);
}

// ! The shapes currently to not hold the x & y coordinates.
bool AlignRect::overlaps (AlignRect const & other)
{
  bool xOverLap = (x - halfWidth < other.x + other.halfWidth)
               || (other.x - other.halfWidth < x + halfWidth);
  bool yOverLap = (y - halfHeight < other.y + other.halfHeight)
               || (other.y - other.halfHeight < y + halfHeight);
  return xOverLap && yOverLap;
}

// ! And this class can't access circle's radius.
bool AlignRect::overlaps (Circle const & other)
{
  float xClosest = limitValue<float>(x - halfWidth, other.x, x + halfWidth);
  float yClosest = limitValue<float>(y - halfHeight, other.y, y + halfHeight);
  float xDist = diff<float>(xClosest, other.x);
  float yDist = diff<float>(yClosest, other.y);
  return sqr(xDist) + sqr(yDist) < sqr(other.radius);
  // ! Possible fix, but still dependent on how locations is stored.
  // Circle closestPoint(xClosest, yClosest, 0);
  // return closestPoint.overlaps(other);
}
