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
public:
  Circle (float radius);
  virtual ~Circle ();

  virtual bool overlaps (Shape const & other) const;
};

#endif//CIRCLE_HPP
