#include "running-state.hpp"

// Implementation of the World/Global/Game State.

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "../input/input-event.hpp"



RunningState::RunningState () :
  map()
{
  map.emplace(GameObject());
}

RunningState::~RunningState ()
{}



// see header
void RunningState::handleInput (InputEvent const & ievent)
{
  map.handleInput(ievent);
}

// see header
void RunningState::update (sf::Time const & deltaT)
{
  for (Plane::iterator it = map.begin() ; it != map.end() ; ++it)
    it->updateAi(deltaT);
}

// see header
void RunningState::draw (sf::RenderTarget & target,
    sf::RenderStates states) const
{
  target.draw(map);
}
