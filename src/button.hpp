#ifndef BUTTON_HPP
#define BUTTON_HPP

/* Button, a game object for the gui.
 *
 * I am exparementing on how this is set up.
 */

#include "game-object.hpp"
class Command;



struct Button : public GameObject
{
  Button (Command * effect, float x, float y, float w, float h);
  /* Create a new button of given size and effect.
   * Params: <something to show what happens when you click it>
   *         <something about how you draw it>
   * and coordinates for the Button's top left corner and its size.
   *         <x & y are ignored>
   */

  Button (Button &&) = default;
};

#endif//BUTTON_HPP
