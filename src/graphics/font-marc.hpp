#ifndef FONT_MARC_HPP
#define FONT_MARC_HPP

#include <string>
#include <SFML/Graphics/Font.hpp>
#include "util/marc.hpp"

struct FontLoadError;
// Exception class.

MaRCData<std::string, sf::Font> * loadFontFromFile (std::string fontName);
/* For use by FontMaRC. Loads a font into a new Font object.
 * Params: Name of font, which is the pathname of the font file relative to
 *   the font directory.
 * Return: Non-null pointer to new MaRCData, caller must free.
 * Except: Throws FontLoadError if there is an error.
 */

using FontMaRC = MaRC<std::string, sf::Font, loadFontFromFile>;

#endif//FONT_MARC_HPP
