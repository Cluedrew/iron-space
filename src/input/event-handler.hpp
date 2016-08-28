#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

/* The EventHandler is responsible for getting events from the window as well
 * as translating them and dispatching them to the rest of the code base. It
 * is the core of the Interface layer, at least for input.
 *
 * It is simply a specialization of the GenEventHandler that gets real input
 * from the SFML Window.
 */

namespace sf { class Window; }
#include "gen-event-handler.hpp"



class EventHandler : public GenEventHandler<sf::Window>
{
private:
protected:
public:
  virtual ~EventHandler ();

  /* Responce pollEvents (sf::Window & window, WorldState & state);
   *
   * Poll all events from the window and dispatch them.
   * Params: A mutable references to the window to poll from and
   *   the state to dispatch the events to.
   * Return: The Response value for the polled Events.
   */
};

#endif//EVENT_HANDLER_HPP
