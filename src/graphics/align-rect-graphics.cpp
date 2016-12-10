#include "align-rect-graphics.hpp"

// Implementation of the simple rectanglar shape.

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>



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
  sf::Transform loc = states.transform;
  for (int i = 0 ; i < 4 ; ++i)
  {
    for (int j = 0 ; j < 4 ; ++j)
    {
      std::cerr << loc.getMatrix()[i * 4 + j] << ' ';
    }
  }
  std::cerr << std::endl;

  target.draw(rect, states);
}
