#include "text-graphics.hpp"

// Implementation of TextGraphics.

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Color.hpp>



TextGraphics::TextGraphics (std::string const & font_,
                            std::string const & text_) :
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
