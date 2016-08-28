#include "echo-world-state.tst.hpp"
#include <catch.hpp>

// Implement the Echo (text output) WorldState

#include <ostream>
#include <SFML/System/Time.hpp>
#include "../input/input-event.hpp"



EchoWorldState::EchoWorldState (std::ostream & out) :
    out(out)
{}

EchoWorldState::~EchoWorldState ()
{}

void EchoWorldState::handleInput (InputEvent const & ievent)
{
  out << ievent << std::endl;
}

void EchoWorldState::update (sf::Time const & deltaT)
{
  out << deltaT.asMilliseconds() << " milliseconds" << std::endl;
}

void EchoWorldState::draw
    (sf::RenderTarget & target, sf::RenderStates states) const
{}



#include <sstream>

TEST_CASE("Testing the EchoWorldState", "[states][testing]")
{
  std::ostringstream echoed;
  EchoWorldState state(echoed);

  SECTION("Check handleInput")
  {
    InputEvent ievent = {.type = InputEvent::Select};
    ievent.pos.x = 10;
    ievent.pos.y = 100;
    state.handleInput(ievent);
    REQUIRE( "Select(x=10 y=100)\n" == echoed.str() );
  }

  SECTION("Check update")
  {
    sf::Time tenth = sf::milliseconds(100);
    state.update(tenth);
    REQUIRE( "100 milliseconds\n" == echoed.str() );
  }

  //SECTION("Check draw") {}
}
