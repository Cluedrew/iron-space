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
 * Not that fail (as well as any invalid use of the logger) will result in
 * exit() being called. It repersents a critical failure.
 *
 * I could argument this class, but currently I have found very little use for
 * its current form. Its only use case is easily adding and removing debug
 * messages. Everything else seems to be better handled by up-front testing to
 * make sure the code does what it is supposed to do.
 */

#include <string>



class Logger
{
public:
  enum class DetailLevel : char {Verbose, Normal, Quiet};

private:
  std::string name;
  DetailLevel detail;

  void lprint (std::string const & msgClass, std::string const & text);

protected:
public:
  Logger (std::string const & name, DetailLevel detail);
  /* Create a new Logger.
   * Params: A string that repersents the name of the logger (no existing
   *   logger can have that name) and the detail level of the logger.
   * Effect: The Logger's name is resurved until it is distroyed.
   */

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
