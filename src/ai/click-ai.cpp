#include "click-ai.hpp"

// Implementation of the ClickAi

#include "input/input-event.hpp"



// see header
ClickAi::ClickAi (Command * onSelect_) :
    onSelect(onSelect_)
{}


ClickAi::~ClickAi ()
{
  delete onSelect;
}

void ClickAi::init (GameObject & container)
{}

bool ClickAi::handleInput (GameObject & container, InputEvent const & ievent)
{
  if (InputEvent::Select == ievent.type)
  {
    (*onSelect)();
    return true;
  }
  return false;
}

void ClickAi::update (GameObject & container, sf::Time const & deltaT)
{}
