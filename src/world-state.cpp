#include "world-state.hpp"

// Implementation of the World/Global/Game State.

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "input/input-event.hpp"



WorldState::WorldState () :
  map()
{
  map.insert(GameObject());
}

WorldState::~WorldState ()
{}



// see header
void WorldState::handleInput (InputEvent const & ievent)
{
  map.handleInput(ievent);
}

// see header
void WorldState::update (sf::Time const & deltaT)
{}

// see header
void WorldState::draw (sf::RenderTarget & target,
    sf::RenderStates states) const
{
  target.draw(map);
}

#if 0
// Null Object for WorldState

NullWorldState::NullWorldState () : WorldState() {}

NullWorldState::~NullWorldState () {}

// see header
void NullWorldState::handleInput (InputEvent const & ievent)
{}

// see header
void NullWorldState::update (sf::Time const & deltaT)
{}

// see header
void NullWorldState::draw (sf::RenderTarget & target,
    sf::RenderStates states) const
{}
#endif
