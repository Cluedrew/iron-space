#ifndef GEN_EVENT_HANDLER_HPP
#define GEN_EVENT_HANDLER_HPP

/* The generic event handler, it can draw and process events from any base
 * class that implements: `Responce SourceT::pollEvent(sf::Event)`. This
 * generic form is used so I can rewire it for testing, the game itself only
 * uses the EventHandler, which takes events from the window.
 *
 * I have no idea if this is a good idea or not, but I'm going to try.
 */

//#include "response.hpp"
class Response;
class WorldState;



template<typename SourceT>
class GenEventHandler
{
private:
protected:
public:
  GenEventHandler ();

  virtual ~GenEventHandler ();

  // Plane is temperary. State?
  Response pollEvents (SourceT & window, WorldState & state);
  /* Poll all events from the window and dispatch them.
   * Params: A mutable reference to the window to poll from.
   * Return: The (should we continue) running value, which is false if
   *   a Close event was found, true otherwise.
   *
   * Currently there is no actually dispatching means nor is there a way to
   * get data back to the engine beyond that one boolean, which probably be
   * outstripped as time goes on.
   */
};

#include "gen-event-handler.tpp"

#endif//GEN_EVENT_HANDLER_HPP
