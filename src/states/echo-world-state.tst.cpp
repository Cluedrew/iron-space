#include "echo-world-state.tst.hpp"
#include <catch.hpp>

// Implement the Echo (text output) WorldState

#include <cassert>
#include <sstream>
#include <ostream>
#include <SFML/System/Time.hpp>
#include "../input/input-event.hpp"



EchoWorldState::EchoWorldState () :
    echoes()
{}

EchoWorldState::~EchoWorldState ()
{}


void EchoWorldState::storeEcho (std::string const & newEcho)
/* Add an echo to the internal list of stored echoes.
 * Params: String repersenting new echo.
 */
{
  echoes.push_back(newEcho);
}


WorldState * EchoWorldState::handleInput (InputEvent const & ievent)
{
  storeEcho(toString(ievent));

  return nullptr;
}

WorldState * EchoWorldState::update (sf::Time const & deltaT)
{
  std::ostringstream out;
  out << deltaT.asMilliseconds() << " milliseconds";
  storeEcho(out.str());

  return nullptr;
}

void EchoWorldState::draw
    (sf::RenderTarget & target, sf::RenderStates states) const
{}


bool EchoWorldState::hasEchoes () const
{
  return !echoes.empty();
}

std::string const & EchoWorldState::peekEcho () const
{
  assert(!echoes.empty());
  return echoes.front();
}

std::string EchoWorldState::popEcho ()
{
  assert(!echoes.empty());
  std::string fin = echoes.front();
  echoes.pop_front();
  return fin;
}


TEST_CASE("Testing the EchoWorldState", "[states][testing]")
{
  EchoWorldState state;

  SECTION("Check handleInput")
  {
    InputEvent ievent = {.type = InputEvent::Select};
    ievent.pos.x = 10;
    ievent.pos.y = 100;
    state.handleInput(ievent);
    REQUIRE( "Select(x=10 y=100)" == state.peekEcho() );
  }

  SECTION("Check update")
  {
    sf::Time tenth = sf::milliseconds(100);
    state.update(tenth);
    REQUIRE( "100 milliseconds" == state.peekEcho() );
  }

  //SECTION("Check draw") ... Except there is nothing to test.
}
