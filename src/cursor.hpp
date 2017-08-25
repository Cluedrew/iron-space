#ifndef CURSOR_HPP
#define CURSOR_HPP

/* When the mouse is active and focused on the screen, we can replace the
 * system cursor with a custom one.
 *
 * Note: I actually do not expect this to make it very far. But it lets me
 * fiddle with mouse control to see how it works.
 */

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
namespace sf { class RenderTarget; class RenderStates; class Window; }



class Cursor : public sf::Drawable
{
public:
  sf::Vector2<int> pos;
private:
  sf::ConvexShape icon;
  bool override;

  void makeIcon ();
  void draw(sf::RenderTarget & target, sf::RenderStates states) const;

protected:
public:
  Cursor() : pos(0, 0), override(false) { makeIcon(); }
  /* Create a new cursor.
   */

  void setCursorOverride (sf::Window & target, bool active = true);
  /* Update the internal override.
   */
};

#endif//CURSOR_HPP
