#include "error.hpp"

#include <cstring>

// Static Declarations:
char const * const GameError::unknownMsg =
  "Unknown Exeception from within the game engine.";

char const * const GameError::lostMsg =
  "Game Error occured, however the message was lost.";

char const * GameError::maybeDup (bool dynamic, char const * src)
{
  return (dynamic) ? strdup(src) : src;
}



GameError::GameError () noexcept :
  dynamic(false), msg(unknownMsg)
{}

GameError::GameError (GameError const & other) noexcept :
  dynamic(other.dynamic), msg(maybeDup(dynamic, other.msg))
{
  if (nullptr == msg)
    msg = lostMsg;
}

GameError::GameError (GameError && other) noexcept :
  dynamic(other.dynamic), msg(other.msg)
{
  other.dynamic = false;
}

GameError::GameError (char const * msg, bool dynamic = true) noexcept :
// How often will we be using a new message? (dynamic = false)
  dynamic(dynamic), msg(maybeDup(dynamic, msg));
{
  if (nullptr == msg)
    msg = lostMsg;
}

GameError::GameError (std::string const & msg) noexcept :
  dynamic(true), msg(maybeDup(true, msg.c_str()))
{
  if (nullptr == msg)
    msg = lostMsg;
}

GameError::~GameError () noexcept
{
  if (dynamic) delete msg;
}

char const * GameError::what () const noexcept
{
  return msg;
}



FileError::FileError (std::string const & problem, std::string const & file)
  GameError((problem + file).c_str(), true)
{}

FileError::FileError (FileError const & other) :
  GameError(other)
{}

//FileError::~FileError () {}

#endif//ERROR_HPP
