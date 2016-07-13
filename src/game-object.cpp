#include "game-object.hpp"

// Implementation of GameObject.

#include "game-object-ptr.hpp"


/*GameObject::GameObject (AiComponent * ai, PhysicsComponent * physics,
                        GraphicsComponent * graphics) :
  sf::Drawable(), sf::Transformable(),
  ptrsToThis(), ai(ai), physics(physics), graphics(graphics)
{}*/
GameObject::GameObject () :
  sf::Transformable(), sf::Drawable(), ptrsToThis(),
  collider(300, 300, 25), graphics(25)
{
  graphics.move(300 - 25, 300 - 25);
}

GameObject::GameObject (GameObject && other) :
  sf::Transformable(), sf::Drawable(),
  ptrsToThis(other.ptrsToThis),// ai(other.ai),
  //physics(other.physics), graphics(other.graphics)
  collider(other.collider), graphics(other.graphics)
{
  // Make sure the other's pointer list is empty (depending on if the
  // MIL does move or copy, it might already be).
  other.ptrsToThis.clear();

  // Null the other's pointers.
  //other.ai = nullptr;
  //other.physics = nullptr;
  //other.graphics = nullptr;

  // Adjust pointers.
  std::vector<GameObjectPtr*>::iterator it;
  for (it = ptrsToThis.begin() ; it != ptrsToThis.end() ; ++it)
  {
     (**it).ptr = this;
  }
}

GameObject::~GameObject ()
{
  // Manually clear this object from all the GameObjectPtrs that point at it.
  std::vector<GameObjectPtr*>::iterator it;
  for (it = ptrsToThis.begin() ; it != ptrsToThis.end() ; ++it)
  {
     (**it).ptr = nullptr;
  }

  // Destroy all the components that make up the GameObject.
  //delete ai;
  //delete physics;
  //delete graphics;
}



#if 0
// see header
bool GameObject::handleInput (InputEvent const & input)
{
  return ai->handleInput(input);
}

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
  target.draw(graphics, states);
  //states.transform *= getTransform();
  //target.draw(*graphics, states);
}
