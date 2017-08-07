#include "chase-orb.hpp"

// Implementation of ChaseOrb PlaneObject.

#include <cmath>
#include "input/input-event.hpp"
#include "ai/ai-wrapper.hpp"
#include "physics/physics-component.hpp"
#include "physics/circle-collider.hpp"
#include "graphics/circle-graphics.hpp"
#include "util/transforms.hpp"



// see header
ChaseOrb::ChaseOrb() :
    PlaneObject(
      new AiWrapper(),
      new PhysicsComponent(new CircleCollider(0, 0, 25)),
      new CircleGraphics(25, sf::Color::Green)),
    target(0, 0)
{}

// see header
ChaseOrb::ChaseOrb(int x, int y) :
    PlaneObject(
      xyTransformable(x, y),
      new AiWrapper(),
      new PhysicsComponent(new CircleCollider(x, y, 25)),
      new CircleGraphics(25, sf::Color::Green)),
    target(x, y)
{}

// see header
ChaseOrb::ChaseOrb(sf::Vector2<int> xy) :
    PlaneObject(
      xyTransformable(xy.x, xy.y),
      new AiWrapper(),
      new PhysicsComponent(new CircleCollider(xy.x, xy.y, 25)),
      new CircleGraphics(25, sf::Color::Green)),
    target(xy)
{}

// see header
bool ChaseOrb::innerHandleInput (InputEvent const & input)
{
  switch (input.type)
  {
  case InputEvent::Select:
    if (CircleGraphics * circle = dynamic_cast<CircleGraphics*>(getGraphics()))
    {
      circle->setColour(sf::Color::Blue);
    }
    return true;
  case InputEvent::Unselect:
    if (CircleGraphics * circle = dynamic_cast<CircleGraphics*>(getGraphics()))
    {
      circle->setColour(sf::Color::Green);
    }
    return true;
  case InputEvent::Point:
    target = sf::Vector2<int>(input.pos.x, input.pos.y);
    return true;
  // Unselect event.
  default:
    return false;
  }
}

// see header
void ChaseOrb::innerUpdateAi (sf::Time const & deltaT)
{
  sf::Vector2<float> const & here = getPosition();
  sf::Vector2<float> const ftarget(target);
  if (here == ftarget)
    return;

  float dx = target.x - here.x;
  float dy = target.y - here.y;
  float distsqr = dx * dx + dy * dy;

  static float speed = 250;
  float movement = speed * deltaT.asSeconds();

  if (distsqr < movement * movement)
  {
    setPosition(ftarget);
    return;
  }

  float dist = sqrt(distsqr);

  // Is there a good way to arrange this for floating point error?
  move(dx / dist * movement, dy / dist * movement);
}

// see header
void ChaseOrb::innerHandleCollision (GameObjectPtr & with)
{
  // Do nothing with any collision.
}
