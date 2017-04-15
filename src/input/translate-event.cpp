#include "translate-event.hpp"

// Implementation of translateEvent.

#include <SFML/Window/Event.hpp>
#include "input-event.hpp"


bool translateEvent (sf::Event const & sfEvent, InputEvent & iEvent)
{
  switch (sfEvent.type)
  {
  case sf::Event::Closed:
    iEvent.type = InputEvent::Quit;
    return true;

  case sf::Event::MouseButtonPressed:
    iEvent.type = InputEvent::Select;
    iEvent.pos.x = sfEvent.mouseButton.x;
    iEvent.pos.y = sfEvent.mouseButton.y;
    return true;

  case sf::Event::KeyPressed:
    if (sf::Keyboard::Key::Space == sfEvent.key.code)
    {
      iEvent.type = InputEvent::Pause;
      return true;
    }

  default:
    return false;
  }
}
