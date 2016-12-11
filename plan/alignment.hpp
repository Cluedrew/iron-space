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



#endif//ALIGNMENT_HPP
