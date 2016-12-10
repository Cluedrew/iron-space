#include "game-object.hpp"
#include <catch.hpp>

/* Tests for the GameObject.
 *
 * Note: This one requires a number of testing tools and since none of them
 * are currently used elsewhere, I make them here.
 */

#include <cassert>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include "ai/null-ai.hpp"
#include "physics/null-physics.hpp"
#include "graphics/null-graphics.hpp"
#include "graphics/graphics-component.hpp"
#include "util/transforms.hpp"



class RecordDraw : public GraphicsComponent
/* A GraphicsComponent that records copies of the states it was called with.
 * Does not draw anything.
 */
{
private:
  mutable std::vector<sf::RenderStates> recordedStates;

protected:
public:
  RecordDraw () :
    GraphicsComponent(), recordedStates()
  {}

  virtual ~RecordDraw () {}

  void draw (sf::RenderTarget & target, sf::RenderStates states) const
  {
    recordedStates.push_back(states);
  }

  unsigned int countCalls ()
  {
    return recordedStates.size();
  }

  sf::RenderStates getState (unsigned int i)
  {
    assert(i < recordedStates.size());

    return recordedStates[i];
  }
};



class RecordUpdate : public Collider
/* A Collider (for use in a PhysicsComponent) that records its incomming
 * calls and does not collide.
 */
{
private:
  mutable std::vector<sf::Transform> recordedTransforms;

protected:
public:
  virtual ~RecordUpdate () {}

  void update (sf::Transform const & root)
  {
    recordedTransforms.push_back(root);
  }

  bool collides (Collider const & other) const
  { return false; }

  bool collides (ColliderLeaf const & other) const
  { return false; }

  unsigned int countCalls ()
  {
    return recordedTransforms.size();
  }

  sf::RenderStates getState (unsigned int i)
  {
    assert(i < recordedTransforms.size());

    return recordedTransforms[i];
  }
};

// It is a graphics component, but is not about that.
class IsAliveComponent : public GraphicsComponent
{
private:
  bool & aliveField;

protected:
public:
  IsAliveComponent (bool & aliveField_) :
    aliveField(aliveField_)
  {
    aliveField = true;
  }

  virtual ~IsAliveComponent ()
  {
    aliveField = false;
  }

  void draw (sf::RenderTarget & target, sf::RenderStates states) const {}
};

GameObject makeAndReturn(float x, float y, AiComponent * ai,
    PhysicsComponent * physics, GraphicsComponent * graphics)
{
  GameObject obj(xyTransformable(x, y), ai, physics, graphics);
  return obj;
}



TEST_CASE("Tests for the GameObject.", "")
{
  SECTION("Check transform constructor")
  {
    sf::Transformable complexLoc;
    complexLoc.setPosition(10, 20);
    complexLoc.setRotation(90);
    complexLoc.setScale(3, 4);

    GameObject obj(complexLoc, new NullAi(),
                   new NullPhysics(), new NullGraphics());
    REQUIRE( complexLoc.getPosition() == obj.getPosition() );
    REQUIRE( complexLoc.getRotation() == obj.getRotation() );
    REQUIRE( complexLoc.getScale() == obj.getScale() );
  }

  SECTION("Check move constructor.")
  {
    bool isGraphicsAlive = false;
    {
      GameObject dest = makeAndReturn(3, 4, new NullAi(), new NullPhysics(),
                                      new IsAliveComponent(isGraphicsAlive));
      CHECK( isGraphicsAlive );
      CHECK( sf::Vector2f(3, 4) == dest.getPosition() );
    }
    CHECK_FALSE( isGraphicsAlive );
  }

  SECTION("Check GameObject::draw")
  {
    RecordDraw * record = new RecordDraw();
    sf::RenderTexture target;

    SECTION("Simple indirect call.")
    {
      sf::Transform nonTransform;
      GameObject obj(new NullAi(), new NullPhysics(), record);
      target.draw(obj);
      REQUIRE( 1 == record->countCalls() );
      REQUIRE( nonTransform == record->getState(0).transform );
    }

    SECTION("Object with transform.")
    {
      sf::Transformable shift = xyTransformable(3, 5);
      GameObject obj(shift, new NullAi(), new NullPhysics(), record);
      target.draw(obj);
      REQUIRE( 1 == record->countCalls() );
      REQUIRE( shift.getTransform() == record->getState(0).transform );
    }

    SECTION("State with transform.")
    {
      sf::Transformable shift = xyTransformable(3, 5);
      GameObject obj(new NullAi(), new NullPhysics(), record);
      target.draw(obj, shift.getTransform());
      REQUIRE( 1 == record->countCalls() );
      REQUIRE( shift.getTransform() == record->getState(0).transform );
    }

    SECTION("Object and state with transform.")
    {
      sf::Transformable shift1 = xyTransformable(3, 5);
      sf::Transformable shift2 = xyTransformable(7, 13);
      GameObject obj(shift1, new NullAi(), new NullPhysics(), record);
      target.draw(obj, shift2.getTransform());
      REQUIRE( 1 == record->countCalls() );
      sf::Transformable shift3 = xyTransformable(10, 18);
      REQUIRE( shift3.getTransform() == record->getState(0).transform );
    }
  }
}
