#ifndef SHAPE_HPP
#define SHAPE_HPP

/* An abstract class that repersents a shape.
 *
 * There is one issue, and that is that I'm not sure how Shapes keep track
 * of their location. I would like to use the GameObject's tranform but I
 * have no system to get that information into the Shape.
 * Solutions:
 * + Store a reference/pointer to the transform.
 * + Store a copy of the location, update during the physics step.
 */

class Shape
{
private:
protected:
  virtual bool overlaps (Circle const & other) const =0;
  virtual bool overlaps (AlignRect const & other) const =0;
  /* Internal Fuctions:
   * Does this Shape overlap with the other Shape of the given type?
   */

public:
  Shape ();
  virtual ~Shape () =0;

  virtual bool overlaps (Shape const & other) const =0;
  /* Does this Shape overlap with the other Shape?
   * Params: A reference to the other shape.
   * Return: True if any part of the two Shapes occupy the same space.
   */
};

#endif//SHAPE_HPP
