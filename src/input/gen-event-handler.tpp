#ifndef GEN_EVENT_HANDLER_TPP
#define GEN_EVENT_HANDLER_TPP

// Implementation of the GenEventHandler Template, a testing tool.

#include <iostream>
#include <SFML/Window/Event.hpp>
#include "response.hpp"
#include "input-event.hpp"
#include "../states/world-state.hpp"



template<typename SourceT>
GenEventHandler<SourceT>::GenEventHandler ()
{}

template<typename SourceT>
GenEventHandler<SourceT>::~GenEventHandler ()
{}

/* TODO
1. I need to be able to get the state change signal out of this class and
   back to the caller (Engine/test code).
2. Consider moving the sf::Event -> InputEvent translation logic out of
   the template and into some universal code.

void GenEventTranslator::translate
    (sf::Event sfEvent, InputEvent iEvent)

template<typename SourceT>
bool GenEventHandler<SourceT>::pollEvents
    (SourceT & source, WorldMachine & machine)

*/

template<typename SourceT>
Response GenEventHandler<SourceT>::pollEvents
    (SourceT & window, WorldState & state)
{
  sf::Event event;

  Response fin;

  while (window.pollEvent(event))
  {
    switch (event.type)
    {
    case sf::Event::Closed:
      fin.type = Response::Quit;
      return fin;
    case sf::Event::MouseButtonPressed:
      InputEvent ievent;
      ievent.type = InputEvent::Select;
      ievent.pos.x = event.mouseButton.x;
      ievent.pos.y = event.mouseButton.y;
      state.handleInput(ievent);
      break;
    case sf::Event::KeyPressed:
      if (sf::Keyboard::Key::Space == event.key.code)
      {
        InputEvent ievent;
        ievent.type = InputEvent::Pause;
        state.handleInput(ievent);
      }
      break;
    //case sf::Event::KeyReleased:
    default:
      break;
    }
  }
  fin.type = Response::Done;
  return fin;
}

#endif//GEN_EVENT_HANDLER_TPP
