#ifndef INTERFACE_HPP
#define INTERFACE_HPP

/* Manages the player's interface into the game.
 *
 * It is a effectively a static class because this game is single player game,
 * therefore it is locked to exactly one instance.
 */

#include <set>
#include "object/entity.hpp"



class Interface
{
  std::set<Entity *> selected;

public:
  // SelectIterator & ConstSelectIterator
  using select_iterator = std::set<Entity *>::iterator;
  using const_select_iterator = std::set<Entity *>::const_iterator;

  void clearSelect();
  /* Clear the current selection.
   * Effect: Changes the selection so no entities are selected.
   */

  void select(Entity *);
  void select(std::vector<Entity *>);
  /* Clear the current selection and replace it with the given entity/ies.
   * Params: A pointer Entity, or pointers to the Entities, to select.
   * Effect: Changes the selection so only the provided entities are selected.
   */

  size_t numSelected();
  /* Get the size of the current selection.
   * Return: The number of unique entities currently selected.
   */

  select_iterator selectBegin();
  const_select_iterator selectCBegin() const;
  select_iterator selectEnd();
  const_select_iterator selectCEnd() const;
};

extern Interface interface;

#endif//INTERFACE_HPP
