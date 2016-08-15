#ifndef COLLIDER_HPP
#define COLLIDER_HPP

/* Idea to have a generic collider.
 * The Collider class is inherited from for anything that can be collided with
 * however they only hand down the question down to their components.
 *
 * The ColliderLeaf is at the bottom of that, and they collide with each other
 * (leaf comes from the idea of leaf node). They contain the actual math in
 * most cases.
 *
 * I'm not sure if this is going to work, but I thought I would right it out
 * to help me thing it through.
 *
 * You know I'm pretty sure this will work, this issue is the number of
 * dynamic dispatch calls. So I looked and neither virtual functions nor
 * the virtor pattern is that slow (looking them up in the vtable yourself
 * can sometimes be faster, but I have no idea how to do that). I mean it is
 * about 3 times longer than a regular function call (but even that is about
 * a 10th the speed of an inline call). So it is slow but that is still a
 * difference messured in nanoseconds so I don't think it will be a problem
 * at least until we are having hundreds of these calls a second.
 * ... That could happen, but I think at that point cutting down the number
 * of calls would be a bigger difference than speeding up the function calls.
 */



class Collider //Collides
{
private:
protected:
public:
  virtual ~Collider ();

  virtual bool collides (Collider const & other) const = 0;

  /* Most of these will be things like
   * innerCollider->collides(other);
   */
};



class ColliderLeaf : public Collider
{
private:
  // virtual bool collides (<ColliderLeaf child type> const & other) const;
protected:
public:
  virtual ~ColliderLeaf ();

  bool collides (Collider const & other) const;
  // { return other.collides(*this); }
};

#endif//COLLIDER_HPP
