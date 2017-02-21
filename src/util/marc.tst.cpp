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


#if DEBUG
#define DEBUG_REQUIRE(x) REQUIRE(x)
#else
#define DEBUG_REQUIRE(x)
#endif//DEBUG

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

    CounterMaRC zee('z');
    REQUIRE( *zee == 1 );

    CounterMaRC tea('t');
    REQUIRE( *tea == 2 );

    {
      CounterMaRC w('w');
      REQUIRE( *w == 3 );
    }

    {
      CounterMaRC uu('w');
      REQUIRE( *uu == 4 );
    }

    CounterMaRC sea('c');
    REQUIRE( *sea == 5 );
  }

  SECTION("Check Timing of Loads and Unloads")
  {
    REQUIRE( "" == CharTracker::record );
    {
      TrackerMaRC bee('b');
#if DEBUG
      auto data = TrackerMaRC::cheat();
      for (auto it = data.begin() ; it != data.end() ; ++it)
        WARN(it->second->key << ' ' << it->second->useCount);
      REQUIRE( 1 == data.size() );
#endif
      REQUIRE( "B" == CharTracker::record );
    }
#if DEBUG
    auto data = TrackerMaRC::cheat();
    for (auto it = data.begin() ; it != data.end() ; ++it)
      WARN(it->second->key << ' ' << it->second->useCount);
    REQUIRE( 0 == data.size() );
#endif
    REQUIRE( "Bb" == CharTracker::record );

    {
      TrackerMaRC zed('z');
      {
        TrackerMaRC zee('z');
      }
      REQUIRE( "BbZ" == CharTracker::record );
    }
    REQUIRE( "BbZz" == CharTracker::record );

    {
      TrackerMaRC que('q');
      REQUIRE( "BbZzQ" == CharTracker::record );
    }
    REQUIRE( "BbZzQq" == CharTracker::record );

    {
      TrackerMaRC que('q');
      REQUIRE( "BbZzQqQ" == CharTracker::record );
    }
    REQUIRE( "BbZzQqQq" == CharTracker::record );
  }
}
