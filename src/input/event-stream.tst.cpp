#include "event-stream.tst.hpp"
#include <catch.hpp>

// Implementation of the event stream testing tool.

#include <cassert>
#include <limits>



// Static Member Declaration
size_t const EventStream::FRAME_MAX = std::numeric_limits<size_t>::max() - 2;
size_t const EventStream::POS_MAX = std::numeric_limits<size_t>::max() - 2;
size_t const EventStream::FRAME_TOP = std::numeric_limits<size_t>::max();
size_t const EventStream::POS_TOP = std::numeric_limits<size_t>::max();



// Constructors and Deconstructor
EventStream::EventStream () :
  frames(), curFrame(0), curPos(0)
{
  // Just make sure that numeric_limits does not give garbage.
  assert(std::numeric_limits<size_t>::is_specialized);

  addFrame();
}

EventStream::~EventStream () {}



// Steam Functions
bool EventStream::pollEvent (sf::Event & event)
{
  if (frames.size() <= curFrame)
    return false;
  else if (frames[curFrame].size() <= curPos)
  {
    ++curFrame;
    curPos = 0;
    return false;
  }
  else
  {
    event = frames[curFrame][curPos++];
    return true;
  }
}

void EventStream::reset ()
{
  curFrame = 0;
  curPos = 0;
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

size_t EventStream::numOfFrames () const
{
  return frames.size();
}

size_t EventStream::sizeOfFrame (size_t frameNum) const
{
  assert(frameNum <= FRAME_MAX);
  if (frames.size() <= frameNum)
    return 0;
  else
    return frames[frameNum].size();
}



// Defualt Calculators
size_t EventStream::defaultFrame () const
{
  return frames.size() - 1;
}

size_t EventStream::defaultPos (size_t frame) const
{
  assert(frame <= FRAME_MAX);
  return sizeOfFrame(frame);
}



// Set-Up Functions
sf::Event & EventStream::loadEvent (size_t frame, size_t pos)
{
  assert(frame <= numOfFrames());
  assert(pos <= sizeOfFrame(frame));
  assert(sizeOfFrame(frame) < POS_MAX);

  // Add an extra frame if required.
  if (numOfFrames() == frame)
    addFrame();

  // Actually add the blank event.
  std::vector<sf::Event> & curFrame = frames[frame];
  std::vector<sf::Event>::iterator it = curFrame.begin();
  curFrame.emplace(it + pos);
  return curFrame[pos];
}

sf::Event & EventStream::readyEvent (size_t frame, size_t pos)
{
  // Check and load frame.
  assert(frame == FRAME_TOP || frame <= numOfFrames());
  if (FRAME_TOP == frame)
    frame = defaultFrame();

  // Check and load position within frame.
  assert(pos == POS_TOP || pos <= sizeOfFrame(frame));
  if (POS_TOP == pos)
    pos = defaultPos(frame);

  return loadEvent(frame, pos);
}

void EventStream::addFrame ()
{
  assert(frames.size() < FRAME_MAX);
  frames.push_back(std::vector<sf::Event>());
}

void EventStream::addEvent (sf::Event const & event, size_t frame, size_t pos)
{
  // Add it the event.
  readyEvent(frame, pos) = event;
}

void EventStream::addClosed (size_t frame, size_t pos)
{
  readyEvent(frame, pos).type = sf::Event::Closed;
}

void EventStream::addMouseLeftPress (int x, int y, size_t frame, size_t pos)
{
  sf::Event event = {.type = sf::Event::MouseButtonPressed};
  event.mouseButton.button = sf::Mouse::Button::Left;
  event.mouseButton.x = x;
  event.mouseButton.y = y;
  addEvent(event, frame, pos);
}



// Even the testing tools must be tested.
TEST_CASE("EventStream test", "[input][testing]")
{
  sf::Event event;
  EventStream stream;

  // This is just a "null value", which is a Closed event.
  sf::Event closeEvent = {.type = sf::Event::Closed};

  SECTION("No events")
  {
    CHECK( 1 == stream.numOfFrames() );
    CHECK( 0 == stream.sizeOfFrame(0) );
    CHECK( 0 == stream.sizeOfFrame(1) );
    CHECK( 0 == stream.sizeOfFrame(2) );

    REQUIRE_FALSE( stream.pollEvent(event) );
  }

  SECTION("Frame Adding")
  {
    stream.addFrame();
    REQUIRE( 2 == stream.numOfFrames() );

    stream.addEvent(closeEvent, 2);
    REQUIRE( 3 == stream.numOfFrames() );
  }

  SECTION("Event Adding Locations")
  {
    stream.addEvent(closeEvent);
    REQUIRE( 1 == stream.sizeOfFrame(0) );

    stream.addEvent(closeEvent, 1);
    REQUIRE( 1 == stream.sizeOfFrame(1) );

    sf::Event gFocusEvent = {.type = sf::Event::GainedFocus};
    sf::Event lFocusEvent = {.type = sf::Event::LostFocus};
    stream.addEvent(gFocusEvent);
    stream.addEvent(lFocusEvent, 1 , 0);
    REQUIRE( 3 == stream.sizeOfFrame(1) );
    CHECK( sf::Event::GainedFocus == stream.getEvent(1, 2).type );
    CHECK( sf::Event::Closed == stream.getEvent(1, 1).type );
    CHECK( sf::Event::LostFocus == stream.getEvent(1, 0).type );

    stream.addEvent(gFocusEvent, 1 , 1);
    CHECK( sf::Event::GainedFocus == stream.getEvent(1, 1).type );
    CHECK( sf::Event::LostFocus == stream.getEvent(1, 0).type );
  }

  SECTION("Steaming Events")
  {
    stream.addEvent(closeEvent);
    CHECK( stream.pollEvent(event) );
    CHECK_FALSE( stream.pollEvent(event) );

    CHECK_FALSE( stream.pollEvent(event) );
    CHECK_FALSE( stream.pollEvent(event) );

    stream.reset();
    stream.addEvent(closeEvent);
    stream.addEvent(closeEvent, 1);
    CHECK( stream.pollEvent(event) );
    CHECK( stream.pollEvent(event) );
    CHECK_FALSE( stream.pollEvent(event) );
    CHECK( stream.pollEvent(event) );
    CHECK_FALSE( stream.pollEvent(event) );
  }

  SECTION("Adding Event Types")
  {
    SECTION("Check addClosed")
    {
      stream.addClosed();
      stream.pollEvent(event);
      REQUIRE( sf::Event::Closed == event.type );
    }

    SECTION("Check addMouseLeftPress")
    {
      stream.addMouseLeftPress(10, 20);
      stream.addMouseLeftPress(25, 15);
      stream.pollEvent(event);
      REQUIRE( sf::Event::MouseButtonPressed == event.type );
      CHECK( sf::Mouse::Button::Left == event.mouseButton.button );
      CHECK( 10 == event.mouseButton.x );
      CHECK( 20 == event.mouseButton.y );
      stream.pollEvent(event);
      REQUIRE( sf::Event::MouseButtonPressed == event.type );
      CHECK( sf::Mouse::Button::Left == event.mouseButton.button );
      CHECK( 25 == event.mouseButton.x );
      CHECK( 15 == event.mouseButton.y );
    }
  }
}
