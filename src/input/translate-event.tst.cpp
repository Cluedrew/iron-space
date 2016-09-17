#include "translate-event.hpp"
#include <catch.hpp>

/* Tests the translateEvent and pollTranslateEvent functions using an
 * EventStream helper. This is because the SFML window can't be seperated from
 * the real input, so the manual stream is used instead.
 */

#include "event-stream.tst.hpp"



TEST_CASE("translateEvent and tests", "[input]")
{
  // TODO
}
