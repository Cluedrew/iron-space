#ifndef BLUE_TOUCH_HPP
#define BLUE_TOUCH_HPP

/* Blue Touch is so called because it turns blue when anything touches it,
 * playing a sound effect. It must be hooked up beside a CircleGraphics.
 */

class GameObject;
class GameObjectPtr;
#include "ai-component.hpp"
#include <SFML/Audio/Sound.hpp>
#include "audio/sound-effect.hpp"



class BlueTouch : public AiComponent
{
private:
  int x;
  int y;
  SoundEffect sound;
  char contact;

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

  void handleCollision (GameObject & container, GameObjectPtr & ptr);
  // Check to see if the color should be changed.
};

#endif//BLUE_TOUCH_HPP
