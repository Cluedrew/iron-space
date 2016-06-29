#ifndef GEN_EVENT_HANDLER_TPP
#define GEN_EVENT_HANDLER_TPP

// Implementation of the GenEventHandler Template, a testing tool.

#include <SFML/Window/Event.hpp>

template<typename SourceT>
GenEventHandler<SourceT>::GenEventHandler ()
{}

template<typename SourceT>
GenEventHandler<SourceT>::~GenEventHandler ()
{}

template<typename SourceT>
bool GenEventHandler<SourceT>::pollEvents(SourceT & window)
{
  sf::Event event;
  while (window.pollEvent(event))
  {
    switch (event.type)
    {
    case sf::Event::Closed:
      return false;
    default:
      break;
    }
  }
  return true;
}

#endif//GEN_EVENT_HANDLER_TPP
