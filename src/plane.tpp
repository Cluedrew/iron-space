#ifndef PLANE_TPP
#define PLANE_TPP

#include "plane.hpp"

// Implementation of the plane.

#include <iostream>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "input/input-event.hpp"
#include "physics/collider.hpp"
#include "physics/point-collider.hpp"



template<typename Object2D>
Plane<Object2D>::Plane () :
    objects()
{}

template<typename Object2D>
Plane<Object2D>::~Plane ()
{}

// see header
template<typename Object2D>
template<typename... Args>
void Plane<Object2D>::emplace (Args&&... args)
{
  objects.emplace_back(std::forward<Args>(args)...);
}

// see header
template<typename Object2D>
typename Plane<Object2D>::iterator Plane<Object2D>::begin ()
{
  return objects.begin();
}

// see header
template<typename Object2D>
typename Plane<Object2D>::const_iterator Plane<Object2D>::cbegin () const
{
  return objects.cbegin();
}

// see header
template<typename Object2D>
typename Plane<Object2D>::iterator Plane<Object2D>::end ()
{
  return objects.end();
}

// see header
template<typename Object2D>
typename Plane<Object2D>::const_iterator Plane<Object2D>::cend () const
{
  return objects.cend();
}

// see header
template<typename Object2D>
bool Plane<Object2D>::handleInput (InputEvent const & ievent)
{
  iterator it;
  if (InputEvent::Select == ievent.type)
  {
    PointCollider click(ievent.pos.x, ievent.pos.y);

    for (it = objects.begin() ; it != objects.end() ; ++it)
    {
      if (it->collides(click))
      {
        if (it->handleInput(ievent))
        {
          return true;
        }
      }
    }
  }
  return false;
}

#if 0
// Planned addition:
template<typename Object2D>
void Plane<Object2D>::resolveCollitions ()
/* Search the Plane for colliding (overlapping) objects and notify them.
 *
 * The implementation might change, but I hope the interface does not get
 * much more complex than this.
 */
{
  iterator it, jt;
  for (it = objects.begin() ; it != objects.end() ; ++it)
  {
    for (jt = it, ++jt ; jt != objects.end() ; ++jt)
    {
      if (it->collides(*jt))
      {
        it->handleCollition(...(jt));
        jt->handleCollition(...(it));
      }
    }
  }
}
#endif

#endif//PLANE_TPP
