#ifndef PLANE_DRAWABLE_HPP
#define PLANE_DRAWABLE_HPP

/* An extention to the Plane class that is also Drawable, and has the
 * nessasary draw function defined to draw all of its contents.
 */

#include <SFML/Graphics/Drawable.hpp>
#include "plane.hpp"



template<typename Drawable2D>
class PlaneDrawable : public Plane<Drawable2D>, public sf::Drawable
{
public:
  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw all game objects within this plane.
   * Params: target to draw to plus the states that repersent the options.
   * Effect: Draw all the objects in the Plane to the target.
   */
};

#include "plane-drawable.tpp"

#endif//PLANE_DRAWABLE_HPP
