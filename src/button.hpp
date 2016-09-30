#ifndef BUTTON_HPP
#define BUTTON_HPP

/* Button, a game object for the gui.
 *
 * I am exparementing on how this is set up.
 */

#include "game-object.hpp"



/* Command, here I am using it to delay an action, you pass in a command
 * to the Button and it runs the command when it is ready. Action->no undo?
 * This will be moved into its own space eventually.
 */

struct Command
{
  Command ();
  virtual ~Command ();

  virtual void operator() () =0;
};


struct Button : public GameObject
{
  Button (Command * effect, float x, float y, float w, float h);
  /* Create a new button of given size and effect.
   * Params: <something to show what happens when you click it>
   *         <something about how you draw it>
   * and coordinates for the Button's top left corner and its size.
   */
};

#endif//BUTTON_HPP
