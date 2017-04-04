#ifndef ERROR_HPP
#define ERROR_HPP

/* Exception class and error handling tools.
 * The trick is to make sure these things can never throw exceptions.
 * My main method of this is to store an inline message and use that if
 * we run out of space. That is the only source of exceptions I can think of.
 *
 * Scratchpad:
 */

#include <exception>
#include <string>

// In implementation.
#include <cstring>

class GameError : public exception
/* Base of local exception types.
 */
{
  static char const * const unknownMsg;
  static char const * const lostMsg;
  static char const * maybeDup (bool dynamic, char const * src)
  {
    return (dynamic) ? strdup(src) : src;
  }

  bool dynamic;
  char const * msg;

public:
  GameError () noexcept :
    dynamic(false), msg(unknownMsg)
  {}
  GameError (GameError const & other) noexcept :
    dynamic(other.dynamic), msg(maybeDup(dynamic, other.msg))
  {
    if (nullptr == msg)
      msg = lostMsg;
  }

  GameError (GameError && other) noexcept :
    dynamic(other.dynamic), msg(other.msg)
  {
    other.dynamic = false;
  }

  GameError (char const * msg, bool dynamic = true) noexcept :
  // How often will we be using a new message? (dynamic = false)
    dynamic(dynamic), msg(maybeDup(dynamic, msg));
  {
    if (nullptr == msg)
      msg = lostMsg;
  }

  GameError (std::string const & msg) noexcept :
    dynamic(true), msg(maybeDup(true, msg.c_str()))
  {
    if (nullptr == msg)
      msg = lostMsg;
  }

  virtual ~GameError ()
  {
    if (dynamic) delete msg;
  }

  virtual char const * what () const noexcept
  // Return value valid until object is deleted.
  // Or until non-const member is used.
  {
    return msg;
  }
};

char const * const GameError::unknownMsg =
  "Unknown Exeception from within the game engine.";

char const * const GameError::lostMsg =
  "Game Error occured, however the message was lost.";

class FileError : public GameError
/* Error in reading from external file.
 */
{
  //std::string const problem;
  //std::string const file;

public:
  FileError (std::string const & problem, std::string const & file)
    GameError((problem + file).c_str(), true)
  {}

  FileError (FileError const & other);
  // I completely forget the 'safe' way to copy between children.

  virtual ~FileError () {}
};

#endif//ERROR_HPP
