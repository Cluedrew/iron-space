#include "loop-clock.hpp"

// Implementation of the wait function.

#include <thread>
#include <chrono>

// Constructors and Deconstructor ===========================================
// Construct a LoopClock with an increment equal to the given time.
LoopClock::LoopClock (sf::Time const & increment_) :
  clock(), increment(increment_)
{}

// Construct a LoopClock with, about, ips increments in a second.
LoopClock::LoopClock (unsigned int ips) :
  clock(), increment(sf::milliseconds(1000 / ips))
{}

// Construct a LoopClock with an increment of 0 time passed.
LoopClock::LoopClock () :
  clock(), increment(sf::Time::Zero)
{}

// Deconstructor
LoopClock::~LoopClock ()
{}

// Implementation Functions ==================================================
// Wait for the rest of the time increment to pass.
void LoopClock::wait () const
{
  sf::Time time = clock.getElapsedTime();
  if (time < increment)
  {
    sf::Time diff = increment - time;
    std::chrono::duration<int, std::milli> waitTime(diff.asMilliseconds());
    std::this_thread::sleep_for<int, std::milli>(waitTime);
  }
  clock.restart();
}

/* The following are some functions I am considering adding.
 * These are to allow a variable frame rate, although it is still always
 * locked at the given framerate (so not true variable timing). If these
 * functions are added the first sf::Time constructor should be changed to
 * have a default paramiter of zero.
 * LoopClock::LoopClock (sf::Time const & increment_ = sf::Time::Zero)
 * wait() will always return (almost) instantly.
 */
// Reset the LoopClock's increment.
void LoopClock::setIncrement (sf::Time const & increment_)
{
  increment = increment_;
}

// Reset the LoopClock's increment.
void LoopClock::setIncrement (unsigned int ips)
{
  increment = sf::milliseconds(1000 / ips);
}

// Get the currant time increment.
sf::Time const & LoopClock::getIncrement () const
{
  return increment;
}
