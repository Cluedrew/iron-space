#include "align-rect-graphics.hpp"

// Implementation of the simple rectanglar shape.

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>



// see header
AlignRectGraphics::AlignRectGraphics (float width, float height) :
  rect(sf::Vector2f(width, height))
{}

AlignRectGraphics::~AlignRectGraphics ()
{}

// see header
void AlignRectGraphics::draw
    (sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(rect, states);
}
