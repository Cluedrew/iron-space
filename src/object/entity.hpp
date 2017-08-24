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
 * EntityKind is the Type Object for entities. Most entities belong to a group
 * that all have the same base. They may very in location or current health,
 * but their base is the same.
 *
 * The main trick is how to seperates entities with different kinds of data.
 * For instance a mineable resource has only the amount left. A unit will
 * likely have health, and one or two bits of active data.
 */

#include "plane-object.hpp"

#include <string>
namespace sf { class RenderTarget; class RenderStates; }
class StatusDisplay;



class EntityKind;

class Entity : public PlaneObject
{
private:
  EntityKind const * kind;
protected:
public:
  Entity (EntityKind const *);

  std::string const & getName () const;

  virtual void display (sf::RenderTarget& target, sf::RenderStates states)
    const;
  /* Draw/write the data for this entity to the user's display.
   * Params: target is the status display widget, and states are the
   *   current render states.
   */
  // OR
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

struct EntityKind
{
  std::string const name;

  EntityKind (std::string const name) : name(name) {}

  Entity * makeEntity() const;
};



inline std::string const & Entity::getName () const { return kind->name; }

#endif//ENTITY_HPP
