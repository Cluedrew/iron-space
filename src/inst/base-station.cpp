#include "base-station.hpp"

// Implementation of BaseStation and BaseStationGraphics.

#include "core/interface.hpp"
#include "input/input-event.hpp"
#include "physics/physics-component.hpp"
#include "physics/circle-collider.hpp"
#include "graphics/graphics-component.hpp"
#include "status-display.hpp"
#include "util/transforms.hpp"



static float const rimRadius = 50;
static float const coreRadius = 10;

struct BaseStationGraphics : public GraphicsComponent {
  sf::CircleShape rim;
  sf::CircleShape core;
  sf::RectangleShape nsSpokes;
  sf::RectangleShape ewSpokes;

  BaseStationGraphics() :
    rim(rimRadius), core(coreRadius),
    nsSpokes(sf::Vector2f(5, rimRadius * 2)),
    ewSpokes(sf::Vector2f(rimRadius * 2, 5))
  {
    rim.setOrigin(rimRadius, rimRadius);
    rim.setOutlineThickness(-5);
    rim.setOutlineColor(sf::Color(128, 128, 128));
    rim.setFillColor(sf::Color::Transparent);
    core.setOrigin(coreRadius, coreRadius);
    core.setFillColor(sf::Color::White);
    nsSpokes.setOrigin(3, rimRadius);
    nsSpokes.setFillColor(sf::Color::Cyan);
    ewSpokes.setOrigin(rimRadius, 3);
    ewSpokes.setFillColor(sf::Color::Cyan);
  }

  void draw(sf::RenderTarget & target, sf::RenderStates states) const
  {
    target.draw(nsSpokes, states);
    target.draw(ewSpokes, states);
    target.draw(rim, states);
    target.draw(core, states);
  }
};

BaseStation::BaseStation(int startX, int startY) :
  Entity(xyTransformable(startX, startY),
         new PhysicsComponent(new CircleCollider(0, 0, rimRadius)),
         new BaseStationGraphics())
{}

std::string const & BaseStation::getName () const
{
  static std::string const name("Base Station");
  return name;
}

void BaseStation::display (StatusDisplay & target) const
{
  target.drawStatusBar("HP", sf::Color::Red, 100, 50);
}

bool BaseStation::innerHandleInput (InputEvent const & input)
{
  switch (input.type)
  {
  // TODO: This is not something I want to have to write for every unit.
  case InputEvent::Select:
    interface.selection.setTo(this);
    return true;
  case InputEvent::Unselect:
    interface.selection.erase(this);
    return true;
  default:
    return false;
  }
}

void BaseStation::innerUpdateAi (sf::Time const & deltaT)
{

}

void BaseStation::innerHandleCollision (GameObjectPtr & with)
{

}
