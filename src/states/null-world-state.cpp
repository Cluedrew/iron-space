#include "null-world-state.hpp"

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
