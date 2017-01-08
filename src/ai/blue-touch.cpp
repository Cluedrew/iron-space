#include "blue-touch.hpp"

// Implementation of the BlueTouch class.

#include "../game-object.hpp"


BlueTouch::BlueTouch (int x, int y) :
  x(x), y(y)
{}

BlueTouch::~BlueTouch ()
{}

void BlueTouch::init (GameObject & container)
{
  container.setPosition(x, y);
}

bool BlueTouch::handleInput
    (GameObject & container, InputEvent const & ievent)
{
  return false;
}

void BlueTouch::update
    (GameObject & container, sf::Time const & deltaT)
{
  // Colour change?
}

