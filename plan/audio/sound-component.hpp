#ifndef SOUND_COMPONENT_HPP
#define SOUND_COMPONENT_HPP

/* A component that handles requests for sounds from the SoundLibrary.
 *
 * It can mark sounds as Frequent (as in it will play them frequently) so
 * the sound library is less likely to unload it.
 */



class SoundComponent
{
private:
  enum class SoundMarks : char { Frequent, Prepared };
  std::map<SoundId,SoundMarks> markedSounds;

protected:
public:
  SoundComponent ();
  virtual ~SoundComponent ();

  void playSound(SoundId);
  /* Request that a particular sound is played from the SoundLibrary.
   */

  void frequent(SoundId);
  /* Marks a sound that will be played frequently, so the SoundLibrary
   * will keep it loaded.
   */

  void infrequent(SoundId);
  /* Removes the frequency mark from a sound.
   */

  void prepareSound(SoundId);
  /* Mark a sound that will be played soon. It will be considered
   * frequent until it is played.
   */
};

#endif//SOUND_COMPONENT_HPP
