#ifndef POINT_COLLIDER_HPP
#define POINT_COLLIDER_HPP

/* A collider that repersents an single point.
 */

namespace sf
{
  template<typename T> class Vector2;
  class Transform;
}
#include "collider-leaf.hpp"



class PointCollider : public ColliderLeaf
{
private:
  float absX, absY;
  float relX, relY;

protected:
public:
  PointCollider (float x, float y);
  PointCollider (sf::Vector2<float> xy);

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

  sf::Vector2<float> getPoint () const;
  /* Get the point in world space.
   * Params: The point's xy coordinates relative to the world.
   */
};

#endif//POINT_COLLIDER_HPP
