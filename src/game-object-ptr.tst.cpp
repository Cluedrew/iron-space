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
      CHECK( ptr2 == ptr1 );
    }

    SECTION("Move Constructor")
    {
      GameObjectPtr ptr3(makePtrTo(object));
      CHECK( ptr3 );
    }
  }

  SECTION("Check Comparison")
  {
    GameObject objs[2] = {GameObject(), GameObject()};
    GameObjectPtr ptr1(objs[0]);
    GameObjectPtr ptr2(objs[1]);
    GameObjectPtr ptr3(objs[0]);

    // These in particular are used in other tests, so REQUIRE them.
    SECTION("Check Equality")
    {
      REQUIRE( ptr1 != ptr2 );
      REQUIRE( ptr1 == ptr3 );
      REQUIRE_FALSE( ptr1 == ptr2 );
      REQUIRE_FALSE( ptr1 != ptr3 );
    }

    SECTION("Check Ordering")
    {
      CHECK( ptr1 < ptr2 );
      CHECK_FALSE( ptr1 < ptr3 );
      CHECK_FALSE( ptr2 < ptr1 );

      CHECK( ptr2 > ptr1 );
      CHECK_FALSE( ptr3 > ptr1 );
      CHECK_FALSE( ptr1 > ptr2 );

      CHECK( ptr1 <= ptr2 );
      CHECK( ptr1 <= ptr3 );
      CHECK_FALSE( ptr2 <= ptr1 );

      CHECK( ptr2 >= ptr1 );
      CHECK( ptr3 >= ptr1 );
      CHECK_FALSE( ptr1 >= ptr2 );
    }
  }

  SECTION("Check access")
  {
    GameObject obj;
    GameObjectPtr ptr(obj);
    REQUIRE( &obj == &*ptr );
  }

  SECTION("Simple Deregester")
  {
    GameObject *dynobj = new GameObject();
    GameObjectPtr ptr(*dynobj);
    REQUIRE( ptr );
    REQUIRE( &*ptr == &*dynobj );
    delete dynobj;
    REQUIRE_FALSE( ptr );
  }

  /*SECTION("Check assignment")
  {
    GameObject obj1;
    GameObject obj2;
  }*/
}
