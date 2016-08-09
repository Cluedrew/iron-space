#include "game-object.hpp"

// Implementation of GameObject.

#include <cassert>
#include <iostream>
#include "input/input-event.hpp"
#include "ai-component.hpp"



GameObject::GameObject () :
  sf::Transformable(), sf::Drawable(), ptrsToThis(),
  ai(nullptr), //physics(nullptr), graphics(nullptr)
  collider(0, 0, 25), graphics(25)
{
  collider.update(*this);
  graphics.setOrigin(25, 25);
}

GameObject::GameObject (AiComponent * ai) ://, PhysicsComponent * physics,
    //GraphicsComponent * graphics) :
  sf::Transformable(), sf::Drawable(), ptrsToThis(),
  ai(ai), //physics(physics), graphics(graphics)
  collider(0, 0, 25), graphics(25)
{
  collider.update(*this);
  graphics.setOrigin(25, 25);
}

GameObject::GameObject (GameObject && other) :
  sf::Transformable(), sf::Drawable(),
  ptrsToThis(other.ptrsToThis), ai(other.ai),
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
  //std::cout << "GameObject: " << input << std::endl;
  //return true;
  return ai->handleInput(*this, input);
}

// This way is definatly going to have to change.
bool GameObject::collides (GameObject const & other)
{
  return collider.collides(other.collider);
}
bool GameObject::collides (Collider const & other)
{
  return collider.collides(other);
}

// see header
void GameObject::updateAi (sf::Time const & deltaT)
{
  ai->update(*this, deltaT);
  // quick fix
  collider.update(*this);
}

#if 0
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
  states.transform *= getTransform();
  target.draw(graphics, states);
}
