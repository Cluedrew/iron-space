#ifndef PLANE_TPP
#define PLANE_TPP

#include "plane.hpp"

// Implementation of the plane.

#include <iostream>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "input/input-event.hpp"
#include "physics/circle-collider.hpp"



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

/*
bool Plane<Object2D>::nextAt (iterator & curBegin, Collider const & location)
{
  iterator curEnd = objects.end();

#define NEXT_AT_BODY				\
  if (curEnd == curBegin)			\
    return false;				\
						\
  do {						\
    ++curBegin;					\
						\
    if (curEnd == curBegin)			\
      return false;				\
  }						\
  while (curBegin->collides(location));		\
  return true;
}

bool Plane<Object2D>::nextAt
    (const_iterator & curBegin, Collider const & location) const
{
  const_iterator curEnd = objects.cend();

  NEXT_AT_BODY
}
*/

// see header
template<typename Object2D>
bool Plane<Object2D>::handleInput (InputEvent const & ievent)
{
  std::vector<GameObject>::iterator it;
  if (InputEvent::Select == ievent.type)
  {
    CircleCollider click(ievent.pos.x, ievent.pos.y, 0);
    click.update(sf::Transformable());

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

/* see header
template<typename Object2D>
void Plane<Object2D>::draw (sf::RenderTarget & target, sf::RenderStates states) const
{
  for (unsigned int i = 0 ; i < objects.size() ; ++i)
  {
    target.draw(objects[i], states);
  }
}*/


#if 0
// Thoughts on what might be TODO

template<typename Object2D>
class Plane
/* I am considering changing the Plane class to be a template. Moves of the
 * GameObject actually has nothing to do with how it is stored in the Plane
 * and so I could save myself some effort on testing this way.
 *
 * Object2D must implement a function to get its 2D position (probably as
 * a sf::Vector2f) and another that checks for collisions between two
 * instances of that class.
 *
 * Being Drawable might actually be drawn out into a seperate class. */
template<typename Drawable2D>
class PlaneDrawable : public Plane<Drawable2D>, public sf::Drawable
/* Again mostly for seperation of conserns. Being Drawable doesn't have
 * anything to do with the 2D shape rules that define how something is
 * stored in the plane. Also compartamentalizes testing.
 */

#endif

#endif//PLANE_TPP
