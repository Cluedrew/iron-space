#include "text-graphics.hpp"

// Implementation of TextGraphics.

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Color.hpp>



TextGraphics::TextGraphics (std::string const & font_,
                            std::string const & text_) :
  font(FontLibrary::getFont(font_)), text(text_, *font)
{
  // TODO setFillColor should be here, but isn't, check version of SFML.
  text.setColor(sf::Color::Blue);
}

TextGraphics::~TextGraphics ()
{}

void TextGraphics::draw (sf::RenderTarget & target,
                         sf::RenderStates states) const
{
  target.draw(text, states);
}
