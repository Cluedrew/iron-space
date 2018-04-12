#ifndef ENTITY_HPP
#define ENTITY_HPP

/* The base object for your interactable objects. Anything that you would
 * want to select, examine and command comes from this. Hence it is where
 * actual game logic really starts coming in.
 *
 * They share the ablitity to be selected and, while selected, to display
 * their data to the user and be issued commands. Some can be issued zero
 * commands, but the support structure is there.
 *
 * You must use the three inner functions instead of an AiComponent.
 */

#include "plane-object.hpp"

#include <string>
namespace sf { class RenderTarget; class RenderStates; }
class StatusDisplay;
class PhysicsComponent;
class GraphicsComponent;



class Entity : public PlaneObject
{
private:
protected:
public:
  Entity (PhysicsComponent * physics, GraphicsComponent * graphics);
  Entity (sf::Transformable const & start,
          PhysicsComponent * physics, GraphicsComponent * graphics);

  virtual std::string const & getName () const = 0;
  /* Non-unique name of this entity.
   * Return: Reference to string, should be valid at least until the next
   *   non-const function is called.
   */

  virtual void display (StatusDisplay & target) const = 0;
  /* Depends on what sort of tools and stuff I provide, putting a mini-
   * toolkit in StatusDisplay could make drawing all of these really easy,
   * but possibly not easy enough to justify the extra work.
   */

  // These overloads are used to implement the non-inner versions on
  // GameObject when AiWrapper is the AiComponent.
  virtual bool innerHandleInput (InputEvent const & input) { return false; }
  virtual void innerUpdateAi (sf::Time const & deltaT) {}
  virtual void innerHandleCollision (GameObjectPtr & with) {}
};

#endif//ENTITY_HPP
