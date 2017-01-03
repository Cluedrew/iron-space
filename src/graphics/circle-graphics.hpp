#ifndef CIRCLE_GRAPHICS_HPP
#define CIRCLE_GRAPHICS_HPP

/* Drawable Circle, draws a white circle around the origin with a given radius.
 */

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include "graphics-component.hpp"



class CircleGraphics : public GraphicsComponent
{
private:
  sf::CircleShape circle;

protected:
public:
  CircleGraphics (int radius, sf::Color const & colour = sf::Color::White);
  /* Create a white circle with the given radius.
   * Params: Circle's radius in pixels.
   */

  virtual ~CircleGraphics ();

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw this object to target.
   * Params: Mutable refence to target to draw to and the states to effect
   *   the draw, including the tranform of the coordinate space.
   */

  void setColour (sf::Color const & newColour);
  /* Set the circle's colour (outline and fill).
   * Params: The new colour that the circle will be drawn in.
   * Effect: Later calls to draw will show the circle in a different color.
   */
};

#endif//CIRCLE_GRAPHICS_HPP
