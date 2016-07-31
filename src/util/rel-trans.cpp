#include "rel-trans.hpp"

// rel-trans ==> RelativeTransformable

#include <SFML/Graphics/Transform.hpp>

/* Unfortunatly SFML does not actually define what the default transformable
 * is, but it works out to be the identity, no nothing operation.
 */
sf::Transformable const RelativeTransformable::identity = sf::Transformable();



// see header
RelativeTransformable::RelativeTransformable () :
  sf::Transformable(), absTransform()
{}

RelativeTransformable::~RelativeTransformable ()
{}



// see header
void RelativeTransformable::update(sf::Transformable const & parent)
{
  absTransform.setPosition(parent.getPosition());
  absTransform.setRotation(parent.getRotation());
  absTransform.setScale(parent.getScale());

  absTransform.move(getPosition());
  absTransform.rotate(getRotation());
  absTransform.scale(getScale());
}

// Ported functions: see header for documentation
// The macros do save code.

#define PORT_GETTERS(ret,name) \
ret RelativeTransformable::getRel##name() const \
{ return get##name(); } \
ret RelativeTransformable::getAbs##name() const \
{ return absTransform.get##name(); }

PORT_GETTERS(sf::Vector2f const &,Position)
PORT_GETTERS(float,Rotation)
PORT_GETTERS(sf::Vector2f const &,Scale)
PORT_GETTERS(sf::Vector2f const &,Origin)
PORT_GETTERS(sf::Transform const &,Transform)
PORT_GETTERS(sf::Transform const &,InverseTransform)

#define PORT_SETTER_1(name,a0) \
void RelativeTransformable::setRel##name(a0 arg0) \
{ return set##name(arg0); }

#define PORT_SETTER_2(name,a0,a1) \
void RelativeTransformable::setRel##name(a0 arg0, a1 arg1) \
{ return set##name(arg0, arg1); }

#define PORT_SETTERS(name) \
PORT_SETTER_2(name,float,float) PORT_SETTER_1(name,sf::Vector2f const &)

PORT_SETTERS(Position)
PORT_SETTER_1(Rotation,float)
PORT_SETTERS(Scale)
PORT_SETTERS(Origin)

#define PORT_SHIFT_1(name,a0) \
void RelativeTransformable::name##Rel(a0 arg0) \
{ return name(arg0); }

#define PORT_SHIFT_2(name,a0,a1) \
void RelativeTransformable::name##Rel(a0 arg0, a1 arg1) \
{ return name(arg0, arg1); }

#define PORT_SHIFTS(name) \
PORT_SHIFT_2(name,float,float) PORT_SHIFT_1(name,sf::Vector2f const &)

PORT_SHIFTS(move)
PORT_SHIFT_1(rotate,float)
PORT_SHIFTS(scale)
