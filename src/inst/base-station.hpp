#ifndef BASE_STATION_HPP
#define BASE_STATION_HPP

/* A central base at the center of the player's network. It provides a bit of
 * the basics and is also the building hub for other units.
 *
 * Code Wise also a testing ground for my new Entity (and related) classes.
 */

#include "object/entity.hpp"



class BaseStation : public Entity {
public:
  BaseStation(int startX, int startY);

  std::string const & getName () const;
  // Non-unique name of this entity.

  void display (StatusDisplay & target) const;
  // Display this unit on the status display.

  bool innerHandleInput (InputEvent const & input);
  void innerUpdateAi (sf::Time const & deltaT);
  void innerHandleCollision (GameObjectPtr & with);
};

#endif//BASE_STATION_HPP
