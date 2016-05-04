#ifndef COLLISION_HPP
#define COLLISION_HPP

/* Holds information about a collision between two objects.
 */



class Collision
{
private:
  GameObjectPtr objectA;
  GameObjectPtr objectB;

protected:
public:
  Collision ();
  virtual ~Collision ();
};

#endif//COLLISION_HPP
