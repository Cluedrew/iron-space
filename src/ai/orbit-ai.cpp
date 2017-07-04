#include "orbit-ai.hpp"

// Implementation of the AI Component block.

#include <iostream>
#include <cmath>
#include <SFML/System/Time.hpp>
#include "../input/input-event.hpp"
#include "../object/game-object.hpp"



OrbitAi::OrbitAi () :
  progress(sf::seconds(0)), moving(true),
  xCenter(400), yCenter(300), radius(50)
{}

OrbitAi::OrbitAi (int x, int y, int r) :
  progress(sf::seconds(0)), moving(true),
  xCenter(x), yCenter(y), radius(r)
{}

OrbitAi::~OrbitAi ()
{}



void OrbitAi::init (GameObject & container)
{
  container.setPosition(450, 300);
}

bool OrbitAi::handleInput
    (GameObject & container, InputEvent const & ievent)
{
  if (InputEvent::Select == ievent.type)
  {
    moving = !moving;
    return true;
  }
  return false;
}

void OrbitAi::update
    (GameObject & container, sf::Time const & deltaT)
{
  if (moving)
  {
    progress += deltaT;
    float x = xCenter + radius * cos(progress.asSeconds());
    float y = yCenter + radius * sin(progress.asSeconds());

    container.setPosition(x, y);
  }
}
