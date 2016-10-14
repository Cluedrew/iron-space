#ifndef NULL_GRAPHICS_HPP
#define NULL_GRAPHICS_HPP

/* Null Object for the GraphicsComponent.
 * WIP
 */

#include "graphics-component.hpp"



class NullGraphics : public GraphicsComponent
{
private:
protected:
public:
  virtual ~NullGraphics () {}

  void draw (sf::RenderTarget & target, sf::RenderStates states) const {}
  /* Draws nothing.
   * Params: Doesn't matter.
   */
};

#endif//NULL_GRAPHICS_HPP
