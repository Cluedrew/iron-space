#include "plane.hpp"
#include <catch.hpp>

/* Tests for the Plane Container.
 * Currently there is not a lot to test, but I'm getting started.
 *
 * TODO I would like to remove the GameObject from the tests here but first
 * I should find a way to make sure that the GameObject ant the TestObject
 * have the same behaviour, where relativant.
 */

#include <vector>
#include "object/game-object.hpp"
#include "inst/null-game-object.hpp"
#include "physics/circle-collider.hpp"



// Replacement for the GameObject for testing the Plane.
struct TestObject
{
  Collider * body;

  TestObject() :
  /* Create a new TestObject with no body, it will never collide.
   */
      body(nullptr)
  {}

  TestObject(Collider * body) :
  /* Create a new TestObject with a body.
   * Params: Pointer to Collider, TestObject takes ownership.
   */
      body(body)
  {}

  bool collides (TestObject const & other) const
  {
    return body && other.body && body->collides(*other.body);
  }

  bool collides (Collider const & other) const
  {
    return body && body->collides(other);
  }
};



TEST_CASE("Testing for the Plane container.", "")
{
  SECTION("Checking emplace (TestObject)")
  {
    Plane<TestObject> plane;
    plane.emplace(TestObject());
    plane.emplace();
    Plane<TestObject>::iterator it = plane.begin();
    Plane<TestObject>::iterator endOfPlane = plane.end();
    REQUIRE( it != endOfPlane );
    ++it;
    REQUIRE( it != endOfPlane );
    ++it;
    REQUIRE( it == endOfPlane );
  }

  SECTION("Checking emplace (GameObject)")
  {
    Plane<GameObject> plane;
    plane.emplace(NullGameObject());
    Plane<GameObject>::iterator it = plane.begin();
    Plane<GameObject>::iterator endOfPlane = plane.end();
    REQUIRE( it != endOfPlane );
    ++it;
    REQUIRE( it == endOfPlane );
  }

  SECTION("Checking overlapping")
  {
    Plane<TestObject> plane;
    CircleCollider bodyA(5, 5, 1);
    CircleCollider bodyB(5, 7, 1);
    CircleCollider bodyC(5, 9, 1);

    plane.emplace(TestObject(&bodyA));
    plane.emplace(TestObject(&bodyB));
    plane.emplace(TestObject(&bodyC));

    std::vector<TestObject*> hits(plane.overlapping(CircleCollider(5, 6, 1)));
    REQUIRE( 2 == hits.size() );
    if (&bodyA == hits[0]->body)
    {
      CHECK( &bodyB == hits[1]->body );
    }
    else
    {
      CHECK( &bodyB == hits[0]->body );
      CHECK( &bodyA == hits[1]->body );
    }
  }
}
