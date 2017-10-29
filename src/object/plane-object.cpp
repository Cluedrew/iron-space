#include "plane-object.hpp"

PlaneObject::PlaneObject (AiComponent * ai,
               PhysicsComponent * physics,
               GraphicsComponent * graphics) :
    GameObject(ai, physics, graphics)
{
  setFlag(UpdatePhysics);
}

PlaneObject::PlaneObject (sf::Transformable const & start,
               AiComponent * ai,
               PhysicsComponent * physics,
               GraphicsComponent * graphics) :
    GameObject(start, ai, physics, graphics)
{
  setFlag(UpdatePhysics);
}

void PlaneObject::updatePhysics (sf::Time const & deltaT)
{}

// No-ops, exist to be overloaded.
void PlaneObject::overlapBegin (PlaneObject & with) {}
void PlaneObject::overlapNext (PlaneObject & with) {}
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
    if (it->with == &with)
    {
      if (it->thisFrame)
        return true;
      else
      {
        it->thisFrame = true;
        overlapNext(with);
        return true;
      }
    }
  }
  overlaps.push_back(OverlapData{.thisFrame = true, .with = &with});
  overlapBegin(with);
  return true;
}

void PlaneObject::endOverlapStep ()
{
  using IteratorT = std::vector<OverlapData>::iterator;
  IteratorT nextCheck = overlaps.begin();
  IteratorT nextEmpty = overlaps.begin();
  IteratorT end = overlaps.end();

  while (nextCheck != end)
  {
    if (nextCheck->thisFrame)
    {
      nextCheck->thisFrame = false;
      *nextEmpty = *nextCheck;
      ++nextEmpty;
    }
    else
    {
      overlapEnd(*nextCheck->with);
    }
    ++nextCheck;
  }
  overlaps.erase(nextEmpty, end);
}
