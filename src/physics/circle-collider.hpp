#ifndef CIRCLE_COLLIDER_HPP
#define CIRCLE_COLLIDER_HPP

/* A minimal implementation of a collider. It is a circlurlar collider with
 * a defined radius and position.
 */

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include "collider.hpp"



class CircleCollider : public Collider
{
private:
  sf::Transformable relativePosition;
  sf::Transformable absolutePosition;
  float radius;

  //bool collidesWith (CircleCollider const & other) const
  //{ return collides(other); }

protected:
public:
  CircleCollider (float x, float y, float r);
  /* Create a new CircleCollider, giving both the position and radius.
   * Params: The position of the CircleCollider's center in x,y coordinates
   *   and the radius of the CircleCollider's body.
   *
   * Note: You should always call update on a (circle) collider between its
   *   construction and any calls to collides.
   */

  CircleCollider (CircleCollider const & other) = default;
  CircleCollider (CircleCollider && other) = default;
  CircleCollider & operator=(CircleCollider const & other) = default;
  CircleCollider & operator=(CircleCollider && other) = default;

  virtual ~CircleCollider ();

  void update (sf::Transformable const & root);// = sf::Transform::Identity);
  /* Update the absolute transform of this collider in the world by messuring
   *   by the relative transform of this collider from root.
   * Params: The root location that this collider's location is messured from.
   *   If omitted the identity matrix is used, which means it is relative
   *   to the global space.
   * Effect: Changes the value of the absolutePosition of this collider.
   */

  bool collides (Collider const & other) const;
  bool collidesWith (CircleCollider const & other) const;
  /* Check to see if the two colliders are colliding.
   *   This is 'inclusive' so if they are exactly on the line it counts.
   * Params: A reference to another Collider to check against.
   */

  void setPos (float x, float y);
  void setPos (sf::Vector2<float> const & xy);
  /* Move the collider to the given location, relative to its root.
   * Params: The x & y coordinates or a Vector2 with x, then y.
   */
};

#endif//CircleCollider_HPP

