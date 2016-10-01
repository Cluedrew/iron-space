#ifndef COMMAND_HPP
#define COMMAND_HPP

/* Command interface. This is a closure style command and just has the call
 * operator defined with no operators. It is a very minimal command interface.
 */



struct Command
{
  Command () {}
  virtual ~Command () {}

  virtual void operator() () =0;
};

#endif//COMMAND_HPP
