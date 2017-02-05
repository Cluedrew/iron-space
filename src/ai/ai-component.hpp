#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

/* The component that does the thinking.
 * Currently there is only one Component at all, later it should be a base
 * class for all the different blocks of AI.
 *
 * Soon to be an abstract base class.
 */

namespace sf { class Time; }
class GameObject;
class InputEvent;
class GameObjectPtr;



class AiComponent
{
private:
protected:
public:
  virtual ~AiComponent () {};

  virtual void init (GameObject & container) = 0;
  /* Called once by the GameObject's constructor to complete set up.
   * Params: Mutable reference to the containing GameObject.
   * Effect: Complete the Ai's set up and any set it does for the
   *   GameObject.
   */

  virtual bool
  handleInput (GameObject & container, InputEvent const & ievent) = 0;
  /* Handle input event that was given to the GameObject.
   * Params: Mutable reference to the containing GameObject.
   *   A reference to the InputEvent that was recived.
   * Effect: Change state according to input.
   * Return: True if the input was handled, false if it was not caught.
   */

  virtual void update (GameObject & container, sf::Time const & deltaT) = 0;
  /* Update the GameObject for the passing time.
   * Params: Mutable reference to the containing GameObject.
   *   The amount of time that has passed.
   * Effect: Update the GameObject and the Ai.
   */

#if 0
  // Functions that probably going to be added and I would like to keep in
  // mind.

  virtual void handleMessage (Message & msg) = 0;
  /* Handle a message from another GameObject.
   * Params: Mutable reference to the Message.
   * Effect: Default is nothing, may be overridden.
   *
   * Add overloads for sub-classes of Message, so that sub-classes of
   * AIComponent can selectively overide for different message types.
   */
#endif

  virtual void handleCollision (
    GameObject & container, GameObjectPtr & ptr) {} //= 0;
  /* Handle a collision with another GameObject.
   * Params: Reference to container. Mutable reference to a GameObjectPtr +.
   * Effect: Default is nothing, may be overridden.
   *
   * + If we can garenty the timing of deletes than this could just be a
   *   reference to the GameObject itself.
   */
};

#endif//AI_COMPONENT_HPP
