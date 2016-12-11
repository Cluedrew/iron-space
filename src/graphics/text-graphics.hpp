#ifndef TEXT_GRAPHICS_HPP
#define TEXT_GRAPHICS_HPP

/* A graphical component that desplays a bit of text.
 *
 * TODO: If this is going to be the basic text desplay option then it should
 *   probably give more control over the text.
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
