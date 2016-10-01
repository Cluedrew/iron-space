#include "running-state.hpp"

// Implementation of the World/Global/Game State.

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "../input/input-event.hpp"
#include "../ai/orbit-ai.hpp"
#include "../physics/physics-component.hpp"
#include "../physics/circle-collider.hpp"
#include "../graphics/circle-graphics.hpp"
#include "pause-screen.hpp"



RunningState::RunningState () :
  map()
{
  map.emplace(GameObject(new OrbitAi(),
                new PhysicsComponent(new CircleCollider(0, 0, 25)),
                new CircleGraphics(25)));
}

RunningState::~RunningState ()
{}



// see header
WorldState * RunningState::handleInput (InputEvent const & ievent)
{
  switch (ievent.type)
  {
  case InputEvent::Select:
    map.handleInput(ievent);
    break;

  case InputEvent::Pause:
    return new PauseScreen(this);

  case InputEvent::Quit:
  case InputEvent::Cap:
    break;
  }

  return nullptr;
}

// see header
WorldState * RunningState::update (sf::Time const & deltaT)
{
  PlaneDrawable<GameObject>::iterator it;
  for (it = map.begin() ; it != map.end() ; ++it)
    it->updateAi(deltaT);

  return nullptr;
}

// see header
void RunningState::draw (sf::RenderTarget & target,
    sf::RenderStates states) const
{
  target.draw(map, states);
}
