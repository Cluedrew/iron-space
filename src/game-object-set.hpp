#ifndef GAME_OBJECT_SET_HPP
#define GAME_OBJECT_SET_HPP

/* Holds a set of GameObjects.
 *
 * The main reason I want this to exist is so I can time when GameObjects are
 * deleted. They can regester themselves to be destroyed and then are cleared
 * out once per frame. Probably right before draw, after the updates are done
 * but before there still being around can be noticed.
 */

class GameObjectSet
{
private:
protected:
public:
  virtual ~GameObjectSet ();
};

#endif//GAME_OBJECT_SET_HPP
