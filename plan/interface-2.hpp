/* This is the interface layer. It is responsible for catching and dispatching
 * and input from the user. It abstracts those events and passes them to the
 * inner layers.
 *
 * It may also draw the tool types and graphical events from the cursur as it
 * should be the only part of the system that actually knows where that is.
 *
 * I just realized I have a README for this... then again maybe I should
 * just focus on getting the game working and not some grand plan.
 * [[
 * This part my _experamental_ model for repersenting the engine. It divides
 * the system into layers. Control goes down through the layers and the
 * responces come back up.
 * + Interface (this one) is closest to the user and acts as an event
 *   dispatcher to the other layers. It has no "place" simple is and wraps
 *   around the rest of the program.
 * + GUI is responsible for widgets, any desplay or input element locked to
 *   the screen.
 * + World is the game world. It is a container for GameObjects that exist in
 *   the game's space.
 *
 * This flow is mostly conserned with control and input. Output can really
 * come from every layer because each "thing" in the lower layers is tied to
 * how it is repersented. There will be some guildlines for that as well but
 * I haven't worked those out.
 * ]]
 */

#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <SFML/Graphics.hpp>
//#include <SFML/Window/Window.hpp>
namespace sf
{
  class Window;
}

class Interface : public sf::Drawable
{
private:
  /* Draws curser. to the screen.
   */
  virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;

protected:
public:
  Interface ();

  virtual ~Interface ();

  /* Polls all input from the window and distributs it.
   * Params: A mutable reference to a window to poll from.
   * Effect: Many, dependant on events.
   * Return: False if a QUIT event was recived, otherwise true.
   */
  bool pollInput (sf::Window & window);


};

#endif//INTERFACE_HPP
