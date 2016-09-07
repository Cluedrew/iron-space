#include "world-machine.hpp"
#include <catch.hpp>

// Testing for the WorldMachine.

#include "null-world-state.hpp"



TEST_CASE("Testing for the WorldMachine", "[states]")
{
  SECTION("Initialization")
  {
    NullWorldState * state = new NullWorldState();
    WorldMachine machine(state);
    REQUIRE( &*machine == state );
  }

  SECTION("Transition between WorldStates")
  {
    WorldMachine machine(new NullWorldState());
    NullWorldState * state = new NullWorldState();
    machine.update(state);
    REQUIRE( &*machine == state );

    state = new NullWorldState();
    machine.changeState(state);
    REQUIRE( machine.get() == state );
  }

  SECTION("Remain in same state with nullptr")
  {
    NullWorldState * state = new NullWorldState();
    WorldMachine machine(state);
    machine.update(nullptr);
    REQUIRE( &*machine == state );
  }
}
