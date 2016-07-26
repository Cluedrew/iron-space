#include "plane.hpp"

// Implementation of the plane.

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>

Plane::Plane () :
    objects(), view()
{}

Plane::~Plane ()
{}

void Plane::insert(GameObject && object)
{
  objects.emplace_back(std::move(object));
}

// see interface
void Plane::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
  for (unsigned int i = 0 ; i < objects.size() ; ++i)
  {
    target.draw(objects[i], states);
  }
}

