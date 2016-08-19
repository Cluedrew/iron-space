#include "gen-event-handler.hpp"
#include <catch.hpp>

/* Tests the GenEventHandler with an EventStream. Because the EventHandler is
 * wired up to the SFML Window we can't test it automatically, so this is used
 * instead and the EventHandler itself is kept as thin as possible.
 */

#include "event-stream.tst.hpp"
#include "../states/null-world-state.hpp"

typedef GenEventHandler<EventStream> TestEventHandler;



TEST_CASE("EventHandler test", "[input]")
{
  TestEventHandler handler;
  EventStream stream;
  NullWorldState state;

  SECTION("No Events")
  {
    Response re = handler.pollEvents(stream, state);
    REQUIRE( Response::Done == re.type );
  }

  SECTION("Closed to Quit")
  {
    stream.addClosed();
    Response re = handler.pollEvents(stream, state);
    REQUIRE( Response::Quit == re.type );
    re = handler.pollEvents(stream, state);
    REQUIRE( Response::Done == re.type );
  }
}
