#include "null-world-state.hpp"

// Null Object for WorldState



NullWorldState::NullWorldState () : WorldState() {}

NullWorldState::~NullWorldState () {}

// see header
void NullWorldState::start ()
{}

// see header
WorldState * NullWorldState::handleInput (InputEvent const & ievent)
{
  return this;
}

// see header
WorldState * NullWorldState::update (sf::Time const & deltaT)
{
  return this;
}

// see header
void NullWorldState::draw (sf::RenderTarget & target,
    sf::RenderStates states) const
{}
