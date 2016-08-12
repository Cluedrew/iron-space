#include "game-object.hpp"

// Implementation of GameObject.

#include <cassert>
#include <iostream>
#include "input/input-event.hpp"
#include "ai/ai-component.hpp"
#include "physics/physics-component.hpp"
#include "graphics/graphics-component.hpp"



GameObject::GameObject () :
  sf::Transformable(), sf::Drawable(), ptrsToThis(),
  ai(nullptr), physics(nullptr), graphics(nullptr)
{
  //ai->init(*this); // !? This actually worked for a while. WHY?
}

GameObject::GameObject (AiComponent * ai, PhysicsComponent * physics,
    GraphicsComponent * graphics) :
  sf::Transformable(), sf::Drawable(), ptrsToThis(),
  ai(ai), physics(physics), graphics(graphics)
{
  ai->init(*this);
  physics->updatePosition(*this);
}

GameObject::GameObject (GameObject && other) :
  sf::Transformable(), sf::Drawable(),
  ptrsToThis(other.ptrsToThis), ai(other.ai),
  physics(other.physics), graphics(other.graphics)
{
  // How do you copy over the transformable.
  assert(other.ptrsToThis.empty());
  GameObjectPtr::setAll(this, ptrsToThis);
  other.ai = nullptr;
  other.physics = nullptr;
  other.graphics = nullptr;
}

GameObject::~GameObject ()
{
  GameObjectPtr::setAll(nullptr, ptrsToThis);
  delete ai;
  delete physics;
  delete graphics;
}



// see header
bool GameObject::handleInput (InputEvent const & input)
{
  return ai->handleInput(*this, input);
}

// This way is definatly going to have to change.
bool GameObject::collides (GameObject const & other)
{
  return physics->collides(*other.physics);
}
bool GameObject::collides (Collider const & other)
{
  return physics->collides(other);
}

// see header
void GameObject::updateAi (sf::Time const & deltaT)
{
  ai->update(*this, deltaT);
  // quick fix
  physics->updatePosition(*this);
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
  target.draw(*graphics, states);
}
