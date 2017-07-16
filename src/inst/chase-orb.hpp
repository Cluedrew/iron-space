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
  ChaseOrb(int x, int y);
  ChaseOrb(sf::Vector2<int> xy);

  bool innerHandleInput (InputEvent const & input);
  void innerUpdateAi (sf::Time const & deltaT);
  void innerHandleCollision (GameObjectPtr & with);
};

#endif//CHASE_ORB_HPP
