#ifndef GEN_EVENT_HANDLER_TPP
#define GEN_EVENT_HANDLER_TPP

// Implementation of the GenEventHandler Template, a testing tool.

#include <iostream>
#include <SFML/Window/Event.hpp>
#include "response.hpp"
#include "input-event.hpp"
#include "translate-event.hpp"
#include "../states/world-state.hpp"



template<typename SourceT>
GenEventHandler<SourceT>::GenEventHandler ()
{}

template<typename SourceT>
GenEventHandler<SourceT>::~GenEventHandler ()
{}

template<typename SourceT>
bool GenEventHandler<SourceT>::pollEvent
    (SourceT & source, InputEvent & iEvent)
{
  sf::Event sfEvent;
  while (source.pollEvent(sfEvent))
  {
    if (translateEvent(sfEvent, iEvent))
      return true;
  }

  return false;
}

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
