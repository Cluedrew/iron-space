#include "engine.hpp"

// Implementation of the games internal Engine.

#include <SFML/Window/Event.hpp>
#include "input/event-handler.hpp"
#include "game-object.hpp"



Engine::Engine (LoggerDetailLevel logdl) :
  window(), clock(60), log("Engine", logdl),
  map()
{}

Engine::~Engine ()
{}

// see header
int Engine::runLoop ()
{
  log.note("Begin runLoop");

  window.create(sf::VideoMode(800, 600), "iron-space",
                sf::Style::Titlebar | sf::Style::Close);
  // For now it is not sf::Style::Resize-able.

  map.insert(GameObject());

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
 * Effect: Collects input from the window the the EventHandler and processes
 *   them.
 * Return: Should the program continue running?
 */
{
  log.data("Begin pollInput");

  // This is not going to be static forever.
  static EventHandler eventHandler;

  while (true)
  {
    Response re = eventHandler.pollEvents(window);
    switch (re.type)
    {
    case Response::Done:
      log.data("End pollInput");
      return true;

    case Response::Quit:
      log.data("End pollInput");
      return false;

    default:
      log.warn("Uncaught Response in pollInput");
      break;
    }
  }

  log.warn("Reached end of pollInput body.");
  return true;
}

void Engine::updateAi (sf::Time const & deltaT)
/* Gets all GameObjects to update their AI.
 * Params: Length of the current frame.
 * Effect: Updates AI according to the time passed and the recent input.
 */
{
  log.data("Begin updateAi");
  log.data("End updateAi");
}

void Engine::updatePhysics (sf::Time const & deltaT)
/* Gets all GameObjects to update their physics.
 * Params: Length of the current frame.
 * Effect: Updates Physics according to the time passed and the recent
 *   AI decisions.
 */
{
  log.data("Begin updatePhysics");
  log.data("End updatePhysics");
}

void Engine::resolveCollisions ()
/* Checks for collisions, that is any overlapping objects.
 * Effect: Triggers collision resloving code for any collisions (overlap)
 *   that are occuring.
 */
{
  log.data("Begin resolveCollisions");
  log.data("End resolveCollisions");
}

void Engine::render ()
/* Draw everything too the screen and preform the frame swap.
 * Effect: Draws to the window.
 */
{
  log.data("Begin render");
  window.clear(sf::Color::Black);
  window.draw(map);
  window.display();
  log.data("End render");
}

void Engine::wait ()
/* Wait until one interements of time has passed since the last call to wait,
 *   or since the object was constructed. If more than that amount of time has
 *   passed return quickly.
 * Effect: Resets the timer.
 */
{
  log.data("Begin wait");
  clock.wait();
  log.data("End wait");
}
