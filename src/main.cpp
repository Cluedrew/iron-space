/* Main file for InkV8.0: iron-space
 *
 * Handles arguments and sets up the Engine.
 *
 * Currently there are no arguments to handle, no settings to adjust in the
 * Engine and not even any checks on the exit value. So it is boring.
 */

#include <iostream>
#include "util/math.hpp"

int main (int argc, char * argv[])
{
  //Engine gameEngine;
  //return gameEngine.runLoop();

  int a = 5;
  int b = 7;
  int d = diff(a,b);

  std::cout << "Diff of "  << a << " & " << b << " is " << d << ".";
  std::cout << std::endl;
}
