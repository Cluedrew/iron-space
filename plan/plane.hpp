#ifndef PLANE_HPP
#define PLANE_HPP

/* Implements a "plane" in the game world. Planes are a 2D world that contains
 * GameObjects.
 */



class Plane
{
private:
  std::vector<GameObject> objects;
  sf::View view;

protected:
public:
  Plane ();
  virtual ~Plane ();

  // The loop functions will have to be filled in.
  void /*bool*/ handleInput ();
  void updateAi (sf::Time const &);
  void updatePhysics (sf::Time const &);
  void resolveCollisions ();
  void render ();
};

#endif//PLANE_HPP
