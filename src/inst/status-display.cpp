#include "status-display.hpp"

// Implementation of StatusDisplay, game character data output.

#include <SFML/Graphics.hpp>
#include "object/entity.hpp"
#include "ai/null-ai.hpp"
#include "physics/null-physics.hpp"
#include "graphics/null-graphics.hpp"



StatusDisplay::StatusDisplay () :
  Widget(new NullAi(), new NullPhysics(), new NullGraphics())
{}

void StatusDisplay::draw
    (sf::RenderTarget& target, sf::RenderStates states) const
{
  // I think this section, updating the center, will actually have to happen
  // earlier, before the main draw pass while this is mutable.
  if (0 == selection.size())
  {
    // Empty core.
  }
  else if (1 == selection.size())
  {
    // Information about the selected entitiy.
    //display(*selection.front());
  }
  else
  {
    // List of all entities selected.
  }
}

void StatusDisplay::display (Entity const & source)
{
  source.display(*this);
}
