#include "event-stream.tst.hpp"

// Implementation of the event stream testing tool.

#include <cassert>
#include <limits>
#include <catch.hpp>



// Constructors and Deconstructor
EventStream::EventStream () :
  frames(), frame(0), fpos(0)
{
  addFrame();
}

EventStream::~EventStream () {}



// Steam Functions
bool EventStream::pollEvent (sf::Event & event)
{
  if (frames.size() <= frame)
    return false;
  else if (frames[frame].size() <= fpos)
  {
    ++frame;
    fpos = 0;
    return false;
  }
  else
  {
    event = frames[frame][fpos++];
    return true;
  }
}

void EventStream::reset ()
{
  frame = 0;
  fpos = 0;
}



// Getters
sf::Event & EventStream::getEvent (size_t frame, size_t pos)
{
  assert(frame < frames.size());
  assert(pos < frames[frame].size());
  return frames[frame][pos];
}

sf::Event const & EventStream::getEvent (size_t frame, size_t pos) const
{
  assert(frame < frames.size());
  assert(pos < frames[frame].size());
  return frames[frame][pos];
}



// Set-Up Functions
sf::Event & EventStream::readyEvent(size_t frame, size_t pos)
{
  assert(frame < numOfFrames());
  assert(pos <= sizeOfFrame(frame));

  std::vector<sf::Event> & curFrame = frames[frame];
  std::vector<sf::Event>::iterator it = curFrame.begin();
  curFrame.emplace(it);
  return curFrame[pos];

  //frames[frame].emplace(frames[frame].begin()[pos]);
  //return frames[frame][pos];
}

size_t EventStream::numOfFrames () const
{
  return frames.size();
}

size_t EventStream::sizeOfFrame (size_t frameNum) const
{
  if (frames.size() <= frameNum)
    return 0;
  else
    return frames[frameNum].size();
}

void EventStream::addFrame ()
{
  frames.push_back(std::vector<sf::Event>());
}

// addEvent Set:
bool EventStream::addEvent (sf::Event const & event)
{
  return addEvent(event, frames.size() - 1);
}
bool EventStream::addEvent (sf::Event const & event, size_t frame)
{
  return addEvent(event, frame, sizeOfFrame(frame));
}
bool EventStream::addEvent (sf::Event const & event, size_t frame, size_t pos)
{
  assert(frame <= numOfFrames());
  assert(pos <= sizeOfFrame(frame));

  // Add an extra frame if required.
  if (numOfFrames() == frame)
    addFrame();

  // Add it the event.
  readyEvent(frame, pos) = event;
  return true;
}



// Even the testing tools must be tested.
// switch to REQUIRE( ... ) instead of REQUIRE(...)?
TEST_CASE("EventStream test", "[input]")
{
  sf::Event event;
  EventStream stream;

  // This is just a "null value", which is a Closed event.
  sf::Event closeEvent = {.type = sf::Event::Closed};

  SECTION("No events")
  {
    CHECK(1 == stream.numOfFrames());
    CHECK(0 == stream.sizeOfFrame(0));
    CHECK(0 == stream.sizeOfFrame(1));
    CHECK(0 == stream.sizeOfFrame(2));

    REQUIRE_FALSE(stream.pollEvent(event));
  }

  SECTION("Frame Adding")
  {
    stream.addFrame();
    REQUIRE(2 == stream.numOfFrames());

    stream.addEvent(closeEvent, 2);
    REQUIRE(3 == stream.numOfFrames());
  }

  SECTION("Event Adding Locations")
  {
    stream.addEvent(closeEvent);
    REQUIRE(1 == stream.sizeOfFrame(0));

    stream.addEvent(closeEvent, 1);
    REQUIRE(1 == stream.sizeOfFrame(1));

    sf::Event gFocusEvent = {.type = sf::Event::GainedFocus};
    sf::Event lFocusEvent = {.type = sf::Event::LostFocus};
    stream.addEvent(gFocusEvent);
    stream.addEvent(lFocusEvent, 1 , 0);
    REQUIRE(3 == stream.sizeOfFrame(1));
    CHECK(sf::Event::GainedFocus == stream.getEvent(1, 2).type);
    CHECK(sf::Event::Closed == stream.getEvent(1, 1).type);
    CHECK(sf::Event::LostFocus == stream.getEvent(1, 0).type);
  }

  SECTION("Steaming Events")
  {
    stream.addEvent(closeEvent);
    CHECK(stream.pollEvent(event));
    CHECK_FALSE(stream.pollEvent(event));

    CHECK_FALSE(stream.pollEvent(event));
    CHECK_FALSE(stream.pollEvent(event));

    stream.reset();
    stream.addEvent(closeEvent);
    stream.addEvent(closeEvent, 1);
    CHECK(stream.pollEvent(event));
    CHECK(stream.pollEvent(event));
    CHECK_FALSE(stream.pollEvent(event));
    CHECK(stream.pollEvent(event));
    CHECK_FALSE(stream.pollEvent(event));
  }
}
