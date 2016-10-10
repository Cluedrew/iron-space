#ifndef TEXT_GRAPHICS_HPP
#define TEXT_GRAPHICS_HPP

/* A graphical component that desplays a bit of text.
 */

#include <string>
#include <SFML/Graphics/Text.hpp>
#include "graphics-component.hpp"
#include "font-library.hpp"



class TextGraphics : public GraphicsComponent
{
private:
  FontLibrary::FontReference font;
  sf::Text text;

protected:
public:
  TextGraphics (std::string const & font, std::string const & text);
  virtual ~TextGraphics ();

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw the text to screen.
   * Follows SFML draw conventions.
   */
};

#endif//TEXT_GRAPHICS_HPP
