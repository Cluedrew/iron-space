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
 */



class Collider //Collides
{
private:
protected:
public:
  virtual ~Collider ();

  virtual bool collides (Collider const & other) const = 0;
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

  virtual bool collides (ColliderLeaf const & other) const;
  // { return other.collides(*this); }
};

#endif//COLLIDER_HPP
