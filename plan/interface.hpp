#ifndef INTERFACE_HPP
#define INTERFACE_HPP

/* Maybe I should change the name, because this really isn't the interface
 * itself, just the an add-on that maintains some state for it.
 */

#include <vector>



class Interface
{
private:
  std::vector<GameObjectPtr> selected;

protected:
public:
  Interface ();
  virtual ~Interface ();

  void handleUnMappedInput (sf::Event const &);
  /* Map and send out an Input Event.
   * Params: A reference to the input event.
   * Effect: Varies with input.
   */

  void foreachSelected (void (*)(GameObjectPtr));
  /* Call a void function on each selected object.
   * Params: A function that accepts a GameObjectPtr and returns void.
   * Effect: Combined effect of all function calls.
   *
   * Maybe something more specialized (messageSelected) would be better.
   */
};

#endif//INTERFACE_HPP
