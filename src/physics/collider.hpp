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
 * TODO It is working, and a lot better than it was before. Now I just have
 *   to see about getting a standard update protocall in and working.
 */

class ColliderLeaf;



class Collider
{
private:
protected:
public:
  virtual ~Collider () {}

  virtual bool collides (Collider const & other) const = 0;
  virtual bool collides (ColliderLeaf const & other) const = 0;
};

#endif//COLLIDER_HPP
