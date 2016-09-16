#include "null-world-state.hpp"

// Null Object for WorldState



NullWorldState::NullWorldState () : WorldState() {}

NullWorldState::~NullWorldState () {}

// see header
WorldState * NullWorldState::handleInput (InputEvent const & ievent)
{
  return nullptr;
}

// see header
WorldState * NullWorldState::update (sf::Time const & deltaT)
{
  return nullptr;
}

// see header
void NullWorldState::draw (sf::RenderTarget & target,
    sf::RenderStates states) const
{}
