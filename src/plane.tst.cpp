#include "plane.hpp"

/* Tests for the Plane Container.
 * Currently there is not a lot to test, but I'm getting started.
 */

#include <catch.hpp>



TEST_CASE("Testing for the Plane container.", "")
{
  SECTION("Checking emplace")
  {
    Plane plane;
    plane.emplace(GameObject());
    plane.emplace();
    Plane::iterator it = plane.begin();
    Plane::iterator endOfPlane = plane.end();
    REQUIRE( it != endOfPlane );
    ++it;
    REQUIRE( it != endOfPlane );
    ++it;
    REQUIRE( it == endOfPlane );
  }
}
