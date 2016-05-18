#define CATCH_CONFIG_MAIN
#include "catch.hpp"

/* Some trivial tests for util/math.
 * Although the tests have some value it is mostly an experament with catch.
 */

#include "../src/util/math.hpp"



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
