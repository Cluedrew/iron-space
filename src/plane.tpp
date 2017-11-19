#ifndef PLANE_TPP
#define PLANE_TPP

#include "plane.hpp"

// Implementation of the plane.

#include <iostream>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "object/game-object-ptr.hpp"
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
void Plane<Object2D>::insert (Object2D * value)
{
  objects.push_back(value);
}

// see header
template<typename Object2D>
template<typename... Args>
void Plane<Object2D>::emplace (Args&&... args)
{
  objects.emplace_back(new Object2D(std::forward<Args>(args)...));
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
std::vector<Object2D*> Plane<Object2D>::overlapping (Collider const & with)
{
  iterator it;
  std::vector<Object2D*> result;
  for (it = objects.begin() ; it != objects.end() ; ++it)
  {
    if (it->isOverlapping(with))
    {
      Object2D & ref = *it;
      result.emplace_back(&ref);
    }
  }

  return result;
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
      if (it->isOverlapping(click))
      {
        if (it->receiveInput(ievent))
        {
          return true;
        }
      }
    }
  }
  return false;
}

// see header
template<typename Object2D>
void Plane<Object2D>::resolveCollisions ()
{
  iterator it, jt;
  for (it = objects.begin() ; it != objects.end() ; ++it)
  {
    for (jt = it, ++jt ; jt != objects.end() ; ++jt)
    {
      if (it->isOverlapping(*jt))
      {
        GameObjectPtr jPtr(*jt);
        it->handleCollision(jPtr);
        GameObjectPtr iPtr(*it);
        jt->handleCollision(iPtr);
      }
    }
  }
}

// see header
template<typename Object2D>
void Plane<Object2D>::overlapStep ()
{
  iterator const end = objects.end();
  for (iterator it = objects.begin() ; it != end ; ++it)
  {
    for (iterator jt = it ; (++jt) != end ; )
      if (it->overlapCheck(*jt))
        jt->overlapCheck(*it);
    // I think this can be mixed in, as long as it's checks are done.
    it->endOverlapStep();
  }
}

// see header
template<typename Object2D>
void Plane<Object2D>::draw
    (sf::RenderTarget & target, sf::RenderStates states) const
{
  typename Plane<Object2D>::const_iterator it;
  for (it = this->cbegin() ; it != this->cend() ; ++it)
    target.draw(*it, states);
}


#endif//PLANE_TPP
