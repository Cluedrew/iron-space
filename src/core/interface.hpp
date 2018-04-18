#ifndef INTERFACE_HPP
#define INTERFACE_HPP

/* Manages the player's interface into the game.
 *
 * It is a effectively a static class because this game is single player game,
 * therefore it is locked to exactly one instance.
 */

#include <set>
#include "object/entity.hpp"



class Selection : public std::set<Entity *>
/* A wrapper class around a set of Entity pointers. The standard set functions
 * are usually sufficient, but for a couple of cases I just needed something
 * extra.
 */
{
public:
  inline void setTo(Entity * entity)
  { clear(); insert(entity); }
  inline void setTo(std::vector<Entity *> const entities)
  { clear(); insert(entities.begin(), entities.end()); }
  inline void setTo(std::set<Entity *> const entities)
  { clear(); insert(entities.begin(), entities.end()); }
  /* Replace the contents of the Selection with a new entity or entities.
   * Params:
   *   - A single Entity pointer.
   *   - A container that contains entity pointers.
   * Effect: The Selection contains only (and all) entities given.
   */
  //template<typename ContainerT>
  //inline void setTo(ContainerT const & entities)
  //{ clear(); insert(entities.begin(), entities.end()); }
};


struct Interface
{
  Selection selection;
};

extern Interface interface;

#endif//INTERFACE_HPP
