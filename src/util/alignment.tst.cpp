#include "alignment.hpp"
#include <catch.hpp>

/* Tests for the alignment types and their helpers.
 * The tests for the basic operations are quite extencive because they
 * involve casts and casts make me uncomfortable.
 */

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>



#define VC(name) VerticalAlignment::name
#define HC(name) HorizontalAlignment::name
#define VH(vname,hname) Alignment2D::vname##hname

#define CROSS_NAME_MATCH(v, h) crossAlign(VC(v), HC(h)) == VH(v,h)
#define VCOMP_NAME_MATCH(v, h) VC(v) == verticalAlignmentComponent(VH(v,h))
#define HCOMP_NAME_MATCH(v, h) HC(h) == horizontalAlignmentComponent(VH(v,h))



TEST_CASE("Tests for Alignment types and helpers", "[util]")
{
  SECTION("Check translations between types of alignments.")
  {
    // Yes. All 27 cases.
    CHECK( CROSS_NAME_MATCH(Top, Left) );
    CHECK( VCOMP_NAME_MATCH(Top, Left) );
    CHECK( HCOMP_NAME_MATCH(Top, Left) );
    CHECK( CROSS_NAME_MATCH(Top, Center) );
    CHECK( VCOMP_NAME_MATCH(Top, Center) );
    CHECK( HCOMP_NAME_MATCH(Top, Center) );
    CHECK( CROSS_NAME_MATCH(Top, Right) );
    CHECK( VCOMP_NAME_MATCH(Top, Right) );
    CHECK( HCOMP_NAME_MATCH(Top, Right) );
    CHECK( CROSS_NAME_MATCH(Middle, Left) );
    CHECK( VCOMP_NAME_MATCH(Middle, Left) );
    CHECK( HCOMP_NAME_MATCH(Middle, Left) );
    CHECK( CROSS_NAME_MATCH(Middle, Center) );
    CHECK( VCOMP_NAME_MATCH(Middle, Center) );
    CHECK( HCOMP_NAME_MATCH(Middle, Center) );
    CHECK( CROSS_NAME_MATCH(Middle, Right) );
    CHECK( VCOMP_NAME_MATCH(Middle, Right) );
    CHECK( HCOMP_NAME_MATCH(Middle, Right) );
    CHECK( CROSS_NAME_MATCH(Bottom, Left) );
    CHECK( VCOMP_NAME_MATCH(Bottom, Left) );
    CHECK( HCOMP_NAME_MATCH(Bottom, Left) );
    CHECK( CROSS_NAME_MATCH(Bottom, Center) );
    CHECK( VCOMP_NAME_MATCH(Bottom, Center) );
    CHECK( HCOMP_NAME_MATCH(Bottom, Center) );
    CHECK( CROSS_NAME_MATCH(Bottom, Right) );
    CHECK( VCOMP_NAME_MATCH(Bottom, Right) );
    CHECK( HCOMP_NAME_MATCH(Bottom, Right) );
  }

  SECTION("Check origin calculation by alignment.")
  {
    float const expectY[] = {0, 2, 4};
    VerticalAlignment vValue[] =
    {
      VerticalAlignment::Top,
      VerticalAlignment::Middle,
      VerticalAlignment::Bottom,
    };
    float const expectX[] = {0, 3, 6};
    HorizontalAlignment hValue[] =
    {
      HorizontalAlignment::Left,
      HorizontalAlignment::Center,
      HorizontalAlignment::Right,
    };

    for (unsigned int vi = 0 ; vi < 3 ; ++vi)
    {
      CHECK( expectY[vi] == alignedVerticalOrigin(vValue[vi], 4) );
      for (unsigned int hi = 0 ; hi < 3 ; ++hi)
      {
        if (0 == vi)
        {
          CHECK( expectX[hi] == alignedHorizontalOrigin(hValue[hi], 6) );
        }
        CHECK( sf::Vector2f(expectX[hi], expectY[vi]) ==
               alignedOrigin(crossAlign(vValue[vi], hValue[hi]),
                 sf::Vector2f(6, 4)) );
      }
    }
  }
}
