#include "except.hpp"


GameError::GameError(std::string const & whatArg) :
  std::runtime_error(whatArg)
{}

GameError::GameError(char const * whatArg) :
  std::runtime_error(whatArg)
{}

GameFault::GameFault(std::string const & whatArg) :
  std::logic_error(whatArg)
{}

GameFault::GameFault(char const * whatArg) :
  std::logic_error(whatArg)
{}

FileError::FileError(std::string const & error, std::string const & file) :
  GameError(error + file)
{}
