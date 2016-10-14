#include "game-object-ptr.hpp"

/* Testing Code for the GameObjectPtr. This also includes testing for the
 * code in the GameObject that works with the pointer. That is all tested
 * here.
 *
 * I think I have most of the cases covered. I may have spent a bit more time
 * (and code) on the trival cases than was needed. The "Check Auto-Null" tests
 * near the ends are the complex ones (and the ones that actually caught an
 * error).
 */

#include "catch.hpp"
#include "game-object.hpp"
#include "objects/null-game-object.hpp"



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
    GameObject object = NullGameObject();
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
    GameObject objs[2] = {NullGameObject(), NullGameObject()};
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
    GameObject obj = NullGameObject();
    GameObjectPtr ptr(obj);
    REQUIRE( &obj == &*ptr );
  }

  SECTION("Check assignment")
  {
    GameObject obj1 = NullGameObject();
    GameObject obj2 = NullGameObject();
    GameObjectPtr ptrA(obj1);
    GameObjectPtr ptrB(ptrA);
    CHECK( ptrA == ptrB );
    //ptrA = obj2;
    ptrA.setTo(obj2);
    CHECK( &*ptrA == &obj2 );
    ptrB = ptrA;
    CHECK( &*ptrB == &obj2 );
    ptrA = makePtrTo(obj1);
    CHECK( &*ptrA == &obj1 );
  }

  SECTION("Check Auto-null")
  {

    SECTION("Simple Case")
    {
      GameObject * dynobj = new NullGameObject();
      GameObjectPtr ptr(*dynobj);
      REQUIRE( ptr );
      REQUIRE( &*ptr == &*dynobj );
      delete dynobj;
      REQUIRE_FALSE( ptr );
    }

    SECTION("takeRegester")
    {
      GameObject * obj1 = new NullGameObject();
      GameObject * obj2 = new NullGameObject();
      GameObjectPtr ptr1(makePtrTo(*obj1));
      CHECK( &*ptr1 == &*obj1 );

      ptr1 = makePtrTo(*obj2);
      CHECK( &*ptr1 == &*obj2 );
      delete obj1;
      CHECK( ptr1.nonNull() );
      delete obj2;
      CHECK( ptr1.isNull() );
    }

    SECTION("Mass Auto-Null")
    {
      int const n = 16;
      GameObject * obj = new NullGameObject();
      GameObjectPtr ptrs[n];
      for (int i = 0 ; i < n ; ++i)
      {
        ptrs[i].setTo(*obj);
      }
      delete obj;
      bool allNull = true;
      for (int i = 0 ; i < n ; ++i)
      {
        allNull &= ptrs[i].isNull();
      }
      CHECK( allNull );
    }
  }
}
