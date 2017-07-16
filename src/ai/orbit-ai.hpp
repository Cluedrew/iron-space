#ifndef ORBIT_AI_HPP
#define ORBIT_AI_HPP

/* The component that does the thinking.
 * Currently there is only one Component at all, later it should be a base
 * class for all the different blocks of AI.
 *
 * Soon to be an abstract base class.
 */


#include <SFML/System/Time.hpp>
#include "ai-component.hpp"
class GameObject;
class InputEvent;



class OrbitAi : public AiComponent
{
private:
  sf::Time progress;
  bool moving;
  int xCenter;
  int yCenter;
  int radius;

protected:
public:
  OrbitAi ();

  OrbitAi (int xCenter, int yCenter, int radius);

  virtual ~OrbitAi ();

  void init (GameObject & container);
  /* Called once by the GameObject's constructor to complete set up.
   * Params: Mutable reference to the containing GameObject.
   * Effect: Complete the Ai's set up and any set it does for the
   *   GameObject.
   */

  bool handleInput (GameObject & container, InputEvent const & ievent);
  /* Handle input event that was given to the GameObject.
   * Params: Mutable reference to the containing GameObject.
   *   A reference to the InputEvent that was recived.
   * Effect: Change state according to input.
   * Return: True if the input was handled, false if it was not caught.
   */

  void update (GameObject & container, sf::Time const & deltaT);
  /* Update the GameObject for the passing time.
   * Params: Mutable reference to the containing GameObject.
   *   The amount of time that has passed.
   * Effect: Update the GameObject and the Ai.
   */

#if 0
  // Functions that probably going to be added and I would like to keep in
  // mind.

  void handleMessage (Message & msg);
  /* Handle a message from another GameObject.
   * Params: Mutable reference to the Message.
   * Effect: Default is nothing, may be overridden.
   *
   * Add overloads for sub-classes of Message, so that sub-classes
   * can selectively overide for different message types.
   */

  void handleCollision (GameObjectPtr & ptr);
  /* Handle a collision with another GameObject.
   * Params: Mutable reference to a GameObjectPtr +.
   * Effect: Default is nothing, may be overridden.
   *
   * + If we can garenty the timing of deletes than this could just be a
   *   reference to the GameObject itself.
   */
#endif
};

#endif//ORBIT_AI_HPP
