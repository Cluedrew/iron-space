#ifndef PLANE_HPP
#define PLANE_HPP

/* Implements a "plane" in the game world. Planes are a 2D world that contains
 * GameObjects
 */



class Plane
{
private:
  std::vector<GameObject> objects;

protected:
public:
  Plane ();
  virtual ~Plane ();
};

#endif//PLANE_HPP
