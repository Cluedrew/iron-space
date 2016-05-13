#include "engine.hpp"

// Implementation of the games internal Engine.

#include <thread>
#include <chrono>


Engine::Engine (/*Settings*/) :
  timer(), increment(sf::milliseconds(1000/60))
{}

Engine::~Engine ()
{}

// see header
int Engine::runLoop ()
{
  bool running = true;
  while (running)
  {
    poolInput();
    updateAi(increment);
    updatePhysics(increment);
    resolveCollisions();
    render();
    wait();
  }
}


void /*bool*/ Engine::pollInput ();
void Engine::updateAi (sf::Time const & deltaT);
void Engine::updatePhysics (sf::Time const & deltaT);
void Engine::resolveCollisions ();
void Engine::render ();

/* wait()
 * Wait until one interements of time has passed since the last call to wait,
 *   or since the object was constructed. If more than that amount of time has
 *   passed return quickly.
 * Effect: Resets the timer.
 */
void Engine::wait ()
{
  sf::Time time = timer.getElapsedTime();
  if (time < increment)
  {
    sf::Time diff = increment - time;
    std::chrono::duration<int, std::milli> waitTime(diff.asMilliseconds());
    std::this_thread::sleep_for<int, std::milli>(waitTime);
  }
  timer.restart();
}
