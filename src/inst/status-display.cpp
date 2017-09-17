#include "status-display.hpp"

// Implementation of StatusDisplay, game character data output.

#include <SFML/Graphics.hpp>
#include "object/entity.hpp"
#include "ai/null-ai.hpp"
#include "physics/null-physics.hpp"
#include "graphics/null-graphics.hpp"
#include "graphics/font-marc.hpp"
#include "input/input-event.hpp"
#include "inst/text-fragment.hpp"



// The custom made component classes. (Not in the component directories.)

// Switch to AiWrapper?
struct StatusDisplayAi : public AiComponent
{
  void init (GameObject & container)
  {}

  bool handleInput (GameObject & container, InputEvent const & ievent)
  {
    if (InputEvent::Select == ievent.type)
    {
      // Select an icon in the multi-character mode.
    }
    return false;
  }

  void update (GameObject & container, sf::Time const & deltaT)
  {
    // Might use the inner update function.
  }

  void handleCollision (GameObject & container, GameObjectPtr & ptr)
  {
    // Does this ever need to handle any collisions?
  }
};

//class StatusDisplayPhysics : public PhysicsComponent {};
//class StatusDisplayGraphics : public GraphicsComponent {};



StatusDisplay::StatusDisplay () :
  Widget(new NullAi(), new NullPhysics(), new NullGraphics())
{
  //if (!core.create(X, Y)) { ... }
}

//StatusDisplay::~StatusDisplay ()
//{}

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

  core.clear(sf::Color::Black);

  if (0 == selection.size())
  {
    // Empty core.

    delete header;
    header = nullptr;
  }
  else if (1 == selection.size())
  {
    // Information about the selected entitiy.
    Entity const & entity = *selection.front();

    //display(*selection.front());

    TextFragment header(entity.getName(), 10, 10);
    //if (header)
    //  delete header;
    //  header->setText(entity.getName());
    //else
    //  header = new TextFragment(entity.getName(), 10, 10);

    core.draw(*header);
  }
  else
  {
    // List of all entities selected.
    for (Entity const * entity : selection)
    {
      // Tracked each one.
    }
  }

  core.swap();
}
#endif

void StatusDisplay::display (Entity const & source)
{
  source.display(*this);
}
