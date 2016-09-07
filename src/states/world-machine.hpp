#ifndef WORLD_MACHINE_HPP
#define WORLD_MACHINE_HPP

/* The WorldMachine is a state-machine for WorldState and its child-classes.
 *
 * It encapsulates a single operation on a single field. It can be also used
 * as a pointer to its internal state. Do not delete the interal state, you
 * can change it but the WorldMachine will maintain its own non-NULL pointer
 * to the object, to help make sure the operations are always valid.
 */

class WorldState;



class WorldMachine
{
private:
  WorldState * currentState;

protected:
public:
  WorldMachine (WorldState * initialState);
  /* Create a World(State)Machine with the current state
   * Params: A non-null pointer to a dynamically allocated state.
   */

  ~WorldMachine ();

  void update (WorldState * nextState);
  /* Update the current state.
   * Params: Pointer to state to transition too (must not be equal to
   *   currentState) or nullptr.
   * Effect: If nextState is nullptr, no effects. Otherwise transitions from
   *   the currentState to the nextState.
   */

  void changeState (WorldState * nextState);
  /* Change from the current state to the nextState.
   * Params: Pointer to the nextState, must not be null or equal to the
   *   currentState.
   * Effect: nextState becomes the currentState.
   */

  WorldState * get ();
  WorldState const * get () const;
  /* Access the internal state.
   * Return: Pointer to the current state.
   */

  WorldState * operator-> ();
  WorldState const * operator-> () const;
  /* Access a member of the internal state of the state machine.
   * Return: Pointer to the current state.
   */

  WorldState & operator* ();
  WorldState const & operator* () const;
  /* Deference operator, get a reference to the internal state.
   * Return: Reference to the current state.
   */
};

#endif//WORLD_MACHINE_HPP
