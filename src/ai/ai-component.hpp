#ifndef AI_COMPONENT_HPP
#define AI_COMPONENT_HPP

/* AI Component: Handles most of the thinking for its GameObject.
 */



class AIComponent
{
private:
protected:
public:
  AIComponent ();
  virtual ~AIComponent () =0;

  virtual void update (GameObject & obj, sf::Time const & dt);
  /* Move the object forward in time.
   * Params: A reference to the GameObject this is attached to and the
   *   amount of time that has passed.
   * Effect: Default is nothing, may be overridden.
   */

  virtual void handleInput (InputEvent const & iEvent);
  /* Handle a piece of input handed to the GameObject.
   * Params: Reference to the input being handled.
   * Effect: Default is nothing, may be overridden.
   */

  virtual void handleMessage (Message & msg);
  /* Handle a message from another GameObject.
   * Params: Mutable reference to the Message.
   * Effect: Default is nothing, may be overridden.
   *
   * Add overloads for sub-classes of Message, so that sub-classes of
   * AIComponent can selectively overide for different message types.
   */

  virtual void handleCollision (GameObjectPtr & ptr);
  /* Handle a collision with another GameObject.
   * Params: Mutable reference to a GameObjectPtr +.
   * Effect: Default is nothing, may be overridden.
   *
   * + If we can garenty the timing of deletes than this could just be a
   *   reference to the GameObject itself.
   */
};

#endif//AI_COMPONENT_HPP
