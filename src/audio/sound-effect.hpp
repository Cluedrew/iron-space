#ifndef SOUND_EFFECT_HPP
#define SOUND_EFFECT_HPP

/* This is handles a simple case of a Sound and SoundMaRC. If the MaRC is not
 * reused than the SoundEffect can create both at the same time. A
 * SoundEffect forwards the Sound's interface but hides the SoundMaRC's
 */

#include <string>
#include <SFML/Audio/Sound.hpp>
#include "sound-marc.hpp"

class SoundEffect : public sf::Sound
{
  SoundMaRC buffer;

public:
  SoundEffect(std::string fileName) :
    sf::Sound(), buffer(fileName)
  {
    setBuffer(*buffer);
  }
};

#endif//SOUND_EFFECT_HPP
