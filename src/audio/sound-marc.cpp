#include "sound-marc.hpp"

// Implementations for the SoundMaRC
// (even though it is never refered to directly)

#include <cassert>
#include <string>
#include "../util/rsrc-dir.hpp"

std::string const soundDirectory = std::string(resourceDirectory) + "sound/";

MaRCData<std::string, sf::SoundBuffer> *
    openSoundBuffer (std::string fileName)
{
  MaRCData<std::string, sf::SoundBuffer> * fin =
      new MaRCData<std::string, sf::SoundBuffer>(fileName);

  assert(fin->coreData.loadFromFile(soundDirectory + fileName));

  return fin;
}
