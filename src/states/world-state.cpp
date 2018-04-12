#include "world-state.hpp"

// Implementation of the World/Global/Game State.



WorldState::WorldState () {}

WorldState::~WorldState () {}

void WorldState::start () {}

WorldState * WorldState::idStart (WorldState * state)
{
  state->start();
  return state;
}
