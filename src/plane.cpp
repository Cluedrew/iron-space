#include "plane.hpp"

// Implementation of the plane.

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "input/input-event.hpp"



Plane::Plane () :
    objects()
{}

Plane::~Plane ()
{}

// see header
Plane::iterator Plane::begin ()
{
  return objects.begin();
}

// see header
Plane::const_iterator Plane::cbegin () const
{
  return objects.cbegin();
}

// see header
Plane::iterator Plane::end ()
{
  return objects.end();
}

// see header
Plane::const_iterator Plane::cend () const
{
  return objects.cend();
}

/*
bool Plane::nextAt (iterator & curBegin, Collider const & location)
{
  std
}

bool Plane::nextAt (const_iterator & curBegin, Collider const & location)
*/

// see header
bool Plane::handleInput (InputEvent const & ievent)
{
  std::vector<GameObject>::iterator it;
  if (InputEvent::Select == ievent.type)
  {
    Collider click(ievent.pos.x, ievent.pos.y, 0);
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

// see header
void Plane::draw (sf::RenderTarget & target, sf::RenderStates states) const
{
  for (unsigned int i = 0 ; i < objects.size() ; ++i)
  {
    target.draw(objects[i], states);
  }
}
