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
#include "plane.hpp"



class WorldState : public sf::Drawable
{
private:
  Plane map;

protected:
public:
  WorldState ();
  virtual ~WorldState ();

  void handleInput (InputEvent const & ievent);
  /* Handles InputEvents.
   * Params: A reference to the event to be handled.
   * Effect: Input is either handled or discarded.
   * Return: void, unlike most handleInput functions if a WorldState does
   *   not handle an Input Event, it is discarded.
   */

  void update (sf::Time const & deltaT);
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
