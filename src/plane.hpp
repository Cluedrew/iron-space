#ifndef PLANE_HPP
#define PLANE_HPP

/* Implements a "plane" in the game world. Planes are a 2D world that contains
 * GameObjects.
 */

#include <vector>
#include <SFML/Graphics/View.hpp>
namespace sf
{
  class RenderTarget;
  class RenderStates;
  class Drawable;
}
#include "game-object.hpp"
class InputEvent;



class Plane : public sf::Drawable
{
private:
  std::vector<GameObject> objects;
  sf::View view;

protected:
public:
  Plane ();
  virtual ~Plane ();

  void insert(GameObject && object);
  /* Insert a GameObject to this plane.
   * Params: object to be added, must be moved in.
   */

  // I think I might need a way to search the plane.

  bool handleInput (InputEvent const & ievent);
  /* Give an event to a GameObject to be handled.
   * Params: An InputEvent (TODO what types)
   * Effect: Event is handled (may result in additional changes in updates).
   * Return: True if the event was handled, false otherwise.
   */

  // The loop functions will have to be filled in.
  //void /*bool*/ handleInput ();
  //void updateAi (sf::Time const &);
  //void updatePhysics (sf::Time const &);
  //void resolveCollisions ();

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw all game objects within this plane.
   * Params: target to draw to plus the states that repersent the options.
   * Effect: Draw
   */
};

#endif//PLANE_HPP
