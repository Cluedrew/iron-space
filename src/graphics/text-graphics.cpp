#include "text-graphics.hpp"

// Implementation of TextGraphics.

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Color.hpp>



// TODO: Keep? Move to Library? Remove?
// I'm just trying out some other formats.
float alignedVerticalOrigin (VerticalAlignment alignment, float y)
{
  switch(alignment)
  {
  case VerticalAlignment::Top:
    return 0;
  case VerticalAlignment::Middle:
    return y / 2;
  case VerticalAlignment::Bottom:
  default:
    return y;
  }
}

float alignedHorizontalOrigin (HorizontalAlignment alignment, float x)
{
  switch (alignment)
  {
  case HorizontalAlignment::Left:
     return 0;
  case HorizontalAlignment::Center:
     return x / 2;
  case HorizontalAlignment::Right:
  default:
     return x;
  };
}

sf::Vector2f alignedOrigin (Alignment2D alignment, sf::FloatRect xy)
{
  return sf::Vector2f(
      alignedHorizontalOrigin(horizontalAlignmentComponent(alignment),
                              xy.width),
      alignedVerticalOrigin(verticalAlignmentComponent(alignment),
                            xy.height));
}



TextGraphics::TextGraphics (std::string const & font_,
                            std::string const & text_,
                            Alignment2D alignment) :
  font(FontLibrary::getFont(font_)), text(text_, *font)
{
  // text.set{Fill,Outline}Color becomes prefered as of SFML 2.4.1.
  text.setColor(sf::Color::Blue);
  setAlignment(alignment);
}

TextGraphics::~TextGraphics ()
{}

void TextGraphics::draw (sf::RenderTarget & target,
                         sf::RenderStates states) const
{
  // TODO: Can this ever fail? if not a faster cast should be used.
  target.draw(text, states);
}

void TextGraphics::setAlignment(Alignment2D alignment)
{
  sf::FloatRect bounds = text.getLocalBounds();
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
  text.setOrigin(xOrigin, yOrigin);
}
