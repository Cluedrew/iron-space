#ifndef PLANE_OBJECT_HPP
#define PLANE_OBJECT_HPP

/* The GameObject that exists in 2D space, that is in a plane.
 *
 * This adds 2D physics, collision and kinematics, to the game object.
 *
 * Collision is currently limited to overlaping, no actual hits are
 * calculated. Collisions should be checked for once per frame (iteration of
 * the main loop). There are three collision handler functions.
 *
 * Its current form is temporary as I refactor GameObject.
 */

#include <vector>
#include <SFML/Graphics/Transform.hpp>
#include "game-object.hpp"

class PlaneObject : public GameObject
// TODO Add public sf::Transformable once GameObject stops using it.
{
  // TODO switch to CountPtr/Ref once that is availible.
  struct OverlapData
  {
    bool thisFrame;
    PlaneObject * with;
  };
  std::vector<OverlapData> overlaps;

  void updatePhysics (sf::Time const & deltaT);
  /* Allow an object to move with time.
   * Not virtual, although probably dependant on some settings else where,
   * such as the update function setting the speed.
   */

protected:
  virtual void overlapBegin (PlaneObject & with);
  virtual void overlapNext (PlaneObject & with);
  virtual void overlapEnd (PlaneObject & with);

public:
  PlaneObject (AiComponent * ai,
               PhysicsComponent * physics,
               GraphicsComponent * graphics);
  PlaneObject (sf::Transformable const & start,
               AiComponent * ai,
               PhysicsComponent * physics,
               GraphicsComponent * graphics);

  bool isOverlapping (PlaneObject const & with) const;
  /* Check for overlap between two objects.
   * Params: Constant reference to other object.
   * Return: True if they overlap, false otherwise.
   */

  bool isOverlapping (Collider const & with) const;
  /* Check for overlap with a collider.
   * Params: Constant reference to collider.
   * Return: True if they overlap, false otherwise.
   */

  bool overlapCheck (PlaneObject & with);
  /* Check for and resolve overlap between two objects.
   * Params: Mutable reference to other object.
   * Effect: If objects overlap, calls one of overlapBegin or overlapContinue
   * Return: True if there is an overlap, otherwise returns false.
   */

  void endOverlapStep ();
  /* Call to end the overlap step of this frame.
   * Effect: Resets the frame for overlaps and calls overlapEnd on all
   *   object that collided last frame but not this one.
   */

  // These overloads are used to implement the non-inner versions on
  // GameObject when AiWrapper is the AiComponent.
  virtual bool innerHandleInput (InputEvent const & input) { return false; }
  virtual void innerUpdateAi (sf::Time const & deltaT) {}
  virtual void innerHandleCollision (GameObjectPtr & with) {}
};

#endif//PLANE_OBJECT_HPP
