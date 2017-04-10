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
  WhileAliveChild (bool & marker, ReferenceCounter::DisableFlagType) :
    WhileAliveBase(marker), ReferenceCounter(ReferenceCounter::Disable) {}
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

  SECTION("Check with multiple pointers and changing pointers.")
  {
    bool isAlive0 = false;
    bool isAlive1 = false;
    {
      CountPtr<WhileAlive> p0 = new WhileAlive(isAlive0);
      REQUIRE( isAlive0 );
      {
        CountPtr<WhileAlive> p1 = p0;
        REQUIRE( isAlive0 );
      }
      REQUIRE( isAlive0 );

      {
        CountPtr<WhileAlive> p2 = new WhileAlive(isAlive1);
        p0 = p2;
        REQUIRE_FALSE( isAlive0 );
      }
      REQUIRE( isAlive1 );
    }
    REQUIRE_FALSE( isAlive1 );

    {
      CountPtr<WhileAlive> p0;
      p0 = new WhileAlive(isAlive0);
      REQUIRE( isAlive0 );
    }
    REQUIRE_FALSE( isAlive0 );
  }

  SECTION("Check reference type.")
  {
    bool isAlive = false;
    INFO("Part one");
    CountPtr<WhileAlive> ptr = new WhileAlive(isAlive);
    {
      INFO("Part one point one");
      CountRef<WhileAlive> ref = *ptr;
      INFO("Part one point two");
      ptr = nullptr;
      INFO("Part one point three");
      REQUIRE( isAlive );
      INFO("Part one point four");
    }
    REQUIRE_FALSE( isAlive );

    INFO("Part two");
    ptr = new WhileAlive(isAlive);
    {
      CountRef<WhileAlive> r0 = *ptr;
      ptr = nullptr;
      REQUIRE( isAlive );
      CountRef<WhileAlive> r1 = r0;
    }
    REQUIRE_FALSE( isAlive );
  }

  SECTION("Check use of ReferenceCounter::Disable.")
  {
    bool isAlive = false;
    {
      WhileAliveChild wac(isAlive, ReferenceCounter::Disable);
      REQUIRE( isAlive );
      {
        CountRef<WhileAliveChild> ptr(wac);
      }
      REQUIRE( isAlive );
    }
    REQUIRE_FALSE( isAlive );
  }
}
