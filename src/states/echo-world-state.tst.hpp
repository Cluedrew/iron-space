#ifndef ECHO_WORLD_STATE_TST_HPP
#define ECHO_WORLD_STATE_TST_HPP

/* A world state that says what happens two it.
 *
 * This is really only useful for testing
 */

#include <iosfwd>
#include "world-state.hpp"



class EchoWorldState
{
private:
  std::ostream & out;

protected:
public:
  EchoWorldState (std::ostream & out);
  /* Create the world state.
   * Params: Stream to echo calls to.
   */

  virtual ~EchoWorldState ();

  void handleInput (InputEvent const & ievent);
  /* Handles an InputEvent.
   * Params: The ievent to handle.
   * Effect: Prints a line to out, giving the ievent.
   */

  void update (sf::Time const & deltaT);
  /* Echo that the update function has been called.
   * Params: The amount of time that has passed.
   * Effect: Prints a line to out, giving the deltaT value in milliseconds.
   */

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Do nothing.
   * Params: All are ignored.
   * Effect: None.
   */
};

#endif//ECHO_WORLD_STATE_TST_HPP
