#include "alignment.hpp"

/* Implementation of the alignment helper functions.
 */

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>



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

// see header
float alignedVerticalOrigin (VerticalAlignment alignment, float y)
{
  switch(alignment)
  {
  case VerticalAlignment::Top:
    return 0;
  case VerticalAlignment::Middle:
    return y / 2;
  case VerticalAlignment::Bottom:
  default:
    return y;
  }
}

// see header
float alignedHorizontalOrigin (HorizontalAlignment alignment, float x)
{
  switch (alignment)
  {
  case HorizontalAlignment::Left:
     return 0;
  case HorizontalAlignment::Center:
     return x / 2;
  case HorizontalAlignment::Right:
  default:
     return x;
  };
}

// see header
sf::Vector2f alignedOrigin (Alignment2D alignment, sf::FloatRect xy)
{
  return alignedOrigin(alignment, xy.width, xy.height);
}
sf::Vector2f alignedOrigin (Alignment2D alignment, sf::Vector2f xy)
{
  return alignedOrigin(alignment, xy.x, xy.y);
}
sf::Vector2f alignedOrigin (Alignment2D alignment, float x, float y)
{
  return sf::Vector2f(
      alignedHorizontalOrigin(horizontalAlignmentComponent(alignment), x),
      alignedVerticalOrigin(verticalAlignmentComponent(alignment), y));
}
