#ifndef GRAPHICS_COMPONENT_HPP
#define GRAPHICS_COMPONENT_HPP

/* Drawable component.
 *
 * Soon to be an abstract base class.
 */

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>



class GraphicsComponent : public sf::Drawable
{
private:
  sf::CircleShape circle;

protected:
public:
  GraphicsComponent ();
  virtual ~GraphicsComponent ();

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw this object to target.
   * Params: Mutable refence to target to draw to and the states to effect
   *   the draw, including the tranform of the coordinate space.
   */
};

#endif//GRAPHICS_COMPONENT_HPP
