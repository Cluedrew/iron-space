#include "orbit-ai.hpp"

// Implementation of the AI Component block.

#include <iostream>
#include <cmath>
#include <SFML/System/Time.hpp>
#include "../input/input-event.hpp"
#include "../game-object.hpp"



OrbitAi::OrbitAi () :
  progress(sf::seconds(0)),
  xCenter(400), yCenter(300), radius(50)
{}

OrbitAi::~OrbitAi ()
{}



void OrbitAi::init (GameObject & container)
{
  container.setPosition(450, 300);
  //std::cout << "OrbitAi::init" << std::endl;
}

bool OrbitAi::handleInput
    (GameObject & container, InputEvent const & ievent)
{
  std::cout << "OrbitAi: " << ievent << std::endl;
  return true;
}

void OrbitAi::update
    (GameObject & container, sf::Time const & deltaT)
{
  //std::cout << "OrbitAi Update: " << progress.asSeconds() << std::endl;

  progress += deltaT;
  float x = xCenter + radius * cos(progress.asSeconds());
  float y = yCenter + radius * sin(progress.asSeconds());

  //std::cout << "Move to: " << x << ", " << y << std::endl;
  container.setPosition(x, y);
}
