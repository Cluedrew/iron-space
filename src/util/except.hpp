#ifndef EXCEPT_HPP
#define EXCEPT_HPP

/* Exception classes and error handling tools.
 * I'm still forming this.
 */

#include <stdexcept>
#include <string>



class GameError : public std::runtime_error
/* Base runtime errors, these should be caught and handled whenever possible.
 */
{
public:
  GameError(std::string const & whatArg);
  GameError(char const * whatArg);
};

class GameFault : public std::logic_error
/* Base logic error, these should not be caught, let them fall through and
 * stop the program so they can be addressed.
 */
{
public:
  GameFault(std::string const & whatArg);
  GameFault(char const * whatArg);
};

class FileError : public GameError
{
public:
  FileError(std::string const & error, std::string const & file);
};

#endif//EXCEPT_HPP
