#ifndef GEN_EVENT_HANDLER_HPP
#define GEN_EVENT_HANDLER_HPP

/* The generic event handler, it can draw and process events from any base
 * class that implements: `bool SourceT::pollEvent(sf::Event)`. This generic
 * form is used so I can rewire it for testing, the game itself only uses the
 * EventHandler, which takes events from the window.
 */

class Response;
class WorldState;
class InputEvent;



template<typename SourceT>
class GenEventHandler
{
private:
protected:
public:
  GenEventHandler ();

  virtual ~GenEventHandler ();

  Response pollEvents (SourceT & window, WorldState & state);
  /* Poll all events from the window and dispatch them.
   * Params: A mutable references to the source 'window' to poll from and
   *   the state to dispatch the events to.
   * Return: The Response value for the polled Events.
   */

  // TODO: I don't need a class for this.
  bool pollEvent (SourceT & source, InputEvent & iEvent);
  /* Poll from the source and translate the event.
   * Params: Mutable references to the source to get the event from and
   *   the iEvent to store the translated event in.
   * Return: True if an event was polled and translated, false if we are at
   *   the end of the queue.
   */
};

#include "gen-event-handler.tpp"

#endif//GEN_EVENT_HANDLER_HPP
