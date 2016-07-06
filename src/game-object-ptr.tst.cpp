#include "game-object-ptr.hpp"

/* Testing Code for the GameObjectPtr. This also includes testing for the
 * code in the GameObject that works with the pointer. That is all tested
 * here.
 *
 * WIP, have more tests to add. Also REQUIRE or CHECK?
 */

#include "catch.hpp"
#include "game-object.hpp"



GameObjectPtr makePtrTo (GameObject & object)
/* Create a new GameObjectPtr pointing to the given object and return it.
 * Params: A reference to the GameObject the pointer will point to.
 * Return: A new GameObjectPtr.
 */
{
  return GameObjectPtr(object);
}



TEST_CASE("Tests for the GameObjectPtr", "")
{
  SECTION("Check initial state")
  {
    GameObjectPtr ptr;
    CHECK_FALSE( ptr );
    CHECK_FALSE( ptr.nonNull() );
    CHECK( ptr.isNull() );
  }

  SECTION("Check construction")
  {
    GameObject object;
    GameObjectPtr ptr1(object);

    SECTION("Target Constructor")
    {
      CHECK( ptr1 );
      CHECK( ptr1.nonNull() );
      CHECK_FALSE( ptr1.isNull() );
    }

    SECTION("Copy Constructor")
    {
      GameObjectPtr ptr2(ptr1);
      CHECK( ptr2 );
    }

    SECTION("Move Constructor")
    {
      GameObjectPtr ptr3(makePtrTo(object));
      CHECK( ptr3 );
    }
  }

  //SECTION("Check assignment")

  SECTION("Comparison")
  {
    // Equality
    GameObject o1;
    GameObject o2;
    GameObjectPtr ptr1(o1);
    GameObjectPtr ptr2(o2);
    GameObjectPtr ptr3(o1);
    REQUIRE( ptr1 != ptr2 );
    REQUIRE( ptr1 == ptr3 );
    REQUIRE_FALSE( ptr1 == ptr2 );
    REQUIRE_FALSE( ptr1 != ptr3 );
  }

  //SECTION("Check access")
}
