#include "collider-leaf.hpp"
#include <catch.hpp>

/* Tests for the collider leaf and its sub-components.
 *
 * This is all in one place to make sure I don't miss any combinations.
 * Classes that inherites directly from Collider, without going through
 * ColliderLeaf, is tested elsewhere as they (should not be) part of this
 * interlocked group.
 *
 * TODO Test all six combinations, with and without transformations.
 */

#include "circle-collider.hpp"
#include "point-collider.hpp"
#include "align-rect-collider.hpp"



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
  {
    CircleCollider cA(10, 10, 5);
    cA.update(root);
    PointCollider pA(10, 10);
    CHECK( cA.collides(pA) );
  }

  SECTION("Check Circle/AlignRect")
  {
    CircleCollider cLeft(0, 5, 1);
    cLeft.update(root);
    AlignRectCollider rSquare(1, 4, 4, 4);
    CircleCollider cTopRight(-2, 12, 5);
    cTopRight.update(root);
    CircleCollider cBottom(2, 9.5, 1.5);
    cBottom.update(root);
    AlignRectCollider rTall(2, 0, 1, 10);

    SECTION("Overlaps")
    {
      CHECK( rTall.collides(cBottom) );
    }

    SECTION("Edges")
    {
      CHECK_FALSE( rSquare.collides(cLeft) );
      CHECK_FALSE( rSquare.collides(cTopRight) );
      CHECK_FALSE( cBottom.collides(rSquare) );
    }

    SECTION("Seperate")
    {
      CHECK_FALSE( cLeft.collides(rTall) );
    }
  }

  SECTION("Check Point/Point")
  {
    PointCollider pA(1, 3);
    PointCollider pB(3, 1);
    PointCollider pC(1, 3);
    CHECK_FALSE( pA.collides(pB) );
    CHECK( pA.collides(pC) );
  }

  SECTION("Check Point/AlignRect")
  {
    AlignRectCollider rect(10, 10, 10, 10);
    PointCollider pA(15, 15);
    CHECK( rect.collides(rect) );
  }

  SECTION("Check AlignRect/AlignRect")
  {
    AlignRectCollider rLeft(10, 5, 5, 5);
    AlignRectCollider rMid(10, 7, 5, 5);
    AlignRectCollider rRight(7, 12, 5, 5);
    AlignRectCollider rDown(12, 11, 5, 5);

    SECTION("Overlaps")
    {
      CHECK( rLeft.collides(rMid) );
    }

    SECTION("Edges")
    {
      CHECK_FALSE( rMid.collides(rRight) );
      CHECK_FALSE( rDown.collides(rRight) );
    }

    SECTION("Seperate")
    {
      CHECK_FALSE( rDown.collides(rLeft) );
    }
  }
}

TEST_CASE("Testing sf::Rect::overlap", "[physics][sfml]")
{
  sf::FloatRect rectA(10, 10, 10, 10);
  sf::FloatRect rectB(15, 15, 10, 10);
  sf::FloatRect rectC(20, 10, 10, 10);
  sf::FloatRect rectD(20, 20, 10, 10);
  REQUIRE( rectA.intersects(rectB) );
  REQUIRE_FALSE( rectA.intersects(rectC) );
  REQUIRE_FALSE( rectA.intersects(rectD) );
}
