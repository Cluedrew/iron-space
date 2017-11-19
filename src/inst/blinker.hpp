#ifndef BLINKER_HPP
#define BLINKER_HPP

/* I realized I am doing all this reworking but I haven't tried it out on a
 * class yet.
 *
 */

#include "object/plane-object.hpp"
#include "audio/sound-effect.hpp"



class Blinker : public PlaneObject
{
private:
  SoundEffect sound;

protected:
  void overlapBegin (PlaneObject & with);
  void overlapEnd (PlaneObject & with);

public:
  Blinker (int x, int y);

  ~Blinker ();
};

#endif//BLINKER_HPP
