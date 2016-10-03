#include "main-menu.hpp"

// Implement the main menu screen.

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "../input/input-event.hpp"
#include "../util/command.hpp"
#include "../button.hpp"
#include "running-state.hpp"



// Helper Class, StartGame, for the Start Game button.
struct StartGame : public Command
{
  MainMenu & buttonOn;

  StartGame (MainMenu & buttonOn_) :
      buttonOn(buttonOn_)
  {}

  void operator() ()
  {
    buttonOn.startGame();
  }
};



MainMenu::MainMenu () :
  gui(), started(false)
{
  gui.emplace(Button(new StartGame(*this),
                     100.0f, 100.0f, 50.0f, 50.0f));
}

MainMenu::~MainMenu ()
{}

WorldState * MainMenu::handleInput (InputEvent const & ievent)
{
  gui.handleInput(ievent);

  return this;
}

WorldState * MainMenu::update (sf::Time const & deltaT)
{
  // TODO: This will actually be added, but first I think I need to
  // add something to the GameObject so that I don't need this step
  // for GameObject to finish their initialization.
  //gui.update(deltaT);

  if (started)
  {
    delete(this);
    return new RunningState();
  }

  return this;
}

void MainMenu::draw (sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(gui, states);
}

void MainMenu::startGame ()
{
  started = true;
}
