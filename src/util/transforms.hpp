#ifndef TRANSFORMS_HPP
#define TRANSFORMS_HPP

/* For helpers relating to the sf::Transform and sf::Transformable classess.
 *
 * Some of these are only used by tests. I could move them to
 * transforms.tst.hpp, but deadcode elimination probably takes care of that
 * anyways.
 */

namespace sf
{
  class Transform;
  class Transformable;
}



sf::Transformable xyTransformable (float x, float y);
/* Make a transformable that with a set possition, no scale or rotation.
 * Params: The x and y coordinates of the transform.
 * Return: A new Transformable object.
 */

// Tests only, transforms.tst.hpp
bool operator== (sf::Transformable const & lhs, sf::Transformable const & rhs);
/* Check to see if two transformables are at the same location.
 * Params: References to two sf::Transformables.
 * Return: True if the transformable match, false otherwise.
 */

bool operator!= (sf::Transformable const & lhs, sf::Transformable const & rhs);
// Check to see if two transformables are not at the same location.

bool operator== (sf::Transform const & lhs, sf::Transform const & rhs);
/* Check to see if two transforms are equal.
 * Params: References to two sf::Transforms.
 * Return: True if the transforms are equal, false otherwise.
 */

bool operator!= (sf::Transform const & lhs, sf::Transform const & rhs);
// Check to see if two transforms are not equal.

#endif//TRANSFORMS_HPP
