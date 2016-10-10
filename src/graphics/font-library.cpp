#include "font-library.hpp"

/* Implementation of the FontLibrary class/modual
 * and the FontReference helper.
 */



// If I use pointers to the string, to remove duplicate storage of the string
// key.
class stringPtrLess
{
  bool operator() (std::string * lhs, std::string * rhs)
  {
    return *lhs < *rhs;
  }
};

// Static Data Members
std::map<std::string, FontLibrary::AnnotatedFont *> FontLibrary::loadedFonts;



FontLibrary::FontReference::FontReference (AnnotatedFont * annotFont) :
  data(*annotFont)
{ ++data.uses; }

FontLibrary::FontReference::FontReference (FontReference const & other) :
  data(other.data)
{ ++data.uses; }

FontLibrary::FontReference::FontReference (FontReference && other) :
  data(other.data)
{ ++data.uses; }

FontLibrary::FontReference::~FontReference ()
{
  --data.uses;
  if (0 == data.uses)
  {
    loadedFonts.erase(data.name);
    delete(&data);
  }
}

sf::Font & FontLibrary::FontReference::operator* ()
{ return data.coreFont; }

sf::Font const & FontLibrary::FontReference::operator* () const
{ return data.coreFont; }

sf::Font * FontLibrary::FontReference::operator-> ()
{ return &(data.coreFont); }

sf::Font const * FontLibrary::FontReference::operator-> () const
{ return &(data.coreFont); }



FontLibrary::FontReference
FontLibrary::getFont(std::string const & fontName)
{
  if (loadedFonts.count(fontName))
  {
    return FontReference(loadedFonts.find(fontName)->second);
  }
  std::string fontDir = std::string("/usr/share/fonts/truetype/freefont/");
  std::string fileName = fontDir + fontName;
  AnnotatedFont * afont = new AnnotatedFont;
  afont->name = fontName;
  afont->uses = 0;
  afont->coreFont.loadFromFile(fileName);
  loadedFonts.insert(std::make_pair(fontName, afont));
  return FontReference(afont);
}
