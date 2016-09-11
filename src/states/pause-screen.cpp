#include "pause-screen.hpp"

// Implementation of the pause screen.

#include <cassert>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Time.hpp>



sf::Color const pauseTint(0, 0, 0, 127);



PauseScreen::PauseScreen (WorldState * paused) :
    paused(paused)
{
  paused->update(sf::Time::Zero);
}

PauseScreen::~PauseScreen ()
{}

void PauseScreen::transition (WorldState * from)
{}

void PauseScreen::handleInput (InputEvent const & ievent)
{}

void PauseScreen::update (sf::Time const & deltaT)
{}

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
