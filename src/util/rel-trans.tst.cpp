#include "rel-trans.hpp"

/* Tests for the RelativeTransformable class. The first TEST_CASE is also
 * a bit of a sanity check, making sure that the identity Transformable
 * stored in the RelativeTransformable is actually the identity. SFML does
 * not define what the default transformable is, so I want to make sure it
 * never changes. The second is actually tests about relative transformation.
 */

#include <catch.hpp>



// I think I should get another tag for this one, but I'm not sure what.
TEST_CASE("Confirm RelativeTransformable::identity", "[util]")
{
  sf::Transformable const & identity = RelativeTransformable::identity;

  sf::Vector2f zeros(0, 0);
  sf::Vector2f ones(1, 1);
  REQUIRE( sf::Vector2f(0, 0) == identity.getPosition() );
  REQUIRE( 0 == identity.getRotation() );
  REQUIRE( sf::Vector2f(1, 1) == identity.getScale() );
  REQUIRE( sf::Vector2f(0, 0) == identity.getOrigin() );
}

TEST_CASE("Check the RelativeTransformableable class", "[util]")
{
  sf::Transformable parent;
  parent.setPosition(2, 2);
  RelativeTransformable child;
  child.setRelPosition(2, 2);
  child.update(parent);

  REQUIRE( sf::Vector2f(4, 4) == child.getAbsPosition() );
  // TODO Add more ...
}
