#include "input-event.hpp"

/* Just some code for printing.
 * This might get moved to debug or even testing later.
 */

#include <ostream>
#include <sstream>



#if 0
// WIP: A lookup on the data held by the each event type.
// Inside the main class:
  InputEvent::EventPayload
  {
    // Holds no additional data:
    Signal,
    // Carries with it a 2d possition, usually a screen position.
    Positional,

    Cap
  }

// This might be worth being a constexpr, it is a fixed lookup.
static constexpr InputEvent::EventPayload InputEvent::payloadType (
    InputEvent::EventPayload type)
{
  switch (type)
  {
  case InputEvent::Unselect:
  case InputEvent::Quit:
  case InputEvent::Pause:
    return Signal;
  case InputEvent::Select:
  case InputEvent::Point:
    return Positional;
  // Do I need this one? Does it make sense?
  case InputEvent::Cap:
    return Cap;
  }
}

InputEvent::EventPayload InputEvent::payloadType () const
{
  return payloadType(type);
}
#endif

static std::ostream & operator<< (std::ostream & out,
    InputEvent::EventType type)
{
  switch (type)
  {
  case InputEvent::Quit:
    out << "Quit";
    break;
  case InputEvent::Select:
    out << "Select";
    break;
  case InputEvent::Unselect:
    out << "Unselect";
    break;
  case InputEvent::Pause:
    out << "Pause";
    break;
  case InputEvent::Point:
    out << "Point";
    break;
  case InputEvent::Cap:
    out << "Cap";
    break;
  }
  return out;
}

static std::ostream & operator<< (std::ostream & out,
    InputEvent::Position const & position)
{
  return out << "x=" << position.x << " y=" << position.y;
}

std::ostream & operator<< (std::ostream & out, InputEvent const & ievent)
{
  out << ievent.type << "(";
  switch (ievent.type)
  {
  case InputEvent::Select:
  case InputEvent::Point:
    out << ievent.pos;
    break;
  case InputEvent::Unselect:
  case InputEvent::Quit:
  case InputEvent::Pause:
  case InputEvent::Cap:
    break;
  };
  return out << ")";
}

std::string toString (InputEvent const & ievent)
{
  std::ostringstream out;
  out << ievent;
  return out.str();
}
