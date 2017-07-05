#include "sound-marc.hpp"

// Implementations for the SoundMaRC
// (even though it is never refered to directly)

#include <cassert>
#include <string>
#include "util/rsrc-dir.hpp"
#include "util/except.hpp"



std::string const soundDirectory = std::string(resourceDirectory) + "sound/";

class SoundLoadError : public FileError
{
public:
  SoundLoadError (std::string const & file) :
    FileError("Could not open sound effect file: ", file)
  {}
};



MaRCData<std::string, sf::SoundBuffer> *
    openSoundBuffer (std::string fileName)
{
  MaRCData<std::string, sf::SoundBuffer> * fin =
      new MaRCData<std::string, sf::SoundBuffer>(fileName);

  if (!fin->coreData.loadFromFile(soundDirectory + fileName))
    throw SoundLoadError(fileName);

  return fin;
}
