#include "running-state.hpp"
#include <catch.hpp>

/* I'm not actually sure if I can meaningfully test this, but I'm getting
 * errors so I will try. Well right now all I can do is see if it doesn't
 * crash.
 */

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include "input/input-event.hpp"



TEST_CASE("Checking the running state.", "[states]")
{
  //RunningState * state = RunningState::idStart(new RunningState());
  RunningState * state = new RunningState();
  state->start();

  SECTION("Check RunningState::handleInput")
  {
    InputEvent event;
    // TODO
  }

  SECTION("Check RunningState::update")
  {
    sf::Time time = sf::milliseconds(20);
    state->update(time);
  }

  SECTION("Check RunningState::draw")
  {
    sf::RenderTexture target;
    target.create(800, 600);
    target.draw(*state);
  }
}
