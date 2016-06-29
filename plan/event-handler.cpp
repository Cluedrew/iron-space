#include "event-handler.hpp"

// Implementation of the EventHandler.

#include <SFML/Window.hpp>



EventHandler::EventHandler ()
{}

EventHandler::~EventHandler ()
{}

bool EventHandler::pollEvents(sf::Window & window)
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
