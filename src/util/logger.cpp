#include "logger.hpp"

// Implementation of the logger class.

#include <iostream>
#include <cstdlib>
#include <set>



// Because this type comes up so much in this file.
#define STRING std::string const &

static std::set<std::string> loggerNames;



// see header
Logger::Logger (STRING name_, LoggerDetailLevel detail_) :
  name(name_), detail(detail_)
{
  if (std::string("") == name)
  {
    std::cerr << "Logger invalid name: empty string" << std::endl;
    exit(EXIT_FAILURE);
  }

  if (0 == loggerNames.count(name))
  {
    loggerNames.insert(name);
  }
  else
  {
    // maybe I could handle this with an exception.
    std::cerr << "Logger name conflict on : " << name << std::endl;
    exit(EXIT_FAILURE);
  }
}

Logger::Logger (Logger && other) :
  name(other.name), detail(other.detail)
{
  other.name = std::string("");
}

Logger::~Logger ()
{
  if (std::string("") == name)
    return;

  // Remove the name from the list of names.
  if (0 == loggerNames.count(name))
  {
    std::cerr << "Logger name missing from loggerNames"
        << " on destroy: " << name << std::endl;
    exit(EXIT_FAILURE);
  }
  loggerNames.erase(name);
}



/* lprint(msgClass, text)
 * Internal printing function for Logger class
 * Params: References to the text that repersents the class of the
 *   message and the text of the message itself.
 * Effect: Prints standard formated message to stderr.
 */
void Logger::lprint (STRING msgClass, STRING text)
{
  std::cerr << name << " [" << msgClass << "]: " << text << std::endl;
}

// see header
void Logger::data (STRING text)
{
  if (detail == LoggerDetailLevel::Verbose)
    lprint("DATA", text);
}

// see header
void Logger::note (STRING text)
{
  if (detail != LoggerDetailLevel::Quiet)
    lprint("NOTE", text);
}

// see header
void Logger::warn (STRING text)
{
  lprint("WARN", text);
}

// see header
void Logger::fail (STRING text, int exitWith)
{
  lprint("FAIL", text);
  exit(exitWith);
}
