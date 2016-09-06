#ifndef WORLD_MACHINE_HPP
#define WORLD_MACHINE_HPP

/* The WorldMachine is a state-machine for WorldState and its child-classes.
 *
 * It encapsulates a single operation on a single field. It can be also used
 * as a pointer to its internal state (do not delete the interal state).
 *
 * Everything is inline just because I was writing my thoughts here.
 * There is some cleanup TODO.
 */

#include <cassert>
class WorldState;
#include "world-state.hpp"



class WorldMachine
{
private:
  WorldState * currentState;

protected:
public:
  WorldMachine (WorldState * initialState) :
      currentState(initialState)
  /* Create a World(State)Machine with the current state
   * Params: A non-null pointer to a dynamically allocated state.
   */
  {
    assert(nullptr != currentState);
  }

  ~WorldMachine ()
  {
    delete currentState;
  }

  void update (WorldState * nextState)
  /* Update the current state.
   * Params: Pointer to state to transition too (must not be equal to
   *   currentState) or nullptr.
   * Effect: If nextState is nullptr, no effects. Otherwise transitions from
   *   the currentState to the nextState.
   */
  {
    if (nullptr == nextState) return;

    nextState->transition(currentState);
    currentState = nextState;
  }

  WorldState * get ()
  {
    return currentState;
  }

  WorldState * operator-> ()
  {
    return currentState;
  }

  WorldState & operator* ()
  {
    return *currentState;
  }

  /* short form for this->update(this->get()->X(Args...)
  template<typename... Args>
  void callAndTransition (WorldState * func(Args...), Args... args)
  {
    update(currentState->func(args...));
  }
  */
};

#endif//WORLD_MACHINE_HPP
