#ifndef LOGGER_HPP
#define LOGGER_HPP

/* A class for logging messages with text streams.
 *
 * Message format:
 * <logger name> [<message type>]: <message text>
 *
 * There are four types of messages that the logger can handle, for the most
 * part they are groupped by the information they display.
 * LoggerDetailLevel
 * Verbose : All messages are printed.
 * Normal : data messages are excluded.
 * Quiet : data and note messages are excluded.
 *
 * fail messages are special in that after desplaying the message the program
 * will quit (probably by exit, might use LoggerQuitException).
 *
 * TODO: LoggerDetailLevel -> Logger::DetailLevel ?
 *  Support for other types of streams for output.
 *  Collection of existing loggers. Maybe just their names?
 *
 * OK, yes, I don't know enough about what the logger should look like right
 * now. I think I will try having the logger enforce unique names. The user
 * has to hold it themselves. I use exit on error instead of throwing an
 * exception (for now) to force one to fix the problem.
 */

#include <string>



enum class LoggerDetailLevel : char { Verbose, Normal, Quiet };

class Logger
{
private:
  std::string name;
  LoggerDetailLevel detail;

  void lprint (std::string const & msgClass, std::string const & text);
protected:
public:
  Logger (std::string const & name, LoggerDetailLevel detail);

  Logger (Logger const &) = delete;
  Logger (Logger &&);

  virtual ~Logger ();

  Logger & operator= (Logger const &) = delete;
  Logger & operator= (Logger &&) = delete;

  void data (std::string const &);
  void note (std::string const &);
  void warn (std::string const &);
  void fail (std::string const &, int exitWith = 1);
  /* Message functions
   * Params: A string message
   * Effect: The message is printed to the logger's stream (stderr).
   *   fail also exits the program.
   */
};

#endif//LOGGER_HPP
