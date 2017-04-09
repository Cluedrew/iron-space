#include "count-ptr.hpp"
#include <catch.hpp>

// Test the usage of the CountPtr and CountRef.

class WhileAliveBase
{
  bool & marker;
public:
  WhileAliveBase (bool & marker) : marker(marker) {marker = true;}
  virtual ~WhileAliveBase () {marker = false;}
};


class WhileAlive : public WhileAliveBase
{
  unsigned int referenceCount_;
  friend class CountPtr<WhileAlive>;
  friend class CountRef<WhileAlive>;
public:
  WhileAlive (bool & marker) : WhileAliveBase(marker), referenceCount_(0) {}

  unsigned int getCount ()
  {
    return referenceCount_;
  }
};

class WhileAliveChild : public WhileAliveBase, public ReferenceCounter
{
public:
  WhileAliveChild (bool & marker) : WhileAliveBase(marker) {}
};

TEST_CASE("Testing CountPtr, CountRef and ReferenceCounter.", "[util]")
{
  SECTION("Check simple one pointer case.")
  {
    bool isAlive = false;
    {
      CountPtr<WhileAlive> ptr = new WhileAlive(isAlive);
      REQUIRE( isAlive );
    }
    REQUIRE_FALSE( isAlive );

    {
      CountPtr<WhileAliveChild> ptr = new WhileAliveChild(isAlive);
      REQUIRE( isAlive );
    }
    REQUIRE_FALSE( isAlive );
  }
}
