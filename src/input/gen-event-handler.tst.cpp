/* Tests the GenEventHandler with an EventStream. Because the EventHandler is
 * wired up to the SFML Window we can't test it automatically, so this is used
 * instead and the EventHandler itself is kept as thin as possible.
 */

#include <catch.hpp>

#include "event-stream.tst.hpp"
#include "gen-event-handler.hpp"

typedef GenEventHandler<EventStream> TestEventHandler;



TEST_CASE("EventHandler test", "[input]")
{
  TestEventHandler handler;
  EventStream stream;

  SECTION("No Events")
  {
    Response re = handler.pollEvents(stream);
    REQUIRE( Response::Done == re.type );
  }

  /*SECTION("Closed to Quit")
  {
    Response re = handler.pollEvents(stream);
    REQUIRE( Response::Quit == re.type );
  }*/
}
