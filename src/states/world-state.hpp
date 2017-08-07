#ifndef WORLD_STATE_HPP
#define WORLD_STATE_HPP

/* A class that repersents the current state of the world. It itself is a
 * state, mantained by the engine.
 *
 * Those functions that return a WorldStart pointer: handleInput & update,
 * return a pointer to the next state. If there is a no change in state than
 * the function should return this. DO NOT return null.
 *
 * When a WorldState signals a change in state it is responsible for cleaning
 * up its memory. Generally this means a delete(this) right before returning
 * a pointer to the new state or passing the current state as an argument to
 * the new state which then assumes responsibility.
 */

#include <SFML/Graphics/Drawable.hpp>
namespace sf
{
  class Time;
  class RenderTarget;
  class RenderStates;
}
class InputEvent;



class WorldState : public sf::Drawable
{
private:
protected:
public:
  WorldState ();
  virtual ~WorldState ();

  //virtual void start() = 0;
  /* Call start before putting the class into the main loop. Starts or
   *   restarts the state.
   * Effect: Dependant on overload.
   */

  virtual WorldState * handleInput (InputEvent const & ievent) = 0;
  /* Handles InputEvents.
   * Params: A reference to the event to be handled.
   * Effect: Input is either handled or discarded.
   * Return: Pointer to next state. The input given in this call is considered
   *   to be handled. See file doc for details.
   */

  virtual WorldState * update (sf::Time const & deltaT) = 0;
  /* Updates the World's State depending on the recent input and time passed.
   * Params: A reference to the amount of real time passed.
   * Effect: Move the state forward in time.
   * Return: Pointer to next state. It is up to date with the end of the time
   *   deltaT. See file doc for details.
   */

  virtual void draw (sf::RenderTarget & target,
      sf::RenderStates states) const = 0;
  /* Draw the world in its current state to the target.
   * Params: The target to draw to and any states to modify the draw.
   * Effect: Draws to screen.
   */
};

#endif//WORLD_STATE_HPP
