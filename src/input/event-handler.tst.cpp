/* Tests the EventHandler through the GenEventHandler with an EventStream.
 * The EventStream is required to produce stable and automated input.
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
    REQUIRE(handler.pollEvents(stream));
  }
}
