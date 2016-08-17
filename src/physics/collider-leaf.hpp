#ifndef COLLIDER_LEAF_HPP
#define COLLIDER_LEAF_HPP

/* A ColliderLeaf is the part that actually collides with other ColliderLeaves
 * and they form the end point of any contained colliders (sort of like the
 * leaf node in a tree).
 *
 * This is a class that is dependant on it is child-classes and things are
 * very interdependant. Every child-class must have a collidesWith that all
 * child-classes must implement.
 */

#include "collider.hpp"
class CircleCollider;
class PointCollider;
class AlignRectCollider;



class ColliderLeaf : public Collider
{
private:
protected:
public:
  virtual ~ColliderLeaf () {}

  bool collides (Collider const & other) const
  /* Check for a collision between the leaf and the other collider.
   * Params: Reference to the other Collider.
   * Return: True if there is a collision, false otherwise.
   */
  { return other.collides(*this); }

  virtual bool collides (ColliderLeaf const & other) const = 0;
  /* Check for a collision between two leaves.
   * Params: Reference to the other ColliderLeaf.
   * Return: True if there is a collision, false otherwise.
   */

  virtual bool collidesWith (CircleCollider const & other) const = 0;
  virtual bool collidesWith (PointCollider const & other) const = 0;
  virtual bool collidesWith (AlignRectCollider const & other) const = 0;
  /* Check for a collision between two leaves of particular types.
   * Params: Reference to the other ColliderLeaf childtype.
   * Return: True if there is a collision, false otherwise.
   */

};

#endif//COLLIDER_LEAF_HPP