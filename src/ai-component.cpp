#include "ai-component.hpp"

// Implementation of the AI Component block.

#include <iostream>
#include <SFML/System/Time.hpp>
#include "input/input-event.hpp"



AiComponent::AiComponent ()
{}

AiComponent::~AiComponent ()
{}

bool AiComponent::handleInput (InputEvent const & ievent)
{
  std::cout << "AiComponent: " << ievent << std::endl;
  return true;
}

void AiComponent::update (sf::Time const & deltaT)
{}
