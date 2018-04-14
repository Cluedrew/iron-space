#include "status-display.hpp"

// Implementation of StatusDisplay, game character data output.

#include <iostream>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include "object/entity.hpp"
#include "core/interface.hpp"
#include "ai/null-ai.hpp"
#include "physics/null-physics.hpp"
#include "graphics/null-graphics.hpp"
#include "graphics/font-marc.hpp"
#include "input/input-event.hpp"
#include "inst/text-fragment.hpp"
#include "util/except.hpp"



// The custom made component classes. (Not in the component directories.)

/* Prehaps I should switch to AiWrapper and use:
 * bool innerHandleInput (InputEvent const & input);
 * void innerUpdateAi (sf::Time const & deltaT);
 * void innerHandleCollision (GameObjectPtr & with);
 */
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
    StatusDisplay * display = dynamic_cast<StatusDisplay *>(&container);
    if (!display)
      throw GameFault("StatusDisplayAi not on StatusDisplay.");

    // Internal State updates.

    // Update core for drawing.
    display->updateCore(deltaT);
  }

  void handleCollision (GameObject & container, GameObjectPtr & ptr)
  {
    // Clicks and hovers on the items displayed in status.
  }
};

//class StatusDisplayPhysics : public PhysicsComponent {};

class StatusDisplayGraphics : public GraphicsComponent
{
public:
  const sf::Texture * texture;
private:
  void draw (sf::RenderTarget& target, sf::RenderStates states) const
  {
    sf::Sprite toDraw(*texture);

    sf::Vector2u drawSize = texture->getSize();
    toDraw.setOrigin(drawSize.x / 2, drawSize.y);

    sf::Vector2u targetSize = target.getSize();
    toDraw.setPosition(targetSize.x / 2, targetSize.y);

    target.draw(toDraw, states);
  }

public:
  StatusDisplayGraphics() :
      texture(nullptr)
  {}
};



StatusDisplay::StatusDisplay () :
  Widget(new StatusDisplayAi(),
         new NullPhysics(),
         new StatusDisplayGraphics())
{
  if (!core.create(200, 100))
  {
    throw GameFault("Could not create StatusDisplay Texture.");
  }

  StatusDisplayGraphics * g = getCastGraphics<StatusDisplayGraphics>();
  if (!g)
  {
    throw GameFault("The type of StatusDisplay's graphics changed.");
  }
  g->texture = &core.getTexture();
}

// Internal function for updating the image on core.
void StatusDisplay::updateCore (sf::Time const & deltaT)
{
  core.clear(sf::Color::Black);

  {
    //sf::Vector2f size = core.getSize();
    sf::RectangleShape frame(sf::Vector2f(core.getSize()));
    frame.setFillColor(sf::Color::Transparent);
    frame.setOutlineColor(sf::Color::Cyan);
    frame.setOutlineThickness(-3);
    core.draw(frame);
  }

  // Copy all the currently stored entities.
  std::vector<Entity *> selection(
    interface.selectBegin(), interface.selectEnd());

  if (0 == selection.size())
  {
    // Empty core.
  }
  else if (1 == selection.size())
  {
    // Information about the selected entitiy.
    Entity const & entity = *selection.front();

    // TODO: Consider TextGraphics, similar use but less overhead (all uses).
    TextFragment header(entity.getName(), 10, 10);

    core.draw(header);

    display(*selection.front());
  }
  else
  {
    // List of all entities selected.
    //for (Entity const * entity : selection)
    //{
      // Display just a little bit of information on each one.
    //}

    std::string title("Entity Objects Selected: ");
    title + std::to_string(selection.size());
    TextFragment header(title, 10, 10);

    core.draw(header);
  }
}

void StatusDisplay::display (Entity const & source)
{
  // Reset all display parameters.
  numStatusBars = 0;

  // Manual drawing of the consistant elements.
  // ...

  // Call backs for the rest.
  source.display(*this);
}

// Call backs
void StatusDisplay::drawStatusBar(
    std::string const & name, sf::Color const & color,
    unsigned int max, unsigned int current)
{
  /*sf::Vector2f basePos(20, 20);
  sf::Vector2f offset(0, 10);
  float nsb = numStatusBars;
  sf::Vector2f barPos = basePos + [nsb|numStatusBars] * offset; */

  // Update number of status bars.
  ++numStatusBars;
}
