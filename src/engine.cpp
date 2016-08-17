#include "engine.hpp"

// Implementation of the games internal Engine.

//#include <SFML/Window/Event.hpp>
#include "input/event-handler.hpp"
#include "states/running-state.hpp"



Engine::Engine (LoggerDetailLevel logdl) :
  window(), state(new RunningState()), clock(60), log("Engine", logdl)
{}

Engine::~Engine ()
{
  delete state;
}

// see header
int Engine::runLoop ()
{
  log.note("Begin runLoop");

  window.create(sf::VideoMode(800, 600), "iron-space",
                sf::Style::Titlebar | sf::Style::Close);
  // For now it is not sf::Style::Resize-able.

  log.note("Finished runLoop init");

  bool running = true;
  while (running)
  {
    running = pollInput();
    log.data("Begin update");
    state->update(clock.getIncrement());
    log.data("End update");
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
    Response re = eventHandler.pollEvents(window, *state);
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

void Engine::render ()
/* Draw everything too the screen and preform the frame swap.
 * Effect: Draws to the window.
 */
{
  log.data("Begin render");
  window.clear(sf::Color::Black);
  window.draw(*state);
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
