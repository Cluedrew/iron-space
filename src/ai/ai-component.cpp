#include "ai-component.hpp"

// Implementation of the AI Component block.

#include <iostream>
#include <cmath>
#include <SFML/System/Time.hpp>
#include "../input/input-event.hpp"
#include "../game-object.hpp"



AiComponent::AiComponent ()
{}

AiComponent::~AiComponent ()
{}



void AiComponent::init (GameObject & container)
{
  container.setPosition(450, 300);
  //std::cout << "AiComponent::init" << std::endl;
}

bool AiComponent::handleInput
    (GameObject & container, InputEvent const & ievent)
{
  std::cout << "AiComponent: " << ievent << std::endl;
  return true;
}

void AiComponent::update
    (GameObject & container, sf::Time const & deltaT)
{
  static sf::Time progress = sf::seconds(0);
  //std::cout << "AiComponent Update: " << progress.asSeconds() << std::endl;

  int xCenter = 400, yCenter = 300, radius = 50;
  progress += deltaT;
  float x = xCenter + radius * cos(progress.asSeconds());
  float y = yCenter + radius * sin(progress.asSeconds());

  //std::cout << "Move to: " << x << ", " << y << std::endl;
  container.setPosition(x, y);
}
