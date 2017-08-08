#include "world-state.hpp"

// Implementation of the World/Global/Game State.

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "input/input-event.hpp"



WorldState::WorldState () {}

WorldState::~WorldState () {}

void WorldState::start () {}

WorldState * WorldState::idStart (WorldState * state)
{
  state->start();
  return state;
}
