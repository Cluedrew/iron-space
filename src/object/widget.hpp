#ifndef WIDGET_HPP
#define WIDGET_HPP

/* A widget is a GameObject for the GUI.
 *
 * Still deciding what the default feature set should be.
 */

#include "../game-object.hpp"



class Widget : public GameObject
{
public:
  Widget (AiComponent * ai,
          PhysicsComponent * physics,
          GraphicsComponent * graphics) :
    GameObject(ai, physics, graphics)
  {}

  Widget (sf::Transformable const & start,
          AiComponent * ai,
          PhysicsComponent * physics,
          GraphicsComponent * graphics) :
    GameObject(start, ai, physics, graphics)
  {}
};

#endif//WIDGET_HPP
