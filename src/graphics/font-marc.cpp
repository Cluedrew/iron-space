#include "font-marc.hpp"

// Implementation of the FontMaRC and the related exception.

#include "util/except.hpp"



// TODO: Does this need to go into the header or can it be forward declared?
struct FontLoadError : public FileError
{
  FontLoadError (std::string const & file) :
    FileError("Could not load from font file: ", file)
  {}
};

MaRCData<std::string, sf::Font> * loadFontFromFile (std::string fontName)
{
  MaRCData<std::string, sf::Font> * fin =
      new MaRCData<std::string, sf::Font>(fontName);

  static std::string fontDir =
      std::string("/usr/share/fonts/truetype/freefont/");
  if (!fin->coreData.loadFromFile(fontDir + fontName))
    throw FontLoadError(fontName);

  return fin;
}
