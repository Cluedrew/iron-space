#ifndef MESSAGE_HPP
#define MESSAGE_HPP

/* Base class to the Message class hierarcy, which repersents messages
 * between GameObjects.
 *
 * All child classes of Message should re-implement sendMessage to that the
 * AIComponent can catch the different types of messages in different
 * functions. More on that in the AIComponent.
 */

class AIComponent;
class GameObject;



class Message
{
private:
protected:
public:
  virtual ~Message () =0;

  virtual void sendMessage (AIComponent & ai) =0;
  /* Dynamically sents the message to the AIComponent.
   * Params: Mutable reference to AIComponent to send the message to.
   * Effect: Varies with AIComponent (plus the override).
   *
   * Important: Remember to override it.
   * vritual void sendMessage (AIComponent & ai)
   * {
   *   ai.handleMessage(*this);
   * }
   */

  // Extra functions for sending the initial message out?.
  //void sendMessage (GameObject & obj);
  //void sendMessage (GameObjectPtr & ptr);
};

#endif//MESSAGE_HPP
