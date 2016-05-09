#ifndef COLLISION_HPP
#define COLLISION_HPP

/* Holds information about a collision between two objects.
 *
 * OK, what information do I actually need?
 * First each GameObject needs to know what the collision was betten. Itself
 *   can be assumed so it needs a pointer/reference to the other.
 * Does it need a start->continue->end qualifier? I know they are used but
 *   is there any use for it here?
 * It does assume that the GameObject will be in existance for its entire
 *   lifetime.
 */



enum class CollisionType : char
{
  Start,
  Continue,
  Finished
};


class Collision
{
private:
  GameObjectPtr objectA;
  GameObjectPtr objectB;
  GameObject obj;

protected:
public:
  Collision ();
  virtual ~Collision ();

  static void issue (GameObject & objA, GameObject & objB)
  /* Inform two objects that they have collided.
   * Params: References to the two GameObjects that have collided.
   * Effect: Varies with GameObject's handleCollision effects.
   */
  {
    objA.handleCollision(objB);
    objB.handleCollision(objA);
  }

  GameObject & with ()
  /* Get what this object collided with.
   * Return: A reference to the GameObject this one collided with.
   */
  { return obj; }
};

#endif//COLLISION_HPP
