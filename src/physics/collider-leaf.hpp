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



class ColliderLeaf : public Collider
{
private:
  // At the very end of the chain of calls are these collides with functions.
  virtual bool collidesWith (CircleCollider const & other) const = 0;
  virtual bool collidesWith (PointCollider const & other) const = 0;
  virtual bool collidesWith (AlignRectCollider const & other) const = 0;

protected:
public:
  virtual ~ColliderLeaf ();

  bool collides (Collider const & other) const;
  // { return other.collides(*this); }
};

#endif//COLLIDER_LEAF_HPP
