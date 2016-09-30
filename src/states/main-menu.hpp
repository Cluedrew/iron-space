#ifndef MAIN_MENU_HPP
#define MAIN_MENU_HPP

/* WorldState for the MainMenu. The game menu before you start playing the
 * game itself.
 */

#include "world-state.hpp"
#include "../plane-drawable.hpp"
#include "../game-object.hpp"



class MainMenu : public WorldState
{
private:
  PlaneDrawable<GameObject> gui;

protected:
public:
  MainMenu ();
  virtual ~MainMenu ();

  WorldState * handleInput (InputEvent const & ievent);
  /* Handles incoming InputEvents.
   * Implements WorldState::handleInput
   */

  WorldState * update (sf::Time const & deltaT);
  /* Update the MainMenu to show change in time.
   * Implements WorldState::update
   */

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw the world in its current state to the target.
   * Implements WorldState::draw
   */
};

#endif//MAIN_MENU_HPP
