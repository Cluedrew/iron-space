#ifndef NULL_AI_HPP
#define NULL_AI_HPP

/* The AI that does nothing.
 *
 * I actually made this as an example.
 */

#include "ai-component.hpp"



class NullAI : public AIComponent
{
private:
protected:
public:
  virtual ~NullAI () {}

  void update (GameObject & obj, sf::Time const & dt) {}

  void handleInput (InputEvent) {}
  void handleMessage (Message) {}
  void handleCollision (Collision) {}
};

#endif//NULL_AI_HPP
