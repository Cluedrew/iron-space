#ifndef CIRCLE_GRAPHICS_HPP
#define CIRCLE_GRAPHICS_HPP

/* Drawable Circle, draws a white circle around the origin with a given radius.
 */

#include <SFML/Graphics/CircleShape.hpp>
#include "graphics-component.hpp"



class CircleGraphics : public GraphicsComponent
{
private:
  sf::CircleShape circle;

protected:
public:
  CircleGraphics (int radius);
  /* Create a white circle with the given radius.
   * Params: Circle's radius in pixels.
   */

  virtual ~CircleGraphics ();

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw this object to target.
   * Params: Mutable refence to target to draw to and the states to effect
   *   the draw, including the tranform of the coordinate space.
   */
};

#endif//CIRCLE_GRAPHICS_HPP
