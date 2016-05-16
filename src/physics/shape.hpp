#ifndef SHAPE_HPP
#define SHAPE_HPP

/* An abstract class that repersents a shape.
 */

class Shape
{
private:
protected:
public:
  Shape ();
  virtual ~Shape () =0;

  virtual bool overlaps (Shape const & other) const;
  /* Visitor pattern may be needed to handle different combinations of shapes.
   */
};

#endif//SHAPE_HPP
