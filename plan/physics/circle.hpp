#ifndef CIRCLE_HPP
#define CIRCLE_HPP

/* A class that repersents a circular shape.
 *
 * Most entities within the game world are circular, or close enough that it
 *   can be an approximation.
 */



class Circle : public Shape
{
private:
  float radius;

protected:
  virtual bool overlaps (Circle const & other) const;
  virtual bool overlaps (AlignRect const & other) const ;

public:
  Circle (float radius);
  virtual ~Circle ();

  virtual bool overlaps (Shape const & other) const;
  /* Does this Shape overlap with the other Shape?
   * Params: A reference to the other shape.
   * Return: True if any part of the two Shapes occupy the same space.
   */
};

#endif//CIRCLE_HPP
