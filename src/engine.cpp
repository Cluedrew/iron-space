#include "engine.hpp"

// Implementation of the games internal Engine.

#include <SFML/Window/Event.hpp>



Engine::Engine (LoggerDetailLevel logdl) :
  window(), clock(60), log("Engine", logdl)
{}

Engine::~Engine ()
{}

// see header
int Engine::runLoop ()
{
  log.note("Begin runLoop");

  window.create(sf::VideoMode(800, 600), "iron-space");//,
//                sf::Style::Titlebar | sf::Style::Close);
  // For now it is not sf::Style::Resize-able.

  log.note("Finished runLoop init");

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

  window.close();
  log.note("End runLoop");
  return 0;
}


bool Engine::pollInput ()
/* Collect and distribut all input over the last frame.
 * Effect: TODO
 * Return: Should the program continue running?
 */
{
  log.data("Begin pollInput");

  bool running = true;
  sf::Event event;

  while (window.pollEvent(event))
  {
    switch (event.type)
    {
    case sf::Event::Closed:
      running = false;
      break;
    default:
      break;
    }
  }

  log.data("End pollInput");
  return running;
}

void Engine::updateAi (sf::Time const & deltaT)
/* Gets all GameObjects to update their AI.
 * Params: Length of the current frame.
 * Effect: TODO
 */
{
  log.data("Begin updateAi");
  log.data("End updateAi");
}

void Engine::updatePhysics (sf::Time const & deltaT)
/* Gets all GameObjects to update their physics.
 * Params: Length of the current frame.
 * Effect: TODO
 */
{
  log.data("Begin updatePhysics");
  log.data("End updatePhysics");
}

void Engine::resolveCollisions ()
/* Checks for collisions, that is any overlapping objects.
 * Effect: TODO
 */
{
  log.data("Begin resolveCollisions");
  log.data("End resolveCollisions");
}

void Engine::render ()
/* Draw everything too the screen and preform the frame swap.
 * Effect: TODO
 */
{
  log.data("Begin render");
  log.data("End render");
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
