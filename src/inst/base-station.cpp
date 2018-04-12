#include "base-station.hpp"

// Implementation of BaseStation and BaseStationGraphics.

#include "physics/physics-component.hpp"
#include "physics/circle-collider.hpp"
#include "graphics/graphics-component.hpp"
#include "status-display.hpp"
#include "util/transforms.hpp"



static float const rimRadius = 100;
static float const coreRadius = 10;

struct BaseStationGraphics : public GraphicsComponent {
  sf::CircleShape rim;
  sf::CircleShape core;
  sf::RectangleShape nsSpokes;
  sf::RectangleShape ewSpokes;

  BaseStationGraphics() :
    rim(rimRadius), core(coreRadius),
    nsSpokes(sf::Vector2f(5, 197)), ewSpokes(sf::Vector2f(197, 5))
  {
    rim.setOrigin(rimRadius, rimRadius);
    rim.setOutlineThickness(-5);
    rim.setOutlineColor(sf::Color(128, 128, 128));
    rim.setFillColor(sf::Color::Transparent);
    core.setOrigin(coreRadius, coreRadius);
    core.setFillColor(sf::Color::White);
    nsSpokes.setOrigin(3, 99);
    nsSpokes.setFillColor(sf::Color::Cyan);
    ewSpokes.setOrigin(99, 3);
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
         new PhysicsComponent(new CircleCollider(0, 0, 100)),
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
  // Selection has to be handled.
  return false;
}

void BaseStation::innerUpdateAi (sf::Time const & deltaT)
{

}

void BaseStation::innerHandleCollision (GameObjectPtr & with)
{

}
