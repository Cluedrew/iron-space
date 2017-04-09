#include "plane-object.hpp"

PlaneObject::PlaneObject (AiComponent * ai,
               PhysicsComponent * physics,
               GraphicsComponent * graphics) :
    GameObject(ai, physics, graphics)
{}

PlaneObject::PlaneObject (sf::Transformable const & start,
               AiComponent * ai,
               PhysicsComponent * physics,
               GraphicsComponent * graphics) :
    GameObject(start, ai, physics, graphics)
{}

void PlaneObject::updatePhysics (sf::Time const & deltaT)
{}

// No-ops, exist to be overloaded.
void PlaneObject::overlapBegin (PlaneObject & with) {}
void PlaneObject::overlapContinue (PlaneObject & with) {}
void PlaneObject::overlapEnd (PlaneObject & with) {}

bool PlaneObject::isOverlapping (PlaneObject const & with) const
{
  // The calculation should take place here later in refactoring.
  return collides(with);
}

bool PlaneObject::overlapCheck (PlaneObject & with)
{
  if (!isOverlapping(with))
    return false;

  std::vector<OverlapData>::iterator it;
  for (it = overlaps.begin() ; it != overlaps.end() ; ++it)
  {
    if (&it->with == &with)
    {
      if (it->thisFrame)
        return true;
      else
      {
        it->thisFrame = true;
        overlapContinue(with);
        return true;
      }
    }
  }
  overlaps.push_back(OverlapData{.thisFrame = true, .with = with});
  overlapBegin(with);
  return true;
}

void PlaneObject::endOverlapStep ()
{
  std::vector<OverlapData>::iterator it;
  for (it = overlaps.begin() ; it != overlaps.end() ; ++it)
  {
    if (it->thisFrame)
      it->thisFrame = false;
    else
    {
      overlapEnd(it->with);
      // Remove the element from the list, which invalidates the iterator.
    }
  }
}
