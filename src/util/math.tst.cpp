#include "math.hpp"
#include "catch.hpp"

/* Some trivial tests for util/math.
 * Although the tests have some value it is mostly an experament with catch.
 */



TEST_CASE("Check diff function", "[util]")
{
  SECTION("diff<int>")
  {
    REQUIRE( 6 == diff<int>(1, 7) );
    REQUIRE( 6 == diff<int>(7, 1) );
  }
  SECTION("diff<float>")
  {
    REQUIRE( 4.25f == diff<float>(3.0f, 7.25f) );
    REQUIRE( 4.25f == diff<float>(7.25f, 3.0f) );
  }
  SECTION("diff<double>")
  {
    REQUIRE( 4.875 == diff<double>(5.0, 9.875) );
    REQUIRE( 4.875 == diff<double>(9.875, 5.0) );
    REQUIRE( Approx(4.825) == diff<double>(5.0, 9.825) );
  }
}

TEST_CASE("Test limitValue function", "[util]")
{
  SECTION("limitValue<int>")
  {
    REQUIRE( 3 == limitValue<int>(2, 3, 4) );
    REQUIRE( 2 == limitValue<int>(2, 1, 4) );
    REQUIRE( 4 == limitValue<int>(2, 5, 4) );
    REQUIRE( 2 == limitValue<int>(2, 2, 4) );
    REQUIRE( 4 == limitValue<int>(2, 4, 4) );
  }
  SECTION("limitValue<float>")
  {
    REQUIRE( 3.0f == limitValue<float>(1.5f, 3.0f, 4.75f) );
  }
}
