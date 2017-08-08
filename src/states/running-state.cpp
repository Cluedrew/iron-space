#include "running-state.hpp"

// Implementation of the World/Global/Game State.

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "input/input-event.hpp"
#include "ai/orbit-ai.hpp"
#include "ai/blue-touch.hpp"
#include "physics/physics-component.hpp"
#include "physics/circle-collider.hpp"
#include "graphics/circle-graphics.hpp"
#include "pause-screen.hpp"
#include "inst/chase-orb.hpp"



RunningState::RunningState () :
  map(), bgm(), selected()
{
  map.emplace(PlaneObject(new OrbitAi(),
                new PhysicsComponent(new CircleCollider(0, 0, 25)),
                new CircleGraphics(25)));
  map.emplace(PlaneObject(new BlueTouch(315, 300),
                new PhysicsComponent(new CircleCollider(0, 0, 25)),
                new CircleGraphics(25)));
  map.insert(new ChaseOrb(25, 25));
  bgm.openFromFile("rsrc/music/Laser_Groove.wav");
  bgm.play();
}

RunningState::~RunningState ()
{}



// see header
void RunningState::start ()
{
  bgm.play();
}

// see header
WorldState * RunningState::handleInput (InputEvent const & ievent)
{
  switch (ievent.type)
  {
  case InputEvent::Select:
    {
      InputEvent unselect = {.type = InputEvent::Unselect};
      for (auto&& object : selected)
        object->handleInput(unselect);
    }
    map.handleInput(ievent);
    {
      PointCollider click(ievent.pos.x, ievent.pos.y);
      selected = map.overlapping(click);
    }
    break;

  case InputEvent::Unselect:
    // Currently just all, perhaps an unselection range could be used.
    selected.clear();
    break;

  case InputEvent::Pause:
    // Currently, I don't have a way to cleanly restart this after a pause.
    bgm.pause();
    return idStart(new PauseScreen(this));

  case InputEvent::Point:
    for (auto&& object : selected)
    {
      object->handleInput(ievent);
    }
    break;

  case InputEvent::Quit:
  case InputEvent::Cap:
    break;
  }

  return this;
}

// see header
WorldState * RunningState::update (sf::Time const & deltaT)
{

  PlaneDrawable<PlaneObject>::iterator it;
  for (it = map.begin() ; it != map.end() ; ++it)
    it->updateAi(deltaT);

  map.resolveCollisions();

  return this;
}

// see header
void RunningState::draw (sf::RenderTarget & target,
    sf::RenderStates states) const
{
  target.draw(map, states);
}
