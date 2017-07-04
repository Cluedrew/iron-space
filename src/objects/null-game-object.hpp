#ifndef NULL_GAME_OBJECT_HPP
#define NULL_GAME_OBJECT_HPP

/* The NullGameObject is implemented with null components (which implement
 * no-ops, or as close as we can get, in every case).
 */

#include "../object/game-object.hpp"



class NullGameObject : public GameObject
{
private:
protected:
public:
  NullGameObject ();
  /* Create a NullGameObject.
   */
};

#endif//NULL_GAME_OBJECT_HPP
