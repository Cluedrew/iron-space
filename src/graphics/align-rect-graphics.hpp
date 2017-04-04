#ifndef ALIGN_RECT_GRAPHICS_HPP
#define ALIGN_RECT_GRAPHICS_HPP

/* Drawable rectangle, specified in terms of size. It is always is aligned
 * with the axis. And is drawn from its upper right corner.
 */

#include <SFML/Graphics/RectangleShape.hpp>
#include "graphics-component.hpp"



class AlignRectGraphics : public GraphicsComponent
{
private:
  sf::RectangleShape rect;

protected:
public:
  AlignRectGraphics (float width, float height);
  /* Create a white rectangle.
   * Params: The rectangle's width & height in pixels.
   */

  virtual ~AlignRectGraphics ();

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw this object to target.
   * Params: Mutable refence to target to draw to and the states to effect
   *   the draw, including the tranform of the coordinate space.
   */
};

#endif//ALIGN_RECT_GRAPHICS_HPP
