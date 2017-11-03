#include "game-object.hpp"

// Implementation of GameObject.

#include <cassert>
#include <iostream>
#include "input/input-event.hpp"
#include "ai/ai-component.hpp"
#include "physics/physics-component.hpp"
#include "graphics/graphics-component.hpp"



GameObject::GameObject (AiComponent * ai, PhysicsComponent * physics,
    GraphicsComponent * graphics) :
  sf::Transformable(), sf::Drawable(), ptrsToThis(), controlFlagSet(0),
  ai(ai), physics(physics), graphics(graphics)
{
  ai->init(*this);
  physics->updatePosition(*this);
}

GameObject::GameObject (sf::Transformable const & start, AiComponent * ai,
    PhysicsComponent * physics, GraphicsComponent * graphics) :
  sf::Transformable(start), sf::Drawable(), ptrsToThis(), controlFlagSet(0),
  ai(ai), physics(physics), graphics(graphics)
{
  ai->init(*this);
  physics->updatePosition(*this);
}

GameObject::GameObject (GameObject && other) :
  sf::Transformable(other), sf::Drawable(),
  ptrsToThis(other.ptrsToThis), controlFlagSet(other.controlFlagSet),
  ai(other.ai), physics(other.physics), graphics(other.graphics)
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
bool GameObject::receiveInput (InputEvent const & input)
{
  return ai->handleInput(*this, input);
}

// This way is definatly going to have to change.
bool GameObject::collides (GameObject const & other) const
{
  return physics->collides(*other.physics);
}
bool GameObject::collides (Collider const & other) const
{
  return physics->collides(other);
}

// see header
void GameObject::updateStep (sf::Time const & deltaT)
{
  update(deltaT);

  // Might have to double buffer this some day.
  if (getFlag(UpdatePhysics))
    physics->updatePosition(*this);
}

GraphicsComponent * GameObject::getGraphics ()
{
  return graphics;
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
#endif

// see header
void GameObject::handleCollision (GameObjectPtr & with)
{
  ai->handleCollision(*this, with);
}

// see header (hook default)
void GameObject::draw (sf::RenderTarget & target, sf::RenderStates states) const
{
  if (graphics)
  {
    states.transform *= getTransform();
    target.draw(*graphics, states);
  }
}

// see header (hook default)
void GameObject::update (sf::Time const & deltaT)
{
  if (ai) ai->update(*this, deltaT);
}
