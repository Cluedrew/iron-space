#ifndef INTERFACE_HPP
#define INTERFACE_HPP

/* The interface is part of the input handling system. It was one class but
 * then I realized that there where not actually part of the same thing.
 */

#include <vector>



enum MappableButton
/* An enumeration of all virtual buttons that the physical keys can be mapped
 * to. The list is static, but it isn't set (not yet at least), as it is
 * really the list of controls. This is a bit more dependant on the game
 * design than perhaps the base engine should be, but I don't yet have a
 * better solution.
 */
{
  Pause,
  Up,
  Right,
  Down,
  Left,

  Nothing,
  // Special: Shows no mapping has been made.
  End
  // Special: The number of buttons.
};



typedef MappableButton ControlScheme[sf::Keyboard::Key::KeyCount];
/* (May create a class with operator[] and operator= instead.)
 * Creates a mapping from every input key to a virtual button. It is also a
 * dynamic mapping so I can add custimization to the control scheme.
 */



//typedef std::vector<CountPtr<GameObject> > Selection;
typedef std::vector<GameObjectPtr> Selection;
/* A selection is just a group of pointers to objects. The reason it is here
 * is that we need a way to remember Mouse Focus (And Keyboard Focus) in the
 * interface if we want to dispatch commands to them. If not in the top level,
 * than at the WorldState level.
 * Hooks in the game objects might be helpful, but I'm not sure if they will
 * be worth it. (onSelect, onUnselect, isSelected)
 */
//template<typename T>
//using Selection<T> = std::vector<CountPtr<T> >;
//  A slightly more generic version of the type.



class Cursor : public sf::Drawable
/* Repersents the mouse on screen.
 *
 * It might be usable for more thematic repersentations of the mouse, or at
 * the very least, selection areas and click-&-drag lines. It will probably be
 * a base class.
 */
{
private:
  virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

protected:
public:
  Cursor ();

  virtual ~Cursor ();

  void update ();
  /* Call to update the Cursor's image.
   *
   * Shouldn't need to pass in any data, might need a time but all the mouse
   * information is available in a static class.
   */
};

#endif//INTERFACE_HPP
