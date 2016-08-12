#include "loop-clock.hpp"
#include "catch.hpp"

/* Testing with the LoopClock.
 * Checks the Increments Per Second calculation, as well as some of the timing
 * behaviours. The latter group is pending as I figure out how to do it.
 */




#include <chrono>
#include <thread>

/* Sleep for a given time, messured in milliseconds.
static void sleepForTime (sf::Time const & time)
{
  std::chrono::duration<int, std::milli> sleepTime(time.asMilliseconds());
  std::this_thread::sleep_for<int, std::milli>(sleepTime);
}*/



TEST_CASE("Check the Increments Per Second approximation", "[util]")
{
  LoopClock lclock;

  SECTION("run through common frame rates")
  {
    lclock.setIncrementsPerSecond(30);
    CHECK( 33 == lclock.getIncrement().asMilliseconds() );
    lclock.setIncrementsPerSecond(15);
    CHECK( 66 == lclock.getIncrement().asMilliseconds() );
    lclock.setIncrementsPerSecond(60);
    CHECK( 16 == lclock.getIncrement().asMilliseconds() );
  }
}
