#include "main-menu.hpp"
#include <catch.hpp>

/* Tests for the MainMenu WorldState.
 */

#include <SFML/System/Time.hpp>
#include "running-state.hpp"



TEST_CASE("Tests for the MainMenu class.", "[states]")
{
  SECTION("Test StartGame")
  {
    MainMenu * menu = new MainMenu();
    WorldState * nextState;

    nextState = menu->update(sf::Time::Zero);
    REQUIRE( menu == nextState );

    menu->startGame();
    nextState = menu->update(sf::Time::Zero);
    REQUIRE( nullptr != dynamic_cast<RunningState*>(nextState) );
    delete(nextState);
  }
}
