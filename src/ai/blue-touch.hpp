#ifndef BLUE_TOUCH_HPP
#define BLUE_TOUCH_HPP

/* Blue Touch is so called because it turns blue when anything touches it.
 * It must be hooked up beside a CircleGraphics.
 */

class GameObject;
#include "ai-component.hpp"



class BlueTouch : public AiComponent
{
private:
  int x;
  int y;

protected:
public:
  BlueTouch (int x, int y);

  virtual ~BlueTouch ();

  void init (GameObject & container);
  // Changes the GameObjects position.

  bool handleInput (GameObject & container, InputEvent const & ievent);
  // No input is handled.

  void update (GameObject & container, sf::Time const & deltaT);
  // Colour change when approprate.
};

#endif//BLUE_TOUCH_HPP
