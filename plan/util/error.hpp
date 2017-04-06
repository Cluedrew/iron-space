#ifndef ERROR_HPP
#define ERROR_HPP

/* Exception classes and error handling tools.
 * WIP: Rename error.hpp -> exception.hpp? Use runtime_error instead of
 *  exception as the base class?
 */

#include <exception>
#include <string>



class GameError : public exception
/* Base of local exception types. All errors
 */
{
  static char const * const unknownMsg;
  static char const * const lostMsg;
  static char const * maybeDup (bool willDup, char const * src);

  bool dynamic;
  char const * msg;

public:
  GameError () noexcept;
  GameError (GameError const & other) noexcept;
  GameError (GameError && other) noexcept;
  GameError (char const * msg, bool dynamic = true);
  // How often will we be using a new message? (dynamic = false)
  GameError (std::string const & msg) noexcept;

  virtual ~GameError () noexcept;

  virtual char const * what () const noexcept;
};

char const * const GameError::unknownMsg =
  "Unknown Exeception from within the game engine.";

char const * const GameError::lostMsg =
  "Game Error occured, however the message was lost.";

class FileError : public GameError
/* Error in a file operation.
 */
{
public:
  FileError (std::string const & problem, std::string const & file);
  FileError (FileError const & other);

  virtual ~FileError () {}
};

#endif//ERROR_HPP
