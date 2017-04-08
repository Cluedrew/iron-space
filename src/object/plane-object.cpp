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

void PlaneObject::overlapBegin (PlaneObject const & with)
{}

void PlaneObject::overlapContinue (PlaneObject const & with)
{}

void PlaneObject::overlapEnd (PlaneObject const & with)
{}

bool PlaneObject::overlapCheck (PlaneObject const & with)
{
  // If the object collides...
  std::vector<OverlapData>::iterator it;
  for (it = overlaps.begin() ; it != overlaps.end() ; ++it)
  {
    if (it->with == &with)
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
  overlaps.push_back(OverlapData{thisFrame = true, with = *with});
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
      overlapEnd(with);
      // Remove the element from the list, which invalidates the iterator.
    }
  }
}

if (it->with == &with):

end if;
