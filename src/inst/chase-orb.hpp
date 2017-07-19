#ifndef CHASE_ORB_HPP
#define CHASE_ORB_HPP

/* PlaneObject that can be selected and instructed to move elsewhere on the
 * screen.
 */

#include <SFML/System/Vector2.hpp>
#include "object/plane-object.hpp"



class ChaseOrb : public PlaneObject
{
private:
  sf::Vector2<int> target;

protected:
public:
  ChaseOrb();
  /* Create a ChaseOrb at 0, 0.
   */

  ChaseOrb(int x, int y);
  ChaseOrb(sf::Vector2<int> xy);
  /* Create a ChaseOrb at the given coordinates.
   */

  bool innerHandleInput (InputEvent const & input);
  /* Handles Point by moving the target (destination) to that position.
   * Params: Reference to event to be handled.
   * Effect: May set target.
   * Return: True of event handled.
   */
  void innerUpdateAi (sf::Time const & deltaT);
  /* Moves towards target if not already there.
   * Params: Reference to time passed.
   * Effect: Updates the position of this.
   */
  void innerHandleCollision (GameObjectPtr & with);
  /* Resolves a collision, allways a no-op.
   * Params: Pointer to object collided with.
   */
};

#endif//CHASE_ORB_HPP
