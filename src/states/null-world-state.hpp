#ifndef NULL_WORLD_STATE_HPP
#define NULL_WORLD_STATE_HPP

/* A world state that does nothing.
 */

#include "world-state.hpp"



class NullWorldState : public WorldState
{
private:
protected:
public:
  NullWorldState ();
  virtual ~NullWorldState ();

  //NullWorldState start ();
  //void transition (WorldState * lastState);


  WorldState * handleInput (InputEvent const & ievent);
  WorldState * update (sf::Time const & deltaT);
  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* See WorldState for purpose.
   * This particular implementations do nothing.
   */
};

#endif//NULL_WORLD_STATE_HPP
