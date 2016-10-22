#include "transforms.hpp"

// Implementing sf::Transform and sf::Transformable helpers.

//#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>



// see header
sf::Transformable xyTransformable(float x, float y)
{
  sf::Transformable fin;
  fin.setPosition(x, y);
  return fin;
}

// see header
bool operator== (sf::Transformable const & lhs, sf::Transformable const & rhs)
{
  return (lhs.getPosition() == rhs.getPosition() &&
          lhs.getRotation() == rhs.getRotation() &&
          lhs.getScale() == rhs.getScale());
}

bool operator!= (sf::Transformable const & lhs, sf::Transformable const & rhs)
{
  return !(lhs == rhs);
}

// see header
bool operator== (sf::Transform const & lhs, sf::Transform const & rhs)
{
  const float * lhsFloats = lhs.getMatrix();
  const float * rhsFloats = rhs.getMatrix();

  for (unsigned int i = 0 ; i < 16 ; ++i)
    if (lhsFloats[i] != rhsFloats[i])
      return false;
  return true;
}

bool operator!= (sf::Transform const & lhs, sf::Transform const & rhs)
{
  return !(lhs == rhs);
}
