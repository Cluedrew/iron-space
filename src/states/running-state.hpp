#ifndef RUNNING_STATE_HPP
#define RUNNING_STATE_HPP

/* Class that repersents the world in its basic running state.
 * Almost all functionality is distributed to the next state.
 */

#include "world-state.hpp"
#include "../plane-drawable.hpp"
#include "../game-object.hpp"



class RunningState : public WorldState
{
private:
  PlaneDrawable<GameObject> map;

protected:
public:
  RunningState ();
  virtual ~RunningState ();



  //static WorldState * start (...);
  /* Possible alternate way to create initial states.
   */

  //void transition (WorldState * from);
  /* Pass this state the previous state.
   */

  WorldState * handleInput (InputEvent const & ievent);
  /* Handles InputEvents.
   * Params: A reference to the event to be handled.
   * Effect: Input is either handled or discarded.
   * Return: void, unlike most handleInput functions if a WorldState does
   *   not handle an Input Event, it is discarded.
   */

  WorldState * update (sf::Time const & deltaT);
  /* Updates the World's State depending on the recent input and time passed.
   * Params: A reference to the amount of real time passed.
   * Effect:
   */

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw the world in its current state to the target.
   * Params: The target to draw to and any states to modify the draw.
   * Effect: Draws to screen.
   */
};

#endif//WORLD_STATE_HPP
