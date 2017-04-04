#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP

/* Types and values for specifing alignment.
 * Alignment is a quick way to give where a objects position should be
 * messured from and is intended for use with GUI objects (ex. menu items).
 */

namespace sf
{
  template<typename T> class Vector2;
  template<typename T> class Rect;
}



enum class VerticalAlignment : char
{
  Top,
  Middle,
  Bottom,
};

enum class HorizontalAlignment : char
{
  Left,
  Center,
  Right,
};

enum class Alignment2D : char
{
  TopLeft,
  TopCenter,
  TopRight,
  MiddleLeft,
  MiddleCenter,
  MiddleRight,
  BottomLeft,
  BottomCenter,
  BottomRight,
};



Alignment2D crossAlign (VerticalAlignment, HorizontalAlignment);
/* Combine alignment on the two axis.
 */

VerticalAlignment verticalAlignmentComponent (Alignment2D);
HorizontalAlignment horizontalAlignmentComponent (Alignment2D);
/* Get the vertical/horizontal component of an Alignment2D.
 */

void alignVertically (Alignment2D &, VerticalAlignment);
void alignHorizontally (Alignment2D &, HorizontalAlignment);
/* Change one of the components of a Alignment2D.
 * target = crossAlign(VerticalAlignmentComponent(target), _)
 * target = crossAlign(_, HorizontallyAlignmentComponent(target))
 */

float alignedVerticalOrigin (VerticalAlignment, float y);
/* Calculate an object's origin so it matches the given alignment.
 * Params: The VerticalAlignment and vertical size of the object.
 * Return: 0, y/2 or y.
 */

float alignedHorizontalOrigin (HorizontalAlignment, float x);
/* Calculate an object's origin so it matches the given alignment.
 * Params: The HorizontalOrigin and horizontal size of the object.
 * Return: 0, x/2 or x.
 */

sf::Vector2<float> alignedOrigin (Alignment2D, sf::Rect<float> xy);
sf::Vector2<float> alignedOrigin (Alignment2D, sf::Vector2<float> xy);
sf::Vector2<float> alignedOrigin (Alignment2D, float x, float y);
/* Calculate an object's origin so it matches the given alignment.
 * Params: The Alignment2D (vertical and horizontal alignment) and size of
 *   the object.
 * Return: Vector containing the two 1D alignments.
 */

#endif//ALIGNMENT_HPP
