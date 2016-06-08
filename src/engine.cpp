#include "engine.hpp"

// Implementation of the games internal Engine.

#include <thread>
#include <chrono>



Engine::Engine (LoggerDetailLevel logdl) :
  clock(60), log("Engine", logdl)
{

}

Engine::~Engine ()
{}

// see header
int Engine::runLoop ()
{
  log.note("Begin runLoop");

  bool running = true;
  while (running)
  {
    running = pollInput();
    updateAi(clock.getIncrement());
    updatePhysics(clock.getIncrement());
    resolveCollisions();
    render();
    wait();
  }

  log.note("End runLoop");
  return 0;
}


bool Engine::pollInput ()
/* Collect and distribut all input over the last frame.
 * Effect: TODO
 * Return: Should the program continue running?
 */
{
  log.data("Called pollInput");
  return false;
}

void Engine::updateAi (sf::Time const & deltaT)
/* Gets all GameObjects to update their AI.
 * Params: Length of the current frame.
 * Effect: TODO
 */
{
  log.data("Called updateAi");
}

void Engine::updatePhysics (sf::Time const & deltaT)
/* Gets all GameObjects to update their physics.
 * Params: Length of the current frame.
 * Effect: TODO
 */
{
  log.data("Called updatePhysics");
}

void Engine::resolveCollisions ()
/* Checks for collisions, that is any overlapping objects.
 * Effect: TODO
 */
{
  log.data("Called resolveCollisions");
}

void Engine::render ()
/* Draw everything too the screen and preform the frame swap.
 * Effect: TODO
 */
{
  log.data("Called render");
}

/* wait()
 * Wait until one interements of time has passed since the last call to wait,
 *   or since the object was constructed. If more than that amount of time has
 *   passed return quickly.
 * Effect: Resets the timer.
 */
void Engine::wait ()
{
  log.data("Begin wait");
  clock.wait();
  log.data("End wait");
}
