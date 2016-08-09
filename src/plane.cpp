#include "plane.hpp"

// Implementation of the plane.

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include "input/input-event.hpp"



Plane::Plane () :
    objects(), view()
{}

Plane::~Plane ()
{}

// see header
void Plane::insert(GameObject && object)
{
  objects.emplace_back(std::move(object));
}

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

void Plane::updateAi (sf::Time const & deltaT)
{
  std::vector<GameObject>::iterator it;
  for (it = objects.begin() ; it != objects.end() ; ++it)
    it->updateAi(deltaT);

  //for (unsigned int i = 0 ; i < objects.size() ; ++i)
  //{
  //  objects[i].updateAi(deltaT);
  //}
}
