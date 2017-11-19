#include "blinker.hpp"

// Implementation of the Blinker GameObject.

#include "physics/physics-component.hpp"
#include "physics/circle-collider.hpp"
#include "graphics/circle-graphics.hpp"
#include "util/transforms.hpp"



Blinker::Blinker (int x, int y) :
  PlaneObject(xyTransformable(x, y),
    nullptr,
    new PhysicsComponent(new CircleCollider(0, 0, 25)),
    new CircleGraphics(25)),
  sound("Metal_Beep.wav")
{}

Blinker::~Blinker ()
{}

void Blinker::overlapBegin (PlaneObject & with)
{
  // Since the class wires itself, this should never return NULL.
  CircleGraphics * graphics = getCastGraphics<CircleGraphics>();
  graphics->setColour(sf::Color::Blue);
}

void Blinker::overlapEnd (PlaneObject & with)
{
  // See above
  getCastGraphics<CircleGraphics>()->setColour(sf::Color::White);
}
