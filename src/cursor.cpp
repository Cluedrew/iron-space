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
  sf::Transform localTransform;
  localTransform.translate(sf::Vector2f(pos));
  states.transform *= localTransform;
  target.draw(icon, states);
}
