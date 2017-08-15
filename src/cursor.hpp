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
namespace sf { class RenderTarget; class RenderStates; }



class Cursor : public sf::Drawable
{
private:
  sf::Vector2<int> pos;
  sf::ConvexShape icon;

  void makeIcon ();
  void draw(sf::RenderTarget & target, sf::RenderStates states) const;

protected:
public:
  Cursor() : pos(0, 0) { makeIcon(); }
  Cursor(sf::Vector2<int> pos) : pos(pos) { makeIcon(); }
  Cursor(int x, int y) : pos(x, y) { makeIcon(); }
  /* Create a new cursor.
   * Params: The position to create the cursor at.
   */
};

#endif//CURSOR_HPP
