#include "alignment.hpp"
#include <catch.hpp>

/* Tests for the alignment types and their helpers.
 * The tests for the basic operations are quite extencive because they
 * involve casts and casts make me uncomfortable.
 *
 * TODO: That being said it probably could be compacted somewhat.
 */



#define COMBINE_NAMES(vertical, horisontal) \
VerticalAlignment::vertical, \
HorizontalAlignment::horisontal, \
Alignment2D::vertical##horisontal

#define CROSS_BASE_MATCH(v, h, vh) crossAlign(v, h) == vh
#define CROSS_NAME_MATCH(v, h) \
CROSS_BASE_MATCH(VerticalAlignment::v, \
HorizontalAlignment::h, Alignment2D::v##h)
//CROSS_BASE_MATCH(COMBINE_NAMES(v, h))

#define VCOMP_BASE_MATCH(v, h, vh) v == verticalAlignmentComponent(vh)
#define VCOMP_NAME_MATCH(v, h) \
VCOMP_BASE_MATCH(VerticalAlignment::v, \
HorizontalAlignment::h, Alignment2D::v##h)
//VCOMP_BASE_MATCH(COMBINE_NAMES(v, h))

#define HCOMP_BASE_MATCH(v, h, vh) h == horizontalAlignmentComponent(vh)
#define HCOMP_NAME_MATCH(v, h) \
HCOMP_BASE_MATCH(VerticalAlignment::v, \
HorizontalAlignment::h, Alignment2D::v##h)
//HCOMP_BASE_MATCH(COMBINE_NAMES(v, h))

#define TOTAL_MATCH(v, h) CROSS_NAME_MATCH(v, h) && \
HCOMP_NAME_MATCH(v, h) && VCOMP_NAME_MATCH(v, h)



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
}
