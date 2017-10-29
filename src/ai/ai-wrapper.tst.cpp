#include "ai-wrapper.hpp"
#include <catch.hpp>

/* Test the AiWrapper.
 * Mostly the assertion about being given to a PlaneObject seems to be going
 * off more than it should.
 */

#include "object/plane-object.hpp"
#include "physics/null-physics.hpp"
#include "graphics/null-graphics.hpp"

#include "ai/null-ai.hpp"



TEST_CASE("Testing for the AiWrapper.", "[ai]")
{
  SECTION("Check Contstruction and the init function.")
  {
    PlaneObject test(new AiWrapper(), new NullPhysics(), new NullGraphics());
    test.updateStep(sf::Time::Zero);
  }
}
