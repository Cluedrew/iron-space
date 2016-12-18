#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP

/* Types and values for specifing alignment.
 * Alignment is a quick way to give where a objects position should be
 * messured from and is intended for use with GUI objects (ex. menu items).
 */



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

#endif//ALIGNMENT_HPP
