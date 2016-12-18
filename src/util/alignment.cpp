#include "alignment.hpp"

/* Implementation of the alignment helper functions.
 */



// see header
Alignment2D crossAlign (VerticalAlignment v, HorizontalAlignment h)
{
  return Alignment2D(char(v) * 3 + char(h));
}

// see header
VerticalAlignment verticalAlignmentComponent (Alignment2D a)
{
  return VerticalAlignment(char(a) / 3);
}

// see header
HorizontalAlignment horizontalAlignmentComponent (Alignment2D a)
{
  return HorizontalAlignment(char(a) % 3);
}

// see header
void alignVertically (Alignment2D & a, VerticalAlignment v)
{
  a = crossAlign(v, horizontalAlignmentComponent(a));
}

// see header
void alignHorizontally (Alignment2D & a, HorizontalAlignment h)
{
  a = crossAlign(verticalAlignmentComponent(a), h);
}
