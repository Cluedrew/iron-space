#ifndef ANGLE_HPP
#define ANGLE_HPP

/* Repersents an angle.
 *
 * Depending on context this angle can repersent just about anything, but for
 * an absolute access it should be the angle counter-clockwise from the
 * positive x access.
 */

class Angle
{
private:
  Angle ();

  float a;
protected:
public:
  Angle (Angle const & other) = default;
  Angle (Angle && other) = default;

  virtual ~Angle ();

  Angle & operator= (Angle const & other) = default;
  Angle & operator= (Angle && other) = default;

  static Angle fromDegrees (float degrees);
  static Angle fromRadians (float radians);

  float toDegrees ();
  float toRadians ();

  float xUnitComponent ();
  float yUnitComponent ();

  Angle operator+ (Angle const & other) const;
  Angle operator- (Angle const & other) const;
  Angle & operator- ();
};

#endif//ANGLE_HPP
