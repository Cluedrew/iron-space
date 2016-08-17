#ifndef ALIGN_RECT_COLLIDER_HPP
#define ALIGN_RECT_COLLIDER_HPP

/* Aligned Rectangular Collider, a collidable area that is rectangular and
 * the edges of which always align with the axis. That is it never rotates.
 *
 * TODO Currently it also doesn't scale, but that is only because I don't
 * know how to get that to work.
 */

#include <SFML/Graphics/Rect.hpp>
namespace sf { class Transform; }
#include "collider-leaf.hpp"



class AlignRectCollider : public ColliderLeaf
{
private:
  sf::FloatRect absRect;
//  sf::FloatRect relRect;
  float left, top, width, height;
protected:
public:
  AlignRectCollider (float left, float top, float width, float height);
  AlignRectCollider (sf::FloatRect const & rect);
  /* Create a collider from the coordinates given or a rect.
   *   Coordinates are given in local space, which is 1to1 to world space
   *   until update is called.
   * Params: The position and size of the rect, position is messured from
   *   the top left of the screen.
   */

  virtual ~AlignRectCollider ();

  void update (sf::Transform const & parent);

  bool collides (ColliderLeaf const & other) const;

  bool collidesWith (CircleCollider const & other) const;
  bool collidesWith (PointCollider const & other) const;
  bool collidesWith (AlignRectCollider const & other) const;
  /* Check for a collision between two leaves of particular types.
   * Params: Reference to the other ColliderLeaf childtype.
   * Return: True if there is a collision, false otherwise.
   */

  sf::FloatRect getWorldRect () const;
};

#endif//ALIGN_RECT_COLLIDER_HPP
