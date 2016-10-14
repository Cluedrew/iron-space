#ifndef FONT_LIBRARY_HPP
#define FONT_LIBRARY_HPP

/* The FontLibrary is a pure static class that holds loaded instances of the
 * sf::Font class. It covers the loading of the Font and sharing of instances
 * to allow re-use.
 */

#include <SFML/Graphics/Font.hpp>
#include <utility>
#include <string>
#include <map>



class FontLibrary
{
public:
  struct AnnotatedFont
  {
    std::string name;
    unsigned int uses;
    sf::Font coreFont;
  };

  class FontReference
  {
  private:
    AnnotatedFont & data;

  protected:
  public:
    FontReference (AnnotatedFont *);
    FontReference (FontReference const &);
    FontReference (FontReference &&);
    virtual ~FontReference ();

    FontReference operator== (FontReference const &) = delete;
    FontReference operator== (FontReference &&) = delete;
    sf::Font & operator* ();
    sf::Font const & operator* () const;
    sf::Font * operator-> ();
    sf::Font const * operator-> () const;
  };

private:
  static std::map<std::string, AnnotatedFont *> loadedFonts;

protected:
public:
  static FontReference
  getFont (std::string const & fontName);
  /* Get a FontReference for a font with the given name.
   * Params: Name of the font to load.
   * Effect: Loads the font if it is not already loaded.
   * Return: A reference to the loaded font.
   */
};

#endif//FONT_LIBRARY_HPP