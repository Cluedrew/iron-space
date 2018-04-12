/* So I had almost forgot why I dropped this for over a month. And it is
 * because I have to find solution to the input problem and how that effects
 * everything else.
 */


/* Plan 0: Almost forgot it: Adjust the current system.
 *
 * Instead of doing some grand redesign, keep the basic idea of input (event)
 * distribution but just try and to refine it a bit. Create some shared
 * functions to prevent re-writing.
 */
class GameObject
{
public:
  bool receiveInput (InputEvent const &);
  /* A splitter function, here or above, is used to deside which checks to
   * use and which functions to call.
   */

  virtual void receivePoint (int const & x, int const & y);
  /* This is one of the smaller functions that might exist at the bottom.
   * It is called only when a point event is recived for this GameObject.
   */
};


/* Plan 1: State-Based Input Observer
 *
 * Requires that many GameObjects and hence perhaps all, know what state they
 * are in at all times. Beside that it is the simplest solution, because that
 * packs a lot of information and overhead (especially with types of observers
 * to choose what to listen for) into the solution.
 *
 * Still even an extra pointer on EVERY GameObject seems a bit much, plus the
 * changes to make sure that is tracked and shared.
 */
class GameObject
{
  WorldState & within;
protected:
  void listen();
  void dontListen();
public:
  bool receiveInput
};

class WorldState
{
  std::vector<Listener> selectionListeners;
public:
  void addSelectionListener(Listener);
  void removeSelectionListener(Listener);
};


/* Plan 2: Global Input Listener
 *
 * Basic idea, have a single static interface for incoming input and any one
 * interested can listen a particular type of input. Main issues come around
 * state changes, because most listeners will have to stop listening then.
 * The addition of some "onPause", "onUnpause" handlers, or a "onStateChange"
 * if I can assign create a set of states a GameObject could be in.
 */
class InputHandler
{
  // Might just store the FatFunctions directly.
  std::vector<Listener<...>> selectionListeners;
public:
  void addSelectionListener(Listener);
  void removeSelectionListener(Listener);
};

template <typename ReturnT, typename... Args>
class Listener
{
  FatFunction<ReturnT, Args> toCall;
public:
  // Forward most of the FatFunction interface, but add calls to
  // add/removeSelectionListener as needed.

  virtual ~Listener ()
  {
    if (toCall) removeSelectionListener(this/toCall);
  }
};


/* Plan 3: Eliminate Generic Input Events
 *
 * Probably the most drastic change, but if I can create a list of the types
 * of things GameObjects might respond to, I can create an interface for each
 * one of those. It would be a massive conversion and currently, I don't have
 * that list, I could create a short form and expand it as nessasary.
 *
 * A more important consern, I have to implement some variant of another plan
 * for the each system. Which gets back to this with just a bit more focus.
 */


/* Note on Selection:
 * The ability to have a GameObject "selected" is powerful and quite generic
 * for this game, but maybe not overall. It serves the original purpose on
 * units, but it could be repurposed for GUI selection and similar.
 */
