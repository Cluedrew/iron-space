#include "interface.hpp"



// The one interface we use in this one player game.
Interface interface;

// see header
void Interface::clearSelect()
{
  selected.clear();
}

// see header
void Interface::select(Entity * entity)
{
  selected.clear();
  selected.insert(entity);
}

// see header
void Interface::select(std::vector<Entity *> entities)
{
  selected.clear();
  for (Entity * entity : entities) {
    selected.insert(entity);
  }
}

// see header
size_t Interface::numSelected()
{
  return selected.size();
}

Interface::select_iterator Interface::selectBegin()
{
  return selected.begin();
}

Interface::const_select_iterator Interface::selectCBegin() const
{
  return selected.cbegin();
}

Interface::select_iterator Interface::selectEnd()
{
  return selected.end();
}

Interface::const_select_iterator Interface::selectCEnd() const
{
  return selected.cend();
}
