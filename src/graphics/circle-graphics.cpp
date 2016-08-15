#include "circle-graphics.hpp"

#include <SFML/Graphics.hpp>



// see header
CircleGraphics::CircleGraphics (int radius) :
  circle(radius)
{
  circle.setOrigin(radius, radius);
}

CircleGraphics::~CircleGraphics ()
{}

// see header
void CircleGraphics::draw
    (sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(circle, states);
}
