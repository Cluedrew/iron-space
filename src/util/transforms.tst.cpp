#include "transforms.hpp"
#include <catch.hpp>

/* Tests for the transforms utility file.
 *
 * Most of these are pretty basic.
 */

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Transform.hpp>
#include <SFML/Graphics/Transformable.hpp>



TEST_CASE("Tests for the transforms file.", "[util]")
{
  SECTION("Check xyTransformable")
  {
    sf::Transformable xy = xyTransformable(2.5, 3.5);
    REQUIRE( sf::Vector2f(2.5, 3.5) == xy.getPosition() );
    REQUIRE( 0.0f == xy.getRotation() );
    REQUIRE( sf::Vector2f(1, 1) == xy.getScale() );
  }
}
