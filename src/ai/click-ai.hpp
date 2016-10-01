#ifndef CLICK_AI_HPP
#define CLICK_AI_HPP

/* AI that takes no action on update. However it will call the command passed
 * to its constructor every time it is "selected".
 */

#include "ai-component.hpp"
// Until I seperate out the Command class.
#include "../util/command.hpp"



class ClickAi : public AiComponent
{
private:
  Command * onSelect;

protected:
public:
  ClickAi (Command * onSelect);
  /* Create an ai that reacts when it is selected by running the command.
   * Params: Pointer to Command, ClickAi takes ownership of the Command.
   */

  virtual ~ClickAi ();

  virtual void init (GameObject & container);
  /* Called once by the GameObject's constructor to complete set up.
   * Params: Mutable reference to the containing GameObject.
   * Effect: Complete the Ai's set up and any set it does for the
   *   GameObject.
   */

  virtual bool
  handleInput (GameObject & container, InputEvent const & ievent);
  /* Handle input event that was given to the GameObject.
   * Params: Mutable reference to the containing GameObject.
   *   A reference to the InputEvent that was recived.
   * Effect: Change state according to input.
   * Return: True if the input was handled, false if it was not caught.
   */

  virtual void update (GameObject & container, sf::Time const & deltaT);
  /* Update the GameObject for the passing time.
   * Params: Mutable reference to the containing GameObject.
   *   The amount of time that has passed.
   * Effect: Update the GameObject and the Ai.
   */
};

#endif//CLICK_AI_HPP
