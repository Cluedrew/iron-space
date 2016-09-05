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
    default:
      break;
    }
  }
  fin.type = Response::Done;
  return fin;
}

#endif//GEN_EVENT_HANDLER_TPP
