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
Response GenEventHandler<SourceT>::pollEvents(SourceT & window)
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
    default:
      break;
    }
  }
  fin.type = Response::Done;
  return fin;
}

#endif//GEN_EVENT_HANDLER_TPP
