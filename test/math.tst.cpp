// Another trival test for util/math

#include "catch.hpp"

#include "../src/util/math.hpp"

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
