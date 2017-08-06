#include "ai-wrapper.hpp"

// Implementation of the wrapper call backs.

#include <stdexcept>
#include "object/plane-object.hpp"



void updateLocalStore (PlaneObject * & local, GameObject & passed)
{
  if (local == &passed)
    return;

  PlaneObject * tmp = dynamic_cast<PlaneObject *>(&passed);
  if (tmp)
  {
    local = tmp;
  }
  else
  {
    throw std::logic_error("Non-PlaneObject passed to AiWrapper.");
  }
}

// see header file
void AiWrapper::init (GameObject & container)
{
  updateLocalStore(cashed, container);
}

// see header file
bool AiWrapper::handleInput (GameObject & container, InputEvent const & ievent)
{
  updateLocalStore(cashed, container);
  return cashed->innerHandleInput(ievent);
}

// see header file
void AiWrapper::update (GameObject & container, sf::Time const & deltaT)
{
  updateLocalStore(cashed, container);
  return cashed->innerUpdateAi(deltaT);
}

// see header file
void AiWrapper::handleCollision (GameObject & container, GameObjectPtr & ptr)
{
  updateLocalStore(cashed, container);
  return cashed->innerHandleCollision(ptr);
}
