#include "engine.hpp"

// Implementation of the games internal Engine.

#include "input/translate-event.hpp"
#include "states/running-state.hpp"
#include "states/pause-screen.hpp"



Engine::Engine (LoggerDetailLevel logdl) :
  running(true), window(), state(new PauseScreen(new RunningState())),
  clock(60), log("Engine", logdl)
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

  log.note("Finished runLoop init");

  while (running)
  {
    pollInput();
    update();
    render();
    wait();
  }

  window.close();
  log.note("End runLoop");
  return 0;
}


void Engine::pollInput ()
/* Collect and distribut all input over the last frame.
 * Effect: Collects input from the window the the EventHandler and processes
 *   them.
 * Return: Should the program continue running?
 */
{
  log.data("Begin pollInput");

  InputEvent iEvent;

  while (pollTranslateEvent<sf::Window>(window, iEvent))
  {
    if (InputEvent::Quit == iEvent.type)
    {
      running = false;
      log.data("End pollInput (Quitting)");
      return;
    }
    state.update(state->handleInput(iEvent));
  }
  log.data("End pollInput");
}

void Engine::update ()
{
    log.data("Begin update");
    state.update(state->update(clock.getIncrement()));
    log.data("End update");
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
