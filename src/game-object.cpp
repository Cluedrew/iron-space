#include "game-object.hpp"

// Implementation of GameObject.

#include <cassert>
#include <iostream>
#include "input/input-event.hpp"



/*GameObject::GameObject (AiComponent * ai, PhysicsComponent * physics,
                        GraphicsComponent * graphics) :
  sf::Drawable(), sf::Transformable(),
  ptrsToThis(), ai(ai), physics(physics), graphics(graphics)
{}*/
GameObject::GameObject () :
  sf::Transformable(), sf::Drawable(), ptrsToThis(),
  collider(300, 300, 25), graphics(25)
{
  collider.update(*this);
  graphics.move(300 - 25, 300 - 25);
}

GameObject::GameObject (GameObject && other) :
  sf::Transformable(), sf::Drawable(),
  ptrsToThis(other.ptrsToThis),// ai(other.ai),
  //physics(other.physics), graphics(other.graphics)
  collider(other.collider), graphics(other.graphics)
{
  assert(other.ptrsToThis.empty());
  GameObjectPtr::setAll(this, ptrsToThis);
}

GameObject::~GameObject ()
{
  GameObjectPtr::setAll(nullptr, ptrsToThis);
}



// see header
bool GameObject::handleInput (InputEvent const & input)
{
  std::cout << "GameObject: " << input << std::endl;
  return true;
  //return ai->handleInput(input);
}

// This way is definatly going to have to change.
bool GameObject::collides (GameObject const & other)
{
  return collider.collides(other.collider);
}
bool GameObject::collides (Collider const & other)
{
  return collider.collides(collider);
}

#if 0
// see header
void GameObject::updateAi (sf::Time const & deltaT)
{
  ai->update(deltaT);
}

// see header
void GameObject::handleMessage (MessageEvent const & msg)
{
  ai->handleMessage(msg);
}

// see header
void GameObject::updatePhysics (sf::Time const & deltaT)
{
  physics->update(this, deltaT);
}

// see header
void GameObject::handleCollision (GameObjectPtr with)
{
  ai->handleCollision(with);
}
#endif

// see header
void GameObject::draw (sf::RenderTarget & target, sf::RenderStates states) const
{
  //states.transform *= getTransform();
  target.draw(graphics, states);
}
