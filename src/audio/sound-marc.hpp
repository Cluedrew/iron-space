#ifndef SOUND_MARC_HPP
#define SOUND_MARC_HPP

/* MaRC for sounds, storing their SoundBuffer.
 *
 * Trying to make this on a MaRC, but I still have issues there to fix too.
 */

#include <string>
#include <SFML/Audio/SoundBuffer.hpp>
#include "../util/marc.hpp"

sf::SoundBuffer openSoundBeffer (std::string fileName);

using SoundMaRC = MaRC<std::string, sf::SoundBuffer, openSoundBuffer>;

#endif//SOUND_MARC_HPP
