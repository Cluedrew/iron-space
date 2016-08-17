#ifndef PLANE_HPP
#define PLANE_HPP

/* Implements a "plane" in the game world. Planes are a 2D world that contains
 * GameObjects. This 2D Plane is not relative to anything, however objects
 * inside the Plane do have spacial positioning.
 *
 * template<typename Object2D> class Plane
 * Where Object2D has a: sf::Vector2f getPosition() function, collides and
 * Drawable. Drawable I could cut out, because it is not part of the main
 * purpose, but everything I would use this template for uses it.
 */

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
namespace sf
{
  class RenderTarget;
  class RenderStates;
}
#include "game-object.hpp"
class InputEvent;



//template<typename Object2D>
class Plane : public sf::Drawable
{
public:
  typedef typename std::vector<GameObject>::iterator iterator;
  typedef typename std::vector<GameObject>::const_iterator const_iterator;

private:
  std::vector<GameObject> objects;

protected:
public:
  Plane ();
  virtual ~Plane ();

  template<typename... Args>
  void emplace (Args&&... args);
  /* Construct a new GameObject in place within the Plane.
   * Params: Constructor arguments for the Plane.
   * Effect: Increases the number of objects in the Plane by 1.
   *   Constructs a GameObject.
   */

  iterator begin ();
  const_iterator cbegin () const;
  /* Get an iterator to the beginning of the Plane.
   * Return: An iterator for the first object in the Plane,
   *    unless the Plane is empty, then an end iterator is retuned.
   */

  iterator end ();
  const_iterator cend () const;
  /* Get an iterator to the end of the Plane.
   * Return: The iterator to (one past) the end of the Plane.
   */

  bool handleInput (InputEvent const & ievent);
  /* Give an event to a GameObject to be handled.
   * Params: An InputEvent (TODO what types)
   * Effect: Event is handled (may result in additional changes in updates).
   * Return: True if the event was handled, false otherwise.
   */

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw all game objects within this plane.
   * Params: target to draw to plus the states that repersent the options.
   * Effect: Draw all the objects in the Plane.
   */
};



// The one single-line function is not worth the tpp file.
template<typename... Args>
inline void Plane::emplace (Args&&... args)
{
  objects.emplace_back(std::forward<Args>(args)...);
}

#endif//PLANE_HPP
