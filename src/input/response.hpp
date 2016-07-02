#ifndef RESPONSE_HPP
#define RESPONSE_HPP

/* Response to event: This is how the EventHandler gets information back to
 * the engine, by responding to the events. I choose this over a callback
 * system because this requires less wiring and so is more modular and easier
 * to test.
 */

struct Response
{
  enum ResponseType
  {
    // Final response given each frame, done polling events.
    Done,
    // Tell the engine to quit.
    Quit,

    Cap
  } type;

  // There will probably be a union here for extra data later.
};

#endif//RESPONSE_HPP
