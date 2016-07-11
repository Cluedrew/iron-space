#include "collider.hpp"

/* Tests for the Collider. It may be temperary, but it is also tested.
 */

#include <catch.hpp>



TEST_CASE("Collider Tests")
{
  Collider cA(10, 10, 5);
  Collider dot(13, 6, 0);
  Collider cB(0, 10, 10);
  Collider cC(20, 10, 5);

  SECTION("Overlaps")
  {
    CHECK(cA.collides(cB));
    CHECK(dot.collides(dot));
  }

  SECTION("Edges")
  {
    CHECK(cA.collides(dot));
    CHECK(cC.collides(cA));
  }

  SECTION("Seperate")
  {
    CHECK_FALSE(cB.collides(cC));
  }
}
