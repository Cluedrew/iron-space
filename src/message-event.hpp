#ifndef MESSAGE_EVENT_HPP
#define MESSAGE_EVENT_HPP

/* Base class to the MessageEvent class hierarcy.
 *
 * All child classes of MessageEvent should re-implement sendTo to that the
 * AIComponent can catch the different types of messages in different
 * functions. More on that in the AIComponent.
 */



class
{
private:
protected:
public:
  virtual ~MessageEvent () =0;

  virtual void sendTo (AIComponent & ai);
  /* Dynamically sents the message to the AIComponent.
   * Params: Mutable reference to AIComponent to send the message to.
   * Effect: Varies with AIComponent (plus the override).
   *
   * Important: Remember to override it.
   */
};
#endif//MESSAGE_EVENT_HPP
