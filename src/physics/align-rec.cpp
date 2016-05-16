#include "align-rec.hpp"

// Implements the Aligned Rectangle shape.



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

// The shapes currently to not hold the x & y coordinates.
// see header
bool AlignRect::overlaps (AlignRect const & other)
{
  bool xOverLap = (x - halfWidth < other.x + other.halfWidth)
               || (other.x - other.halfWidth < x + halfWidth);
  bool yOverLap = (y - halfHeight < other.y + other.halfHeight)
               || (other.y - other.halfHeight < y + halfHeight);
  return xOverLap && yOverLap;
}

// see header
bool AlignRect::overlaps (Circle const & other)
{
  return;
}
