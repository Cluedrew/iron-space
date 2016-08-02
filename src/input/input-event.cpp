#include "input-event.hpp"

/* Just some code for printing.
 * This might get moved to debug or even testing later.
 */

#include <ostream>



static std::ostream & operator<< (std::ostream & out,
    InputEvent::EventType type)
{
  switch (type)
  {
  case InputEvent::EventType::Select:
    out << "Select";
    break;
  case InputEvent::EventType::Cap:
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
  case InputEvent::EventType::Select:
    out << ievent.pos;
    break;
  case InputEvent::EventType::Cap:
    break;
  };
  return out << ")";
}
