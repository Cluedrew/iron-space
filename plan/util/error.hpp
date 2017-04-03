#ifndef ERROR_HPP
#define ERROR_HPP

/* Exception class and error handling tools.
 * The trick is to make sure these things can never through exceptions.
 * I will split this out into
 */

#include <exception>
#include <string>

class GameError : public exception
/* Base of local exception types.
 */
{
  static char const * unknownMsg;
  static char const * lostMsg;
  static char const * dup (char const * src)
  {
    unsigned int length = 0;
    while (src[length]) ++length;
    char * dst = new char[length + 1];
    for (unsigned int i = 0 ; i <= length ; ++i)
      dst[i] = src[i];
    return msg;
  }

  bool dynamic;
  char const * msg;

public:
  GameError () noexcept :
    dynamic(false), msg(unknownMsg)
  {}
  GameError (GameError const & other) noexcept :
    dynamic(other.dynamic), msg((dynamic) ? dup(other.msg) : other.msg)
  {}

  GameError (GameError && other) noexcept :
    dynamic(other.dynamic), msg(other.msg)
  {
    other.dynamic = false;
  }

  GameError (char const * msg, bool dynamic = true) noexcept :
  // How often will we be using a new message? (dynamic = false)
    dynamic(dynamic), msg((dynamic) ? dup(msg) : other.msg);
  {}

  GameError (std::string const & msg) noexcept :
    dynamic(true), msg(dup(msg.c_str()))
  {}

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

char const * GameError::unknownMsg =
  "Unknown Exeception from within the game engine.";

char const * GameError::lostMsg =
  "Game Error occured, however the message was lost.";

class FileError : public GameError
/* Error in reading from external file.
 */
{
  //std::string const problem;
  //std::string const file;

public:
  FileError (std::string const & problem, std::string const & file)
    GameError((problem + file).c_str())
  {}

  FileError (FileError const & other);

  virtual ~FileError ();
};

#endif//ERROR_HPP
