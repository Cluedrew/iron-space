#ifndef ECHO_WORLD_STATE_TST_HPP
#define ECHO_WORLD_STATE_TST_HPP

/* A world state that says what happens two it.
 *
 * This is really only useful for testing
 */

#include <string>
#include <list>
#include "world-state.hpp"



class EchoWorldState : public WorldState
{
private:
  std::list<std::string> echoes;

  void storeEcho (std::string const &);

protected:
public:
  EchoWorldState ();
  /* Create the world state. There are no stored echoes initially.
   */

  virtual ~EchoWorldState ();

  WorldState * handleInput (InputEvent const & ievent);
  /* Handles an InputEvent.
   * Params: The ievent to handle.
   * Effect: Prints a line to out, giving the ievent.
   */

  WorldState * update (sf::Time const & deltaT);
  /* Echo that the update function has been called.
   * Params: The amount of time that has passed.
   * Effect: Prints a line to out, giving the deltaT value in milliseconds.
   */

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Do nothing.
   * Params: All are ignored.
   * Effect: None.
   */

  bool hasEchoes () const;
  /* Check to see if any echoes are stored.
   * Return: True is 1 or more echoes are stored, false otherwise.
   */

  std::string const & peekEcho () const;
  /* Look at the oldest stored echo.
   *   Program halts if no echoes are stored.
   * Return: Reference to oldest echo.
   */

  std::string popEcho ();
  /* Get the oldest stored echo, removing it from the container.
   *   Program halts if no echoes are stored.
   * Effect: Removes the oldest echo from internal storage.
   * Return: The oldest echo.
   */
};

#endif//ECHO_WORLD_STATE_TST_HPP
