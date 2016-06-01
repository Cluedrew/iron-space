#include "logger.hpp"

// Implementation of the logger class.

#include <iostream>
#include <cstdlib>



// Because this type comes up so much in this file.
#define STRING std::string const &

// Static Field Declaration
std::map<Logger, std::string> Logger::loggers;



Logger::Logger (STRING name_) :
  name(name_)
{}

Logger::~Logger ()
{}

// see header
Logger & Logger::requestLogger (STRING name)
{}

/* lprint(msgClass, text)
 * Internal printing function for Logger class
 * Params: References to the text that repersents the class of the
 *   message and the text of the message itself.
 * Effect: Prints standard formated message to stderr.
 */
void Logger::lprint (STRING msgClass, STRING text)
{
  std::cerr << name << "[" << msgClass << "]: " << text << std::endl;
}

// see header
void Logger::data (STRING text)
{
  // if Verbose
  lprint(name, "DATA", text);
}

// see header
void Logger::note (STRING text)
{
  // if not Quite
  lprint(name, "NOTE", text);
}

// see header
void Logger::warn (STRING text)
{
  lprint(name, "WARN", text);
}

// see header
void Logger::fail (STRING text, int exitWith)
{
  lprint(name, "FAIL", text);
  exit(exitWith);
}
