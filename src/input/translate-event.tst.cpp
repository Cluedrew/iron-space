#include "translate-event.hpp"
#include <catch.hpp>

/* Tests the translateEvent and pollTranslateEvent functions using an
 * EventStream helper.
 *
 * The EventStream helper replaces SFML window here to create a source of
 * input that doesn't have to come from the user. This is only nessasary
 * for pollTranslateEvent, but it is also just used for convence.
 */

#include "event-stream.tst.hpp"
#include "input-event.hpp"



TEST_CASE("translateEvent and pollTranslateEvent tests", "[input]")
{
  EventStream stream;
  InputEvent iEvent;

  SECTION("No Events")
  {
    REQUIRE_FALSE( pollTranslateEvent(stream, iEvent) );
  }

  SECTION("Non-Tranlated Events")
  {
    // Note: I don't even know what this event is, so I figure it is pretty
    // unlikely I ever use it for anything.
    sf::Event ignoredEvent = {.type = sf::Event::SensorChanged};
    REQUIRE_FALSE( translateEvent(ignoredEvent, iEvent) );

    stream.addEvent(ignoredEvent);
    stream.addClosed();
    stream.addEvent(ignoredEvent);
    REQUIRE( pollTranslateEvent(stream, iEvent) );
    REQUIRE( InputEvent::Quit == iEvent.type );
    REQUIRE_FALSE( pollTranslateEvent(stream, iEvent) );
  }

  SECTION("Event Translation Checks")
  {
    SECTION("Check Quit")
    {
      stream.addClosed();
      REQUIRE( pollTranslateEvent(stream, iEvent) );
      CHECK( InputEvent::Quit == iEvent.type );
    }

    SECTION("Check Select")
    {
      stream.addMouseLeftPress(10, 15);
      stream.addMouseLeftPress(15, -5);
      REQUIRE( pollTranslateEvent(stream, iEvent) );
      CHECK( InputEvent::Select == iEvent.type );
      CHECK( 10 == iEvent.pos.x );
      CHECK( 15 == iEvent.pos.y );
      REQUIRE( pollTranslateEvent(stream, iEvent) );
      CHECK( InputEvent::Select == iEvent.type );
      CHECK( 15 == iEvent.pos.x );
      CHECK( -5 == iEvent.pos.y );
      REQUIRE_FALSE( pollTranslateEvent(stream, iEvent) );
    }

    SECTION("Check Pause")
    {
      sf::Event spaceBar = {.type = sf::Event::KeyPressed};
      spaceBar.key.code = sf::Keyboard::Space;
      REQUIRE( translateEvent(spaceBar, iEvent) );
      CHECK( InputEvent::Pause == iEvent.type );
    }

    SECTION("Check Point")
    {
      // Piggy backs Select a bit.
      stream.addMouseRightPress(3, 4);
      REQUIRE( pollTranslateEvent(stream, iEvent) );
      CHECK( InputEvent::Point == iEvent.type );
      CHECK( 3 == iEvent.pos.x );
      CHECK( 4 == iEvent.pos.y );
    }
  }
}
