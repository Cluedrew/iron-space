#include "main-menu.hpp"
#include <catch.hpp>

/* Tests for the MainMenu WorldState.
 */

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
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

    // Also, I checked, MainMenu will delete itself in this case and
    // deleting it again [delete(menu);] is invalid.
  }

  /*SECTION("Check draw (can only check for crashes)")
  {
    // Made to be the same size as the true window.
    sf::RenderTexture target;
    target.create(800, 600);

    MainMenu menu;
    target.draw(menu);
  }*/
}
