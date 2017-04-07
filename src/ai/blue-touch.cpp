#include "blue-touch.hpp"

// Implementation of the BlueTouch class.

#include <cstdlib>
#include <iostream>
#include "../game-object.hpp"
#include "../graphics/circle-graphics.hpp"


BlueTouch::BlueTouch (int x, int y) :
  x(x), y(y), sound("Metal_Beep.wav"),
  contact(0)
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

CircleGraphics * getGraphics(GameObject & container)
{
  CircleGraphics * graphics =
    dynamic_cast<CircleGraphics *>(container.getGraphics());

  if (nullptr == graphics)
  {
    // Error state:
    std::cerr << "BlueTouch: GraphicsComponent to CircleGraphics cast failed."
              << std::endl;
    exit(EXIT_FAILURE);
  }

  return graphics;
}

void BlueTouch::update
    (GameObject & container, sf::Time const & deltaT)
{
  CircleGraphics * graphics = getGraphics(container);
  graphics->setColour(sf::Color::White);
  if (0 != contact)
     --contact;
}

void BlueTouch::handleCollision (GameObject & container, GameObjectPtr & ptr)
{
  CircleGraphics * graphics = getGraphics(container);
  graphics->setColour(sf::Color::Blue);

  if (0 == contact)
    sound.play();
  contact = 2;
}
