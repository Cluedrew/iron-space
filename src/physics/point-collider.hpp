#ifndef POINT_COLLIDER_HPP
#define POINT_COLLIDER_HPP

/* A collider that repersents an single point.
 */

#include <SFML/System/Vector2.hpp>
namespace sf { class Transform; }
#include "collider-leaf.hpp"



class PointCollider : public ColliderLeaf
{
private:
  sf::Vector2f localPos;
  sf::Vector2f worldPos;

protected:
public:
  PointCollider (float x, float y);
  PointCollider (sf::Vector2f xy);
  /* Define a PointCollider by its 2d coordinates.
   *   The given location is in local space, which is assumed to be the
   *   same as world space initally (call update to change that.
   * Params: Either the local x & y coordinates or a Vector2f with both.
   */

  virtual ~PointCollider ();

  void update (sf::Transform const & parent);

  bool collides (ColliderLeaf const & other) const;

  bool collidesWith (CircleCollider const & other) const;
  bool collidesWith (PointCollider const & other) const;
  bool collidesWith (AlignRectCollider const & other) const;
  /* Check for a collision between two leaves of particular types.
   * Params: Reference to the other ColliderLeaf childtype.
   * Return: True if there is a collision, false otherwise.
   */

  sf::Vector2f getWorldPoint () const;
  /* Get the point in world space.
   * Params: The point's xy coordinates relative to the world.
   */
};

#endif//POINT_COLLIDER_HPP
