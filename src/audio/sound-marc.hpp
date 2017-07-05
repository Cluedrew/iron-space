#ifndef SOUND_MARC_HPP
#define SOUND_MARC_HPP

/* MaRC for sounds, storing their SoundBuffer.
 *
 * This is not the Sound object itself, it is the SoundBuffer. As long as
 * each Sound that wants to use the buffer has access to an existing SoundMaRC
 * the buffer will remain loaded and ready.
 */

#include <string>
#include <SFML/Audio/SoundBuffer.hpp>
#include "util/marc.hpp"

MaRCData<std::string, sf::SoundBuffer> *
    openSoundBuffer (std::string fileName);
/* For use by SoundMaRC. Creates and opens a sound buffer
 * Params: Name of file in rsrc/sound/ to load data from.
 * Return: Pointer to dynamical allocated MaRCData, caller must free.
 * Except: SoundLoadError, child of FileError, if the load fails.
 */

using SoundBufferMaRC = MaRC<std::string, sf::SoundBuffer, openSoundBuffer>;

#endif//SOUND_MARC_HPP
