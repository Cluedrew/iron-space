/* Tests the GenEventHandler with an EventStream. Because the EventHandler is
 * wired up to the SFML Window we can't test it automatically, so this is used
 * instead and the EventHandler itself is kept as thin as possible.
 */

#include <catch.hpp>

#include "event-stream.tst.hpp"
#include "gen-event-handler.hpp"
#include "../plane.hpp"

typedef GenEventHandler<EventStream> TestEventHandler;



TEST_CASE("EventHandler test", "[input]")
{
  TestEventHandler handler;
  EventStream stream;
  Plane blankplane;

  SECTION("No Events")
  {
    Response re = handler.pollEvents(stream, blankplane);
    REQUIRE( Response::Done == re.type );
  }

  SECTION("Closed to Quit")
  {
    stream.addClosed();
    Response re = handler.pollEvents(stream, blankplane);
    REQUIRE( Response::Quit == re.type );
    re = handler.pollEvents(stream, blankplane);
    REQUIRE( Response::Done == re.type );
  }
}
