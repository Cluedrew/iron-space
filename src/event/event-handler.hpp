#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

/* The EventHandler is responsible for getting events from the window as well
 * as translating them and dispatching them to the rest of the code base. It
 * is the core of the Interface layer, at least for input.
 */

namespace sf
{
  class Window;
}

#include "gen-event-handler.hpp"

class EventHandler : public GenEventHandler<sf::Window>
{
private:
protected:
public:
  virtual ~EventHandler ();

  /* bool pollEvents (sf::Window & window);
   *
   * Poll all events from the window and dispatch them.
   * Params: A mutable reference to the window to poll from.
   * Return: The (should we continue) running value, which is false if
   *   a Close event was found, true otherwise.
   *
   * Currently there is no actually dispatching means nor is there a way to
   * get data back to the engine beyond that one boolean, which probably be
   * outstripped as time goes on.
   */
};

#endif//EVENT_HANDLER_HPP
