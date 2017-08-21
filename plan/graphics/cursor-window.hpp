#ifndef CURSOR_WINDOW_HPP
#define CURSOR_WINDOW_HPP

/* A modified render window that tracks and draws the cursor.
 *
 * It has a cursor field that is used to repersent the cursor, if that is
 * set and the cursor is in range (over the screen when the screen is in
 * focus).
 *
 * This is one of my two solutions to creating a global cursor, the other is
 * to track window from the cursor (a custom drawable class), one should
 * probably track the other, otherwise we have to connect them manually every
 * time.
 */

#include <SFML/Graphics/RenderWindow.hpp>



class CursorWindow : public RenderWindow
{
private:
protected:
public:
  sf::Drawable const * cursor;

  // Various forwarding constructors.

  void drawCursor()
  {
    if (cursor && hasFocus())
    {
      sf::Vector2i mousePos(sf::Mouse::getPosition(window));
      sf::Vector2u winSize(getSize());
      if (0 <= mousePos.x && 0 <= mousePos.y &&
          (unsigned)mousePos.x < winSize.x && (unsigned)mousePos.y < winSize.y)
      {
        setMouseCursorVisible(false);
        draw(*cursor);
        return;
      }
    }
    setMouseCursorVisible(true);
  }
};

#endif//CURSOR_WINDOW_HPP
