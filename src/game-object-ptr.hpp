#ifndef GAME_OBJECT_PTR_HPP
#define GAME_OBJECT_PTR_HPP

/* A smart pointer to a game object. Goes NULL if the object it points to is
 * destroyed. It is rather coupled with the GameObject itself.
 */

class NullingTarget;
class GameObject;

/* Some additions that might let me move all the pointer stuff into one class.
public:
  typedef std::vector<GameObject*> ptr_container;
  typedef typename ptr_container::iterator ptr_iterator;
  static void preDistroy(ptr_container & );
  static void move(... ??? ...);
  static void merge(... ??? ...);

Essentually, move all the code from the other classes that work with these
pointers into this class,
*/



class GameObjectPtr
{
private:
  GameObject * ptr;
  friend class NullingTarget;

protected:
  void assignPtr(NullingTarget *);

  void unregester ();
  /* Internal function for setting the pointer to point at nothing.
   * If the pointer already points at nothing than nothing is done.
   */

  void regesterTo (GameObject *);
  /* Internal function for setting the pointer to point at something.
   * If the pointer already points at something it is first unregestered.
   */

  void takeRegester (GameObjectPtr && other);
  /* takeRegester(other)
   * Take the other GameObjectPtr's pointer, nulling it if it isn't already
   * null.
   */

public:
  GameObjectPtr ();
  /* Default GameObjectPtr constructor, points at nothing.
   */

  GameObjectPtr (GameObjectPtr const & other);
  GameObjectPtr (GameObjectPtr && other);
  /* Copy/Move constructor, new pointer is a copy of the other pointer.
   * Params: A reference to another GameObjectPtr.
   */

  GameObjectPtr (GameObject & object);
  /* Target constructor, new pointer points at the given GameObject.
   * Params:
   */

  virtual ~GameObjectPtr ();

  GameObject & operator* ();
  GameObject * operator-> ();
  /* Deferencing operators.
   */

  bool nonNull () const;
  operator bool () const;
  /* Check the status of the pointer.
   * Return: True if this points at a GameObject, false otherwise.
   */

  bool isNull () const;
  /* Check the status of the pointer.
   * Return: True if this does not point at a GameObject, false otherwise.
   */

  void setNull ();
  /* Set the GameObjectPtr to point at nothing.
   * Effect: Changes what this pointer is pointing at.
   */

  void setTo (GameObject & object);
  /* Set the GameObjectPtr to point at object.
   * Params: A reference/pointer to a GameObject.
   * Effect: Changes what this pointer is pointing at.
   */

  GameObjectPtr & operator= (GameObjectPtr const & other);
  GameObjectPtr & operator= (GameObjectPtr && other);
  /* Copy/Move assignment, this pointer points
   * Params: A reference to another GameObjectPtr.
   * Effect: This pointer now points at the other pointer.
   * Return: Mutable refence to this.
   */

  bool operator== (GameObjectPtr const & other) const;
  bool operator!= (GameObjectPtr const & other) const;
  bool operator>  (GameObjectPtr const & other) const;
  bool operator<  (GameObjectPtr const & other) const;
  bool operator>= (GameObjectPtr const & other) const;
  bool operator<= (GameObjectPtr const & other) const;
  /* Comparison operators.
   * Params: A constant reference to a different game-object ptr.
   * Return: True if the given comparison is true. Ordering uses
   *   the object's address in memory.
   */

  friend class GameObject;
};

#endif//GAME_OBJECT_PTR_HPP
