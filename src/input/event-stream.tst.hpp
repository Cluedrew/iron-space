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

/* The EventStream acts as an alternate source of events for the EventHandler
 * (or GenEventHandler). Instead of looking for actual input it simply gives
 * out the events that have been loaded into it already. This allows for both
 * predictable and automated input, which is used in testing.
 *
 * Normal/Basic usage of this class should just be a bunch of calls to addX
 * methods with some addFrame calls mixed in to mimic events over time. Each
 * frame will repersent the events polled in one iteration of the main loop.
 * You may keep polling after all the frames have been used, but no more
 * events will be generated.
 *
 * The class uses a lot of asserts because it is used in testing where knowing
 * something went wrong right away is more important than any error recovery.
 */



class EventStream
{
private:
  std::vector<std::vector<sf::Event> > frames;
  size_t curFrame;
  size_t curPos;

  size_t defaultFrame () const;
  /* Get the default frame for the stream in its current state.
   * Return: Index of last frame.
   */
  size_t defaultPos (size_t frame) const;
  /* Get the default position of the given frame.
   * Params: The index of a frame.
   * Return: The index of the end of the frame.
   */

  sf::Event & loadEvent (size_t frame, size_t pos);
  /* Create space for an event at a given location in the stream and return
   *   a reference to it. (Which will be valid for a moment.)
   * Params: The frame to add the event to [0..numOfFrames] and the position
   *   in that frame to inseart the event at [0..sizeOfFrame(frame)].
   * Effect: Adds an uninitialized event to the stream.
   * Return: A reference to the new event. (May not stay valid for long)
   */

  sf::Event & readyEvent (size_t frame, size_t pos);
  /* A wrapper for loadEvent that translates FRAME_TOP and POS_TOP to the
   *   approprate values depending on the current state of the stream.
   * Params: frame=[0..numOfFrames]|FRAME_TOP
   *   pos=[0..sizeOfFrame(frame)]|POS_TOP
   * Effect: Adds an uninitialized event to the stream.
   * Return: A reference to the new event. (May not stay valid for long)
   */

protected:
public:
  // The maximum number of frames in the stream. frame=[0..FRAME_MAX]
  static size_t const FRAME_MAX;
  // The maximum number of events in a frame. pos=[0..POS_MAX]
  static size_t const POS_MAX;

  // The defualts used for adding events if no value is given.
  // The defualt frame is the last frame that currently exists.
  static size_t const FRAME_TOP;
  // The defualt position in frame is at the end of the frame.
  static size_t const POS_TOP;

  EventStream ();
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
   * Effect: New frame is added at the end of frames.
   */

  void addEvent (sf::Event const & event, size_t frame = FRAME_TOP,
                 size_t pos = POS_TOP);
  /* Add a new event to the stream.
   * Params: A reference to the event to copy in. Optionally the frame to
   *   put the event in (last frame is assumed) and the pos in the frame to
   *   put the event at (end of frame is assumed).
   * Effect: Add a new event at the given spot in the stream.
   */

  void addClosed (size_t frame = FRAME_TOP, size_t pos = POS_TOP);
  /* Add a new Closed event to the stream.
   * Params: Optional frame and pos parameters as in addEvent.
   * Effect: Add a new Closed event at the given spot in the stream.
   */

  void addMouseLeftPress (int x, int y,
      size_t frame = FRAME_TOP, size_t pos = POS_TOP);
  /* Add a new left MouseButtonPressed event to the stream.
   * Params: The x & y location of the mouse click.
   *   Optional frame and pos parameters as in addEvent.
   * Effect: Add a new MouseButtonPressed event to the stream, its button
   *   field will be set to Mouse::Button::Left.
   */
};

#endif//EVENT_STREAM_TST_HPP
