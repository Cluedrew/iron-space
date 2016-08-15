#include "circle-collider.hpp"

/* Tests for the CircleCollider.
 *
 * TODO Go over all of this and adjust it for the new final collider format.
 */

#include <catch.hpp>



TEST_CASE("CircleCollider Tests")
{
  sf::Transformable root;

  CircleCollider cA(10, 10, 5);
  cA.update(root);
  CircleCollider dot(13, 6, 0);
  dot.update(root);
  CircleCollider cB(0, 10, 10);
  cB.update(root);
  CircleCollider cC(20, 10, 5);
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
    CircleCollider dot2(9, 9, 0);
    dot2.update(root);
    CHECK_FALSE( dot.collides(dot2) );
  }
}
