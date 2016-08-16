#include "collider-leaf.hpp"
#include <catch.hpp>

/* Tests for the collider leaf and its sub-components.
 *
 * This is all in one place to make sure I don't miss any combinations.
 * Classes that inherites directly from Collider, without going through
 * ColliderLeaf, is tested elsewhere as they (should not be) part of this
 * interlocked group.
 */

#include "circle-collider.hpp"



TEST_CASE("Testing ColliderLeaf and child-classes", "[physics]")
{
  sf::Transformable root;

  SECTION("Check Circle/Circle")
  {
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

  SECTION("Check Circle/Point")
  {}
  SECTION("Check Circle/AlignRect")
  {}
  SECTION("Check Point/Point")
  {}
  SECTION("Check Point/AlignRect")
  {}
  SECTION("Check AlignRect/AlignRect")
  {}
}
