#ifndef EVENT_STREAM_TST_HPP
#define EVENT_STREAM_TST_HPP

/* A testing tool, the stream may be filled with sf::Event objects and then
 * passes them to the whatever calls pollEvent. pollEvent will break up the
 * streams to act.
 *
 * I use more asserts and sudden falure code here because it is for testing
 * and so it needs to be very obvious that it is not working. Plus recovery
 * is not an issue.
 */

#include <vector>
#include <SFML/Window/Event.hpp>



class EventStream
{
private:
  std::vector<std::vector<sf::Event> > frames;
  size_t frame;
  size_t fpos;

  sf::Event & readyEvent(size_t frame, size_t pos);
  /* Create space for an event at a given location in the stream and return
   * a reference to it. (Which will be valid for a moment.)
   * Params: The frame to add the event to [0..numOfFrames] and the position
   *   in that frame to inseart the event at [0..sizeOfFrame(frame)].
   * Effect:
   * Return:
   */

protected:
public:
  EventStream();
  /* Construct a new EventStream with a single empty frame.
   */

  virtual ~EventStream ();

  bool pollEvent (sf::Event & event);
  /* Return the next event if there is one in the current frame and return
   *   true. Otherwise return false and the next call will start returning
   *   events from the next frame. If we have finished the last frame false
   *   will always be returned.
   * Params: A mutable reference to the space to store the event in.
   * Effect: May mutate event and advance the position in the stream.
   * Return: True if event was modified, false otherwise.
   */

  void reset ();
  /* If you ever want to re-use the stream, call reset and it will repeat
   *   the pattern of events.
   * Effect: Sets the position in the stream to the beginning.
   */

  sf::Event & getEvent (size_t frame, size_t pos);
  sf::Event const & getEvent (size_t frame, size_t pos) const;
  /* Get an event at a given position
   * Params: The frame and position in frame to get the event from.
   * Return: A reference to the given event.
   * Throws: No-Throw, instead of std::out_of_range it aborts.
   */

  size_t numOfFrames () const;
  /* Get the number of frames in the stream.
   * Return: The number initialized frames of frames.
   */

  size_t sizeOfFrame (size_t frameNum) const;
  /* Get the size of a particular frame.
   * Params: The index of the frame to check.
   * Return: Size of the given frame.
   *   (Frames off the end are considered empty)
   */

  void addFrame ();
  /* Add a new empty frame to the stream.
   * Effect: New frame is added to frames.
   */

  bool addEvent (sf::Event const & event);
  bool addEvent (sf::Event const & event, size_t frame);
  bool addEvent (sf::Event const & event, size_t frame, size_t pos);
  /* Add a new event to the stream.
   * Params: A reference to the event to copy in.
   * Effect:
   * Return: True if event was added, false on error.
   */

  //bool addClosed ();
};

#endif//EVENT_STREAM_TST_HPP
