#ifndef PLANE_DRAWABLE_TPP
#define PLANE_DRAWABLE_TPP

// Implementation of the Drawable Plane class.



template<typename Drawable2D>
void PlaneDrawable<Drawable2D>::draw
    (sf::RenderTarget & target, sf::RenderStates states) const
{
  typename Plane<Drawable2D>::const_iterator it;
  for (it = this->cbegin() ; it != this->cend() ; ++it)
    target.draw(*it, states);
}

#endif//PLANE_DRAWABLE_TPP
