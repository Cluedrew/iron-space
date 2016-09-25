#ifndef WORLD_STATE_HPP
#define WORLD_STATE_HPP

/* A class that repersents the current state of the world. It itself is a
 * state, mantained by the engine. Or will be, the state-machine part of the
 * Engine is not complete yet so there is one non-abstract state for now.
 *
 * There are two points a WorldState can signal a change in state:
 * 1. In handleInput, the current InputEvent is considered handled and all
 *    future events will be passed to the new state. This is for state
 *    changes triggered by input.
 * 2. In update, the returned state is considered up to date and is drawn
 *    for this frame. This is for changes from internal events.
 * In both cases a change in state is signaled by returning a non-null
 * pointer.
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

  virtual WorldState * handleInput (InputEvent const & ievent) = 0;
  /* Handles InputEvents.
   * Params: A reference to the event to be handled.
   * Effect: Input is either handled or discarded.
   * Return: void, unlike most handleInput functions if a WorldState does
   *   not handle an Input Event, it is discarded.
   */

  virtual WorldState * update (sf::Time const & deltaT) = 0;
  /* Updates the World's State depending on the recent input and time passed.
   * Params: A reference to the amount of real time passed.
   * Effect: Move the state forward in time.
   */

  virtual void draw (sf::RenderTarget & target,
      sf::RenderStates states) const = 0;
  /* Draw the world in its current state to the target.
   * Params: The target to draw to and any states to modify the draw.
   * Effect: Draws to screen.
   */
};

#endif//WORLD_STATE_HPP
