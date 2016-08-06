#include "collider.hpp"

/* Tests for the Collider. It may be temperary, but it is also tested.
 */

#include <catch.hpp>



TEST_CASE("Collider Tests")
{
  sf::Transformable root;

  Collider cA(10, 10, 5);
  cA.update(root);
  Collider dot(13, 6, 0);
  dot.update(root);
  Collider cB(0, 10, 10);
  cB.update(root);
  Collider cC(20, 10, 5);
  cC.update(root);

  SECTION("Overlaps")
  {
    CHECK( cA.collides(cB) );
    CHECK( dot.collides(dot) );
  }

  SECTION("Edges")
  {
    CHECK( cA.collides(dot) );
    CHECK( cC.collides(cA) );
  }

  SECTION("Seperate")
  {
    CHECK_FALSE( cB.collides(cC));
    Collider dot2(9, 9, 0);
    dot2.update(root);
    CHECK_FALSE( dot.collides(dot2) );
  }
}
