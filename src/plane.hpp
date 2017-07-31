#ifndef PLANE_HPP
#define PLANE_HPP

/* Implements a "plane" in the game world. Planes are a 2D world that contains
 * GameObjects. This 2D Plane is not relative to anything, however objects
 * inside the Plane do have spacial positioning.
 *
 * The filter_it from the ABCToolBox would actually fix in really well here.
 * Maybe I should go back to that.
 *
 * Object2D must have defined on it:
 * bool collides (Collider const &) const;
 * bool collides (Object2D const &) const;
 */

#include <vector>
#include "util/double-ptr.hpp"
class InputEvent;
class Collider;



template<typename Object2D>
class Plane
{
public:
  typedef DoublePtr<typename std::vector<Object2D *>::iterator> iterator;
  typedef DoublePtr<typename std::vector<Object2D *>::const_iterator>
      const_iterator;

private:
  std::vector<Object2D*> objects;

protected:
public:
  Plane ();
  virtual ~Plane ();

  void insert (Object2D * value);
  /* Insert an existing object into the Plane, takes ownership.
   * Params: Pointer to the object to insert.
   * Effect: Object is added to the Plane.
   */

  template<typename... Args>
  void emplace (Args&&... args);
  /* Construct a new Object2D in place within the Plane.
   * Params: Constructor arguments for the Plane.
   * Effect: Increases the number of objects in the Plane by 1.
   *   Constructs a Object2D.
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

  std::vector<Object2D*> overlapping (Collider const & with);
  /* WIP: get all internal objects that overlap with the Collider.
   * Params: The collider to check against.
   * Effect: ???
   * Return: A vector of references to the resulting objects. -> Iterator?
   */

  bool handleInput (InputEvent const & ievent);
  /* Give an event to a GameObject* to be handled.
   *   * This one needs a GameObject until I have a better solution.
   *     The handle input function is part of the Object2D requirents.
   * Params: An InputEvent with type == InputEvent::Select.
   * Effect: Event is handled (may result in additional changes in updates).
   * Return: True if the event was handled, false otherwise.
   */

  void resolveCollisions ();
  /* Find all the collisions in the plane and notify the colliding objects.
   * Effect: The objects within the plane might cause some as they resolve
   *    the collisions.
   */
};



#include "plane.tpp"

#endif//PLANE_HPP
