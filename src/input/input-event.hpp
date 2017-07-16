#ifndef INPUT_EVENT_HPP
#define INPUT_EVENT_HPP

/* Repersents a translated input event. These events are agnostic as to how
 * they are generated, although many can only be generated certain ways.
 * They are used for comunication within the program, from the EventHandler
 * down to GameObjects.
 *
 * I could write some tests for this using std::ostringstream
 */

#include <iosfwd>
#include <string>



struct InputEvent
{
  enum EventType
  {
    // A command is given to quit the game.
    Quit,
    // A selection is made on the screen.
    Select,
    // The pause/unpause command.
    Pause,
    // Point to a particular point on screen.
    Point,

    Cap
  } type;

  struct Position
  {
    int x;
    int y;
  };

  union
  {
    // Used with Select & Point.
    Position pos;
  };
};

std::ostream & operator<< (std::ostream & out, InputEvent const & ievent);
std::string toString (InputEvent const & ievent);

#endif//INPUT_EVENT_HPP
