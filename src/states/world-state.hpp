#ifndef WORLD_STATE_HPP
#define WORLD_STATE_HPP

/* A class that repersents the current state of the world. It itself is a
 * state, mantained by the engine. Or will be, the state-machine part of the
 * Engine is not complete yet so there is one non-abstract state for now.
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



  //static WorldState * start (...);
  /* Possible alternate way to create initial states.
   */

  virtual void transition (WorldState * from);
  /* Transition from the previous state to this one.
   * Params: Pointer to privious state. (nullptr for initial state?)
   * Effect: Exits from the old state and enters the new one.
   *   Default is simply to free the old state as it is no longer needed.
   */

  virtual void handleInput (InputEvent const & ievent) = 0;
  /* Handles InputEvents.
   * Params: A reference to the event to be handled.
   * Effect: Input is either handled or discarded.
   * Return: void, unlike most handleInput functions if a WorldState does
   *   not handle an Input Event, it is discarded.
   */

  virtual void update (sf::Time const & deltaT) = 0;
  /* Updates the World's State depending on the recent input and time passed.
   * Params: A reference to the amount of real time passed.
   * Effect:
   */

  virtual void draw (sf::RenderTarget & target,
      sf::RenderStates states) const = 0;
  /* Draw the world in its current state to the target.
   * Params: The target to draw to and any states to modify the draw.
   * Effect: Draws to screen.
   */
};

#endif//WORLD_STATE_HPP
