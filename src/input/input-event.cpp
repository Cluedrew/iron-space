#include "input-event.hpp"

/* Just some code for printing.
 * This might get moved to debug or even testing later.
 */

#include <ostream>
#include <sstream>



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
  case InputEvent::Pause:
    out << "Pause";
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
    out << ievent.pos;
    break;
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
