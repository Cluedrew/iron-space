#ifndef COLLIDER_HPP
#define COLLIDER_HPP

/* This Collider class is used as a base for anything that can collide with
 * something else.
 *
 * The collision detection system does involve a lot of virtual function
 * calls. Not only are there several layers of calls but it will have
 * quadratic growth for each top level call. Still as we are losing mean
 * nanoseconds on each call, by the time there are enough calls for it to
 * be a problem pruning calls should be sufficant.
 *
 * TODO I managed to hack this class (& CircleCollider) into working. But it
 * is a mess that I need to clean up. For instance ColliderLeaf was supposed
 * to be part of the chain, but I realized the calls don't quite line up the
 * way I had intended.
 * So I have to get that working in a more expandible way than I do now.
 */

class CircleCollider;



class Collider
{
private:
  virtual bool collidesWith (CircleCollider const & other) const = 0;

protected:
public:
  virtual ~Collider () {}

  virtual bool collides (Collider const & other) const = 0;
};

#endif//COLLIDER_HPP
