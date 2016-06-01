#ifndef DRAW_COMPONENT_HPP
#define DRAW_COMPONENT_HPP

/* Component that draws an image to the screen.
 *
 * Right now this is sort of a scratch-pad as I figure out what the drawing
 * will actually need.
 */



class DrawComponent : public sf::Drawable
{
private:
  void draw (sf::RenderTarget & target, sf::RenderStates states) const;

protected:
public:
  DrawComponent ();
  virtual DrawComponent ();

  void adjust (GameObject const &);
  /* Update the interal image's position to match the change in the host
   * GameObject's position.
   */
};

#endif//DRAW_COMPONENT_HPP
