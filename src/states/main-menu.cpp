#include "main-menu.hpp"

// Implement the main menu screen.

#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "../input/input-event.hpp"
#include "../util/command.hpp"
#include "../button.hpp"
#include "../text-fragment.hpp"
#include "running-state.hpp"

#include <cassert>



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
  //GameObject * button = new Button(new StartGame(*this),
  //                                 100.0f, 100.0f, 50.0f, 50.0f);
  //assert(button->getPosition().x == 100.0f);
  //delete button;

  gui.emplace(Button(new StartGame(*this),
                     100.0f, 100.0f, 50.0f, 50.0f));
  //assert(gui.begin()->getPosition().x == 100.0f);
  gui.emplace(TextFragment("iron-space"));
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
  for (PlaneDrawable<GameObject>::iterator it = gui.begin() ;
       it != gui.end() ; ++it)
  {
    // This doesn't fix the problem as I had hoped. It does change the
    // position of the collider to be the same place as the drawn box,
    // but both of those are still wrong.

    //assert(it->getPosition().x == 0);

    // The object updates itself properly with this, but still doesn't start
    // in the right place.
    //it->move(1, 1);

    it->updateAi(deltaT);
  }
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
