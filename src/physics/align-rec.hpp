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
  virtual ~AlignRec ();

  virtual bool overlaps (Shape const & other);
  /* Does this Shape overlap with the other Shape?
   * Params: A reference to the other shape.
   * Return: True if any part of the two Shapes occupy the same space.
   */
};
#endif//ALIGN_REC_HPP
