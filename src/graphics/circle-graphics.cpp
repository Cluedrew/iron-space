#include "circle-graphics.hpp"

#include <SFML/Graphics.hpp>



// see header
CircleGraphics::CircleGraphics (int radius, sf::Color const & colour) :
  circle(radius)
{
  circle.setOrigin(radius, radius);
  circle.setFillColor(colour);
  circle.setOutlineColor(colour);
}

CircleGraphics::~CircleGraphics ()
{}

// see header
void CircleGraphics::draw
    (sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(circle, states);
}

// see header
void CircleGraphics::setColour (sf::Color const & newColour)
{
  circle.setFillColor(newColour);
  circle.setOutlineColor(newColour);
}
