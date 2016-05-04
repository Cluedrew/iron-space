#ifndef LOGGER_HPP
#define LOGGER_HPP

/* A class for logging messages with text streams.
 *
 * Message format:
 * <logger name> (<message type>): <message text>
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
 */



enum class LoggerDetailLevel : char { Verbose, Normal, Quiet };

class Logger
{
private:
  std::map<std::string,Logger> loggers;
  Logger ();
protected:
public:
  virtual ~Logger ();

  Logger & requestLogger (std::string const &);

  void note (std::string const &);
  void data (std::string const &);
  void warn (std::string const &);
  void fail (std::string const &, int exitWith = 1);
};


// Fail will either call exit or throw this exception.
class LoggerQuitExecption : public Exception
{
  char * what ();
  int exitCode ();
};

#endif//LOGGER_HPP
