#include "world-machine.hpp"

/* Implementation of the WorldMachine.
 *
 * Most of it is simple enough to inline, but here we
 */

#include <cassert>
#include "world-state.hpp"



// see header
WorldMachine::WorldMachine (WorldState * initialState) :
    currentState(initialState)
{
  assert(nullptr != currentState);
}

WorldMachine::~WorldMachine ()
{
  delete currentState;
}

// see header
void WorldMachine::update (WorldState * nextState)
{
  if (nullptr == nextState) return;

  nextState->transition(currentState);
  currentState = nextState;
}

// see header
void WorldMachine::changeState (WorldState * nextState)
{
  assert(nullptr != nextState);
  assert(currentState != nextState);

  nextState->transition(currentState);
  currentState = nextState;
}

// see header
WorldState * WorldMachine::get ()
{
  return currentState;
}

WorldState const * WorldMachine::get () const
{
  return currentState;
}

// see header
WorldState * WorldMachine::operator-> ()
{
  return currentState;
}

WorldState const * WorldMachine::operator-> () const
{
  return currentState;
}

// see header
WorldState & WorldMachine::operator* ()
{
  return *currentState;
}

WorldState const & WorldMachine::operator* () const
{
  return *currentState;
}

#if 0

/* I wonder if I can avoid giving the pointer out (so it can't be deleted).
 * I'm not entirely sure how useful it will be, but I might implement it
 * just as a learning experiance about argument forwarding and member function
 * pointers.
 */

// equiliant to: this->update(this->get()->func(Args...)
template<typename... Args>
void WorldMachine::callAndTransition
    (WorldState * (*func)(Args/*&&*/...), Args/*&&*/... args)
{
  update(currentState->func(args...));
}

// equiliant to: this->get()->func(args)
template<typename RetType, typename... Args>
RetType WorldMachine::call (RetType (*func)(Args...), Args... args)
{
  return currentState->func(args...);
}

#endif
