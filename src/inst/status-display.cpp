#include "status-display.hpp"

// Implementation of StatusDisplay, game character data output.

#include <SFML/Graphics.hpp>
#include "object/entity.hpp"
#include "ai/null-ai.hpp"
#include "physics/null-physics.hpp"
#include "graphics/null-graphics.hpp"



StatusDisplay::StatusDisplay () :
  Widget(new NullAi(), new NullPhysics(), new NullGraphics())
{
  //if (!core.create(X, Y)) { ... }
}

void StatusDisplay::draw
    (sf::RenderTarget& target, sf::RenderStates states) const
{
  const sf::Texture & texture = core.getTexture();
  sf::Sprite sprite(texture);
  target.draw(sprite, states);
}

#if 0
// I'm not sure where this goes, but I think we need it somewhere.
void StatusDisplay::update ( ??? )
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
    for (Entity const * entity : selection)
    {
      // Tracked each one.
    }
  }
}
#endif

void StatusDisplay::display (Entity const & source)
{
  source.display(*this);
}
