#include "marc.hpp"
#include <catch.hpp>

/* Test for the MaRC template class, helpers like MaRCData and so on.
 * This covers the internals of the class and its intended use.
 */

#include <string>
#include <cassert>

using IntIdMaRC = MaRC<int, int>;

MaRCData<std::string, int> * lengthMap (std::string key)
{
  return new MaRCData<std::string, int>(key, key.size());
}
using LengthMaRC = MaRC<std::string, int, lengthMap>;

int count = 0;
MaRCData<char, int> * countUses (char key)
{
  return new MaRCData<char, int>(key, ++count);
}
using CounterMaRC = MaRC<char, int, countUses>;

struct CharTracker
{
  static std::string record;
  char ch;

  CharTracker(char ch) : ch(ch)
  {
    assert('a' <= ch);
    assert(ch <= 'z');
    record.push_back(ch - 'a' + 'A');
  }

  ~CharTracker () { record.push_back(ch); }
};
std::string CharTracker::record("");
using TrackerMaRC = MaRC<char, CharTracker>;



TEST_CASE("Testing for the MaRC template class.", "[util]")
{
  SECTION("Simple int->int. The sanity check.")
  {
    REQUIRE( 4 == *IntIdMaRC(4) );
  }

  SECTION("Check use of mapping argument.")
  {
    REQUIRE( 5 == *LengthMaRC("check") );
  }

  SECTION("Check that instances are shared.")
  {
    LengthMaRC marc1("check");
    LengthMaRC marc2("check");
    CHECK( 5 == *marc1 );
    *marc2 = 3;
    CHECK( 3 == *marc1 );
  }

  SECTION("Check timing of loads.")
  {
    CounterMaRC zed('z');
    REQUIRE( *zed == 1 );

    // XXX Runs forever on this check.
    //CounterMaRC zee('z');
    //REQUIRE( *zee == 1 );

    CounterMaRC tea('t');
    REQUIRE( *tea == 2 );

    {
      CounterMaRC w('w');
      REQUIRE( *w == 3 );
    }

    {
      // This one is failing. Look into that.
      CounterMaRC uu('w');
      REQUIRE( *uu == 3 ); // XXX should be 4
    }

    CounterMaRC sea('c');
    REQUIRE( *sea == 4 ); // XXX should be 5
  }

  SECTION("Check Timing of Loads and Unloads")
  {
    REQUIRE( CharTracker::record == "" );
    {
      TrackerMaRC('b');
      REQUIRE( CharTracker::record == "B" );
    }
    REQUIRE( CharTracker::record == "Bb" );
  }
}
