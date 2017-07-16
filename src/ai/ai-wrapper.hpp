#ifndef AI_WRAPPER_HPP
#define AI_WRAPPER_HPP

/* This is for the transition, to see how the inheirtance based system
 * compares to the container based one. It is a component, but all it does
 * is run call backs on the container, which should
 */

#include "ai-component.hpp"
class PlaneObject;



class AiWrapper
{
  PlaneObject * cashed;

public:
  AiWrapper() : cashed(nullptr) {}
  virtual ~AiWrapper() {}

  void init (GameObject & container);
  /* The inheirited object is assumed to do everything it need to.
   * Effect: Updates cashed.
   */

  bool handleInput (GameObject & container, InputEvent const & ievent);
  /* Call back to innerHandleInput.
   * Effect: Updates cashed and effects of innerHandleInput.
   */

  void update (GameObject & container, sf::Time const & deltaT);
  /* Call back to innerUpdateAi.
   * Effect: Updates cashed and effects of innerUpdateAi.
   */

  void handleCollision (GameObject & container, GameObjectPtr & ptr);
  /* Call back to innerHandleCollision.
   * Effect: Updates cashed and effects of innerHandleCollision.
   */
};

#endif//AI_WRAPPER_HPP
