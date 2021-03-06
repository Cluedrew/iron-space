#include "running-state.hpp"

// Implementation of the World/Global/Game State.

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "input/input-event.hpp"
#include "object/plane-object.hpp"
#include "object/widget.hpp"
#include "ai/orbit-ai.hpp"
#include "ai/blue-touch.hpp"
#include "physics/physics-component.hpp"
#include "physics/circle-collider.hpp"
#include "graphics/circle-graphics.hpp"
#include "pause-screen.hpp"
#include "inst/chase-orb.hpp"
#include "inst/blinker.hpp"
#include "inst/status-display.hpp"
#include "inst/base-station.hpp"



RunningState::RunningState () :
  map(), hud(), bgm(), selected()
{
  map.emplace(PlaneObject(new OrbitAi(),
                new PhysicsComponent(new CircleCollider(0, 0, 25)),
                new CircleGraphics(25)));
  map.emplace(PlaneObject(new BlueTouch(315, 300),
                new PhysicsComponent(new CircleCollider(0, 0, 25)),
                new CircleGraphics(25)));
  // TODO: Using this causes a Segmentation fault, look into that.
  //map.insert(new Blinker(315, 300));
  map.insert(new ChaseOrb(25, 25));

  map.insert(new BaseStation(450, 200));

  hud.insert(new StatusDisplay());

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
        object->receiveInput(unselect);
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
    bgm.pause();
    return idStart(new PauseScreen(this));

  case InputEvent::Point:
    for (auto&& object : selected)
    {
      object->receiveInput(ievent);
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
  for (PlaneObject & object : map)
    object.updateStep(deltaT);

  map.resolveCollisions();

  for (Widget & object : hud)
    object.updateStep(deltaT);

  return this;
}

// see header
void RunningState::draw (sf::RenderTarget & target,
    sf::RenderStates states) const
{
  target.draw(map, states);
  target.draw(hud, states);
}
