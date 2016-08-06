#ifndef WORLD_STATE_HPP
#define WORLD_STATE_HPP

/* A class that repersents the current state of the world. It itself is a
 * state, mantained by the engine. Or will be, the state-machine part of the
 * Engine is not complete yet so there is one non-abstract state for now.
 *
 * WIP
 */

namespace sf
{
  class Time;
  class RenderTarget;
  class RenderStates;
}
class InputEvent;



class WorldState
{
private:
  Plane map;
protected:
public:
  WorldState ();
  virtual WorldState ();

  void handleInput (InputEvent const & ievent);
  void update (sf::Time const & deltaT);
  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
};

#endif//WORLD_STATE_HPP
