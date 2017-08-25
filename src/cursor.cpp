#include "cursor.hpp"

// The cursor draws an X

#include <SFML/Graphics.hpp>



void Cursor::makeIcon ()
{
  icon.setPointCount(12);
  icon.setPoint(0, sf::Vector2f(2, 2));
  icon.setPoint(1, sf::Vector2f(2, 10));
  icon.setPoint(2, sf::Vector2f(-2, 10));
  icon.setPoint(3, sf::Vector2f(-2, 2));
  icon.setPoint(4, sf::Vector2f(-10, 2));
  icon.setPoint(5, sf::Vector2f(-10, -2));
  icon.setPoint(6, sf::Vector2f(-2, -2));
  icon.setPoint(7, sf::Vector2f(-2, -10));
  icon.setPoint(8, sf::Vector2f(2, -10));
  icon.setPoint(9, sf::Vector2f(2, -2));
  icon.setPoint(10, sf::Vector2f(10, -2));
  icon.setPoint(11, sf::Vector2f(10, 2));
}

void Cursor::draw (sf::RenderTarget & target, sf::RenderStates states) const
{
  if (override)
  {
    sf::Transform localTransform;
    localTransform.translate(sf::Vector2f(pos));
    states.transform *= localTransform;
    target.draw(icon, states);
  }
}

bool isOverWindow (sf::Window & window)
{
  sf::Vector2i mousePos(sf::Mouse::getPosition(window));
  sf::Vector2u winSize(window.getSize());
  return (0 <= mousePos.x && 0 <= mousePos.y &&
          (unsigned)mousePos.x < winSize.x &&
          (unsigned)mousePos.y < winSize.y);
}

void Cursor::setCursorOverride (sf::Window & target, bool active)
{
  bool overWindow;

  if (active && target.hasFocus() && (overWindow = isOverWindow(target)) )
  {
    if (!override)
    {
      override = true;
      target.setMouseCursorVisible(false);
    }
  }
  else
  {
    if (override)
    {
      override = false;
      target.setMouseCursorVisible(true);
    }
  }
}
