#include "text-graphics.hpp"

// Implementation of TextGraphics.

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Color.hpp>



TextGraphics::TextGraphics (std::string const & font_,
                            std::string const & text_,
                            Alignment2D alignment) :
  sf::Text(), font(FontLibrary::getFont(font_))
{
  setString(text_);
  setFont(*font);
  // set{Fill,Outline}Color become prefered as of SFML 2.4.1.
  setColor(sf::Color::Blue);
}

TextGraphics::~TextGraphics ()
{}

void TextGraphics::draw (sf::RenderTarget & target,
                         sf::RenderStates states) const
{
  // TODO: Can this ever fail? if not a faster cast should be used.
  target.draw(dynamic_cast<const sf::Text &>(*this), states);
}

void TextGraphics::setAlignment(Alignment2D alignment)
{
  sf::FloatRect bounds = getLocalBounds();
  float xOrigin;
  float yOrigin;
  switch(verticalAlignmentComponent(alignment))
  {
  case VerticalAlignment::Top:
    yOrigin = 0;
    break;
  case VerticalAlignment::Middle:
    yOrigin = bounds.height / 2;
    break;
  case VerticalAlignment::Bottom:
    yOrigin = bounds.height;
    break;
  }
  switch(horizontalAlignmentComponent(alignment))
  {
  case HorizontalAlignment::Left:
     xOrigin = 0;
     break;
  case HorizontalAlignment::Center:
     xOrigin = bounds.width / 2;
     break;
  case HorizontalAlignment::Right:
     xOrigin = bounds.width;
     break;
  }
  setOrigin(xOrigin, yOrigin);
}
