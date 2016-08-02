#ifndef REL_TRANS_HPP
#define REL_TRANS_HPP

/* The RelativeTransformable class is a Transformable that messures its
 * position relative to another Transformable. The Transformable functions
 * effect the relative transform, a call to update re-calculates the absolute
 * transform (in world space) by measuring relative to the given root.
 *
 * TODO Figure out what the relative and absolute origin actually means.
 *      Problem: does not actually do a relative transformation,
 *      or rather does it by component, instead of all being messured from the
 *      new origin.
 */

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

class RelativeTransformable : protected sf::Transformable
{
private:
  sf::Transformable absTransform;

protected:
public:
  RelativeTransformable ();
  /* Default Constructor, relative transform is default constructed which
   * I think makes it the identy matrix?
   */

  virtual ~RelativeTransformable ();

  void update (sf::Transformable const & parent);
  /* Update the absolute transform, which caches the mesurement from parent.
   * Params: Reference to parent transformable, which is what this tranform
   *   is relative to.
   */

  void setRelPosition (float x, float y);
  void setRelPosition (sf::Vector2f const & position);
  void setRelRotation (float angle);
  void setRelScale (float factorX, float factorY);
  void setRelScale (sf::Vector2f const & factors);
  void setRelOrigin (float x, float y);
  void setRelOrigin (sf::Vector2f const & origin);
  void moveRel (float x, float y);
  void moveRel (sf::Vector2f const & position);
  void rotateRel (float angle);
  void scaleRel (float factorX, float factorY);
  void scaleRel (sf::Vector2f const & factors);
  /* All setters go to the relative transform but are otherwise identical
   *   to the Transforable functions of the similar name.
   * See sf::Transformable for details.
   */

  sf::Vector2f const & getRelPosition () const;
  sf::Vector2f const & getAbsPosition () const;
  float getRelRotation () const;
  float getAbsRotation () const;
  sf::Vector2f const & getRelScale () const;
  sf::Vector2f const & getAbsScale () const;
  sf::Vector2f const & getRelOrigin () const;
  sf::Vector2f const & getAbsOrigin () const;
  sf::Transform const & getRelTransform () const;
  sf::Transform const & getAbsTransform () const;
  sf::Transform const & getRelInverseTransform () const;
  sf::Transform const & getAbsInverseTransform () const;
  /* All the getters come in pairs, one for the relative and one for
   *   the absolute transform.
   * See sf::Transformable for details.
   */

  static sf::Transformable const identity;
};

#endif//REL_TRANS_HPP
