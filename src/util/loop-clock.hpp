#ifndef LOOP_CLOCK_HPP
#define LOOP_CLOCK_HPP

/*   The LoopClock is a small class that implements a fixed rate timer.
 *   Each call of wait will cause the system to pause so that one increment
 * of time has passed since the last time wait returned or, for the first call
 * to wait, the LoopClock's creation.
 *   Note that is more than one increment of time has already passed wait will
 * return imediately, not wait for the end of the next increment. The next
 * increment will start counting from here, instead of when the last increment
 * ended. A time increment of 0 will cause it to return imediately every time.
 *   Also a constaint LoopClock is still partially mutable to allow the change
 * of increments to be tracked, however the increment is now locked. Generally
 * one should pass around a reference to the increment itself instead of the
 * LoopClock if you wish to prevent the LoopClock from being used.
 */

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class LoopClock
{
private:
  mutable sf::Clock clock;
  sf::Time increment;
protected:
public:
  LoopClock (sf::Time const &);
  /* Construct a LoopClock with an increment equal to the given time.
   * Params: A reference to an sf::Time with the desired increment.
   */

  LoopClock (unsigned int ips);
  /* Construct a LoopClock with, about, ips increments in a second.
   * Params: The number of increments per second.
   *   The division of the second into increments is not perfect and
   *   error on the side of being to short.
   */

  LoopClock ();
  /* Construct a LoopClock with an increment of 0 time passed.
   */

  virtual ~LoopClock ();

  void wait () const;
  /* Wait for the rest of the time increment to pass.
   *   If the entire increment has passed, the function returns without delay.
   */

  void setIncrement (sf::Time const &);
  /* Reset the LoopClock's increment.
   * Params: A reference to an sf::Time with the desired increment.
   * Effect: Changes the LoopClock's increment. The end time of the last
   *   increment remains unchanged and the currant increment will be
   *   messured from there.
   */

  void setIncrementsPerSecond (unsigned int ips);
  /* Reset the LoopClock's increment.
   * Params: The number of increments per second.
   *   The division of the second into increments is not perfect and
   *   error on the side of being to short.
   * Effect: Changes the LoopClock's increment. The end time of the last
   *   increment remains unchanged and the currant increment will be
   *   messured from there.
   */

  sf::Time const & getIncrement () const;
  /* Get the amount of time per increment of the LoopClock.
   * Return: A constaint reference to the LoopClock's time increment.
   */
};

#endif//LOOP_CLOCK_HPP
