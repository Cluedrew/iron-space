#ifndef BUTTON_HPP
#define BUTTON_HPP

/* Button, a game object for the gui.
 *
 * I am exparementing on how this is set up.
 */

#include "../object/widget.hpp"
class Command;



struct Button : public Widget
{
  // TODO: Some control over how it is drawn should be added at some point.
  Button (Command * effect, float x, float y, float w, float h);
  /* Create a new button of given size and effect.
   * Params: A command to be called when the button is clicked
   *   and coordinates for the Button's top left corner and its size.
   */

  Button (Button &&) = default;
};

#endif//BUTTON_HPP
