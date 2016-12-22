#ifndef TEXT_GRAPHICS_HPP
#define TEXT_GRAPHICS_HPP

/* A graphical component that desplays a bit of text.
 *
 * It wraps up an SFML Text object and ensures the Font used stays loaded.
 */

#include <string>
#include <SFML/Graphics/Text.hpp>
#include "graphics-component.hpp"
#include "font-library.hpp"



class TextGraphics : public GraphicsComponent, public sf::Text
{
private:
  FontLibrary::FontReference font;

protected:
public:
  TextGraphics (std::string const & font, std::string const & text);
  /* Create a new TextGraphics component.
   * Params: Takes the name of the font and the string to display as text.
   */

  virtual ~TextGraphics ();

  void draw (sf::RenderTarget & target, sf::RenderStates states) const;
  /* Draw the text to screen.
   * Follows SFML draw conventions.
   */
};

#endif//TEXT_GRAPHICS_HPP
