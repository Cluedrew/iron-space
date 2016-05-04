/* Main file for InkV8.0: iron-space
 *
 * Handles arguments and sets up the Engine.
 *
 * Currently there are no arguments to handle, no settings to adjust in the
 * Engine and not even any checks on the exit value. So it is boring.
 */

int main (int argc, char * argv[])
{
  Engine gameEngine;
  return gameEngine.runLoop();
}
