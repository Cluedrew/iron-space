#ifndef PAUSE_SCREEN_HPP
#define PAUSE_SCREEN_HPP

/* The PauseScreen is a WorldState that repersents the game while paused.
 * It showed the world in its paused state.
 */

#include "world-state.hpp"



class PauseScreen : public WorldState
{
private:
  WorldState * paused;
  bool unpause;

protected:
public:
  PauseScreen (WorldState * paused);
  /* Create a PauseScreen state, from the paused state.
   * Params: Non-null pointer to state being paused.
   */

  virtual ~PauseScreen ();

  WorldState * handleInput (InputEvent const & ievent);
  /* Handle InputEvents.
   * Params: Reference to the state being handled.
   * Effect: Handles input.
   */

  WorldState * update (sf::Time const & deltaT);
  /* Update the pause screen. Very little happens here.
   * Params: A reference to the amount of real time passed.
   * Effect: Move the state forward in time.
   */

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw the paused screen.
   * Params: The target to draw to and any states to modify the draw.
   * Effect: Draws to screen.
   */
};

#endif//PAUSE_SCREEN_HPP
