#ifndef ENGINE_HPP
#define ENGINE_HPP

/* Class that repersents the core of the game. The constructor sets up all
 * the 'global' resources, the deconstructor takes them down and runLoop is
 * essentally the game itself.
 *
 * This class exists to break up the main loop across more functions, while
 * still keeping them all in the same scope, but not opening the scope up to
 * the global interface.
 */



class Engine
{
private:
  Plane gui;
  Plane map;

  void /*bool*/ pollInput ();
  void updateAi (sf::Time const &);
  void updatePhysics (sf::Time const &);
  void resolveCollisions ();
  void render ();

protected:
public:
  Engine (/*Settings*/);
  virtual ~Engine ();

  int runLoop ();
  /* Run the game.
   * Effect: Many, it runs the entire game.
   * Return: The requested exit code, so 0 means the game ran successfully,
   *   non-zero is an error report.
   */
};

#endif//ENGINE_HPP
