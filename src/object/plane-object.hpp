#ifndef PLANE_OBJECT_HPP
#define PLANE_OBJECT_HPP

/* The GameObject that exists in 2D space, that is in a plane.
 *
 * The current constructors are temperary, while I refactor.
 */

/* MapObject? PlaneObject? I like the idea of varing it by the first letter.
 * This takes all of the features of the GameObject but then makes it occur
 * in a space. PlaneObject then has a location in space, and probably a body
 * that can collide and overlap (well maybe not always, but I think at this
 * point it is reasonable to assume that) as well as move around.
 *
 * So in short it adds 2D location and physics to the GameObject.
 *
 * handleCollision should also be broken up. There is some timing issues with
 * the current set up. I think we need 3 handlers: begin->continue->end.
 * Begin is called the first frame of collision, continue ever frame of
 * collison there after and end the first frame after that. collision->overlap
 */

#include <vector>
#include <SFML/Graphics/Transform.hpp>
#include "game-object.hpp"

class PlaneObject : public GameObject, public sf::Transformable
{
  // TODO switch to CountPtr/Ref once that is availible.
  struct OverlapData
  {
    bool thisFrame;
    PlaneObject * with
  };
  std::vector<OverlapData> overlaps;

  void updatePhysics (sf::Time const & deltaT);
  /* Allow an object to move with time.
   * Not virtual, although probably dependant on some settings else where,
   * such as the update function setting the speed.
   */

protected:
  virtual void overlapBegin (PlaneObject const & with);
  virtual void overlapContinue (PlaneObject const & with); // <~name
  virtual void overlapEnd (PlaneObject const & with);

public:
  PlaneObject (AiComponent * ai,
               PhysicsComponent * physics,
               GraphicsComponent * graphics);
  PlaneObject (sf::Transformable const & start,
               AiComponent * ai,
               PhysicsComponent * physics,
               GraphicsComponent * graphics);

  bool overlapCheck (PlaneObject const & with);
  /* Check to see if this object overlaps with the provided one.
   * Params: Regular reference?
   * Effect: If objects overlap, calls one of overlapBegin or overlapContinue
   * Return: True if there is an overlap, otherwise returns false.
   */

  void endOverlapStep ();
  /* Call to end the overlap step of this frame.
   * Effect: Resets the frame for overlaps and calls overlapEnd on all
   *   object that collided last frame but not this one.
   */
};

#endif//PLANE_OBJECT_HPP
