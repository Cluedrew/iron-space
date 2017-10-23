#include "fat-func.hpp"
#include <catch.hpp>

/* Testing (and examples for) FatFunction.
 *
 * And of course the numerous helper functions and classes.
 */



static int globalCount = 0;
void globalIncrement () { ++globalCount; }
void globalIncrementBy (int by) { globalCount += by; }
int getGlobalCount () { return globalCount; }

struct Counter
{
  Counter () : count(0) {}
  int count;
  void increment () { ++count; }
  void incrementBy (int by) { count += by; }
  int getCount () { return count; }
};

char rotate (char start, int distance)
{
  return 'a' + ((start - 'a' + distance) % 26);
}

struct Rotator
{
  bool forward;
  Rotator(bool forward) : forward(forward) {}
  char rotate (char start, int distance)
  {
    return ::rotate(start, (forward) ? distance : -distance);
  }
};

void doubling (int & value) { value *= 2; }

int globalMoveValue = 0;
void moveAndSet (int && value) { globalMoveValue = value; }

TEST_CASE("Tests for FatFunction", "[util]")
{
  globalCount = 0;

  SECTION("Simplest use of function binding.")
  {
    FatFunction<void> signal;
    signal.set<globalIncrement>();

    REQUIRE( 0 == globalCount );
    signal.call();
    REQUIRE( 1 == globalCount );
  }

  SECTION("Simplest use of method binding.")
  {
    FatFunction<void> signal;
    Counter localCounter;
    signal.set<Counter, &Counter::increment>(&localCounter);

    REQUIRE( 0 == localCounter.count );
    signal.call();
    REQUIRE( 1 == localCounter.count );
  }

  SECTION("Non-void return type used with both bindings.")
  {
    FatFunction<int> func;
    func.set<getGlobalCount>();

    globalCount = 4;
    REQUIRE( 4 == func.call() );
  }

  SECTION("Non-void return type used with method binding.")
  {
    FatFunction<int> func;
    Counter localCounter;
    func.set<Counter, &Counter::getCount>(&localCounter);

    localCounter.count = 4;
    REQUIRE( 4 == func.call() );
  }

  SECTION("Paramter used with function binding.")
  {
    FatFunction<void, int> func;
    func.set<globalIncrementBy>();

    func.call(1);
    REQUIRE( 1 == globalCount );
    func.call(2);
    REQUIRE( 3 == globalCount );
  }

  SECTION("Paramter used with method binding.")
  {
    FatFunction<void, int> func;
    Counter localCounter;
    func.set<Counter, &Counter::incrementBy>(&localCounter);

    func.call(1);
    REQUIRE( 1 == localCounter.count );
    func.call(2);
    REQUIRE( 3 == localCounter.count );
  }

  SECTION("Full use of both bindings. Also multiple uses of set.")
  {
    FatFunction<char, char, int> map;
    map.set<rotate>();

    REQUIRE( 'j' == map.call('c', 7) );

    Rotator backwardRotate(false);
    Rotator forwardRotate(true);

    map.set<Rotator, &Rotator::rotate>(&backwardRotate);
    REQUIRE( 'l' == map.call('p', 4) );
    map.set<Rotator, &Rotator::rotate>(&forwardRotate);
    REQUIRE( 'a' == map.call('z', 1) );
  }

  SECTION("References should be maintained.")
  {
    FatFunction<void, int &> func;
    func.set<doubling>();

    int num = 7;
    func.call(num);
    REQUIRE( 14 == num );
  }

  SECTION("Move operations should be maintained.")
  {
    // I'm not entirely sure if this is a true meaningful test.
    FatFunction<void, int &&> func;
    func.set<moveAndSet>();

    func.call(4);
    REQUIRE( 4 == globalMoveValue );
  }
}
