#ifndef SOUND_LIBRARY_HPP
#define SOUND_LIBRARY_HPP

/* A repository for loaded sound files.
 */



class SoundLibrary
{
private:
protected:
public:
  SoundLibrary ();
  virtual ~SoundLibrary ();

  SoundId loadSound (std::string);
  playSound (SoundId);

  // Moving is supported, copying is not.
  SoundLibrary (SoundLibrary const &) = delete;
  SoundLibrary (SoundLibrary && other) = default;
  SoundLibrary & operator= (SoundLibrary const &) = delete;
  SoundLibrary & operator= (SoundLibrary && other) = default;
};

#endif//SOUND_LIBRARY_HPP
