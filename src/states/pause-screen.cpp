#include "pause-screen.hpp"

// Implementation of the pause screen.

#include <cassert>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>
#include "../input/input-event.hpp"



static sf::Color const pauseTint(0, 0, 0, 127);



PauseScreen::PauseScreen (WorldState * paused) :
    paused(paused), unpause(false)
{
  paused->update(sf::Time::Zero);
}

PauseScreen::~PauseScreen ()
{}

void PauseScreen::transition (WorldState * from)
{}

WorldState * PauseScreen::handleInput (InputEvent const & ievent)
{
  if (InputEvent::Pause == ievent.type)
    unpause = true;
  return nullptr;
}

WorldState * PauseScreen::update (sf::Time const & deltaT)
{
  if (unpause)
  {
    // TODO: Should this be valid? paused:=this->paused
    //WorldState * fin = paused;
    delete(this);
    //return fin;
    return paused;
  }
  else
    return nullptr;
}

static void fill (sf::RenderTarget & target, sf::RenderStates states,
                  sf::Color colour)
{
  sf::RectangleShape targetRect(sf::Vector2f(target.getSize()));
  targetRect.setFillColor(colour);
  target.draw(targetRect, states);
}

void PauseScreen::draw (sf::RenderTarget & target,
                        sf::RenderStates states) const
{
  target.draw(*paused, states);
  fill(target, states, pauseTint);
}
