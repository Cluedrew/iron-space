#ifndef WIDGET_HPP
#define WIDGET_HPP

/* A widget is a GameObject for the GUI.
 *
 * Still deciding what the default feature set should be.
 * Positioning of some sort, alignment and x y coordinates, should be in there
 * somehow because that is how most of these things will be orginized. Size
 * and maybe shape could also be used for auto layouts, but that is a bit far
 * out.
 * For interactable widgets some sort of sensors for hover and click builtin
 * might be nice as well.
 */

#include "game-object.hpp"



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
