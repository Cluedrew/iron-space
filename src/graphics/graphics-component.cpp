#include "graphics-component.hpp"

#include <SFML/Graphics.hpp>



GraphicsComponent::GraphicsComponent () :
  circle(25)
{
  circle.setOrigin(25, 25);
}

GraphicsComponent::~GraphicsComponent ()
{}

void GraphicsComponent::draw
    (sf::RenderTarget & target, sf::RenderStates states) const
{
  target.draw(circle, states);
}
