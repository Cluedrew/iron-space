#include "text-graphics.hpp"
#include <catch.hpp>

/* So, due to the slightly experemental nature of TextGraphics (trying
 * to create less repetitive classes) this is not quite the write and go
 * I would hope it would be.
 */

#include <SFML/Graphics/RenderTexture.hpp>



TEST_CASE("Testing for the TestGraphics GraphicsComponent.")
{
  SECTION("Check draw (can only check for crashes)")
  {
    // Made to be the same size as the true window.
    sf::RenderTexture target;
    target.create(800, 600);

    TextGraphics text("FreeSans.ttf", "Testing");
    target.draw(text);
  }
}
