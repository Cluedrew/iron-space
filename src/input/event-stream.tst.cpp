/* A testing tool, the stream may be filled with sf::Event objects and then
 * passes them to the whatever calls pollEvent.
 */

#include <vector>
#include <SFML/Window/Event.hpp>



class EventStream
{
private:
  std::vector<std::vector<sf::Event> > frames;
  unsigned int frame;
  unsigned int fpos;
protected:
public:
  EventStream();
  /* Construct a new EventStream with a single empty frame.
   */

  virtual ~EventStream ();

  bool pollEvent(sf::Event & event);
  /* Return the next event if there is one in the current frame and return
   *   true. Otherwise return false and the next call will start returning
   *   events from the next frame. If we have finished the last frame false
   *   will always be returned.
   * Params:
   * Effect:
   * Return:
   */

  void reset();
  /* If you ever want to re-use the stream, call reset and it will repeat
   *   the pattern of events.
   * Effect:
   */

  void addFrame();
  /* Add a new empty frame to the stream.
   * Effect: New frame is added to frames.
   */

  bool addEvent(sf::Event const & event);
  //, size_t frame = <last-frame>, size_t pos = <last-pos-in frame>);
  /* Add a new event to the stream.
   * Params: A reference to the event to copy in.
   * Effect:
   * Return: True if event was added, false on error.
   */
};



// Constructors and Deconstructor
EventStream::EventStream() :
  frames(), frame(0), fpos(0)
{
  addFrame();
}

EventStream::~EventStream () {}



// Steam Functions
bool EventStream::pollEvent(sf::Event & event)
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

void EventStream::reset()
{
  frame = 0;
  fpos = 0;
}



// Set-Up Functions
void EventStream::addFrame()
{
  frames.push_back(std::vector<sf::Event>());
}
