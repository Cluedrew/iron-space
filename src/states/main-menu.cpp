#include "main-menu.hpp"

// Implement the main menu screen.

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "input/input-event.hpp"
#include "util/command.hpp"
#include "inst/button.hpp"
#include "inst/text-fragment.hpp"
#include "util/alignment.hpp"
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
  // Try to make relative to the window some day.
  gui.emplace(TextFragment("iron-space", 400.0f, 100.0f,
                           Alignment2D::MiddleCenter));
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
  for (PlaneDrawable<Widget>::iterator it = gui.begin() ;
       it != gui.end() ; ++it)
  {
    it->updateAi(deltaT);
  }

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
