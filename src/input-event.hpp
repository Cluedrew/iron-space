#ifndef INPUT_EVENT_HPP
#define INPUT_EVENT_HPP

/* Structure that repersent a disbatched input event.
 *
 * This is planned to be used in the final engine, but it will change a lot
 * as I work out what events I need and what data will accompany them. So its
 * current form is temperary.
 */



struct InputEvent
{
  // Enumeration of all types of events.
  enum InputType
  {
    MouseClick,
    Cap
  } type;

  // Mouse position
  struct Pos
  {
    int x;
    int y;
  };

  // All possible data for an input event.
  union
  {
    Pos pos;
  };
};

#endif//INPUT_EVENT_HPP
