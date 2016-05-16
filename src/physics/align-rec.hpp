#ifndef ALIGN_REC_HPP
#define ALIGN_REC_HPP

/* A shape that repersents a rectangle that has its sides aligned with the
 *   x & y axis. Many GUI elements use this shape.
 */



class AlignRec
{
private:
  float halfWidth;
  float halfHeight;

  virtual bool overlaps (Circle const & other);
  virtual bool overlaps (AlignRect const & other);

protected:
public:
  AlignRec (float halfWidth, float halfHeight);
  virtual AlignRec ();

  virtual bool overlaps (Shape const & other);
};
#endif//ALIGN_REC_HPP
