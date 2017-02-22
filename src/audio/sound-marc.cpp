#include "sound-marc.hpp"

// Implementations for the SoundMaRC
// (even though it is never refered to directly)

#include <cassert>

MaRCData<std::string, sf::SoundBuffer> *
    openSoundBuffer (std::string fileName)
{
  MaRCData<std::string, sf::SoundBuffer> * fin =
      new MaRCData<std::string, sf::SoundBuffer>(fileName);

  assert(fin->coreData.loadFromFile(fileName));

  return fin;
}
