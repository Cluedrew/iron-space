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
#define NAME(n0,n1,n2) RelativeTransformable::n0##n1##n2

#define WRAP_0ARG_FUNC(ret,n0,n1,n2) \
ret RelativeTransformable::n0##n1##n2() \
{ return n0##n2(); }

#define WRAP_1ARG_FUNC(ret,n0,n1,n2,a0) \
ret RelativeTransformable::n0##n1##n2(a0 an0) \
{ return n0##n2(an0) ; }

#define WRAP_2ARG_FUNC(ret,n0,n1,n2,a0,a1) \
ret RelativeTransformable::n0##n1##n2(a0 an0 ,a1 an1) \
{ return n0##n2(an0,an1); }

#define WRAP_GETTER_FUNC(ret,n2) \
ret RelativeTransformable::getRel##n2() const \
{ return get##n2(); }

#define WRAP_GETTER_BOTH(ret,n2) \
WRAP_GETTER_FUNC(ret,n2) WRAP_GETTER_FUNC(ret,n2)

WRAP_GETTER_BOTH(sf::Vector2f const &, Position)
WRAP_GETTER_BOTH(float, Rotation)
WRAP_GETTER_BOTH(sf::Vector2f const &, Scale)
WRAP_GETTER_BOTH(sf::Vector2f const &, Origin)

#define WRAP_SETTER_1ARG(n2,a0) \
WRAP_1ARG_FUNC(void,set,Rel,n2,a0)

#define WRAP_SETTER_2ARG(n2,a0,a1)
WRAP_2ARG_FUNC(void,set,Rel,n2,a0,a1)

WRAP_SETTER_2ARG(Position, float, float)
WRAP_SETTER_1ARG(Position, sf::Vector2f const &)
WRAP_SETTER_1ARG(Rotation, float)
WRAP_SETTER_2ARG(Scale, float, float)
WRAP_SETTER_1ARG(Scale, sf::Vector2f const &)
WRAP_SETTER_2ARG(Origin, float, float)
WRAP_SETTER_1ARG(Origin, sf::Vector2f const &)

#define WRAP_SHIFT_1ARG(n0,a0) \
WRAP_1ARG_FUNC(void,n0,Rel,,a0)

#define WRAP_SHIFT_2ARG(n0,a0) \
WRAP_1ARG_FUNC(void,n0,Rel,,a0)

WRAPE_SHIFT_2ARG(move, float, float)
WRAPE_SHIFT_1ARG(move, sf::Vector2f const &)
WRAPE_SHIFT_1ARG(rotate, float)
WRAPE_SHIFT_2ARG(scale, float, float)
WRAPE_SHIFT_1ARG(scale, sf::Vector2f const &)
#endif
