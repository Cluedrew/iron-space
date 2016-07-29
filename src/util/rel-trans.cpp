#include "rel-trans.hpp"

// rel-trans ==> RelativeTransformable

/* Unfortunatly SFML does not actually define what the default transformable
 * is, but it works out to be the identity, no nothing operation.
 */
sf::Transformable const RelativeTransformable::identity = sf::Transformable();



RelativeTransformable::RelativeTransformable () :
  sf::Transformable(), absTransform()
{}

RelativeTransformable::~RelativeTransformable ()
{}



void RelativeTransformable::update(sf::Transformable const & root)
{
  absTransform.setPosition(root.getPosition());
  absTransform.setRotation(root.getRotation());
  absTransform.setScale(root.getScale());

  absTransform.move(getPosition());
  absTransform.rotate(getRotation());
  absTransform.scale(getScale());
}

// Ported functions:
#if 0
// Add the class scope prefix.

#define WRAP_0ARG_FUNC(ret,n0,n1,n2) \
ret n0##n1##n2() { return n0##n2(); }

#define WRAP_1ARG_FUNC(ret,n0,n1,n2,a0) \
ret n0##n1##n2(a0) { return n0##n2(a0) ; }

#define WRAP_2ARG_FUNC(ret,n0,n1,n2,a0,a1) \
ret n0##n1##n2(a0,a1) { return n0##n2(a0,a1); }

#define WRAP_SETTER_BOTH(ret,n2) \
WRAP_0ARG_FUNC(ret,set,Rel,n2) WRAP_0ARG_FUNC(ret,set,Abs,n2)

WRAP_SETTER_BOTH(sf::Vector2f const &, Position)
WRAP_SETTER_BOTH(float, Rotation)
WRAP_SETTER_BOTH(sf::Vector2f const &, Scale)
WRAP_SETTER_BOTH(sf::Vector2f const &, Origin)
#endif
