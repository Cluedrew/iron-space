#include "nulling-target.hpp"

// Default Constructor for NullingTarget
NullingTarget::NullingTarget() :
  ptrsToThis()
{}

#define FOREACH_PTR(it_name) \
for (ptr_iterator it_name = ptrsToThis.begin() ; \
     it_name != ptrsToThis.end() ; ++it_name)

/*
#define FOREACH_PTR(iterator, container) \
for (ptr_iterator iterator = container.begin() ; \
     it_name != container.end() ; ++it_name)
*/

// Deconstructor
NullingTarget::~NullingTarget ()
{
  //for (ptr_iterator it = ptrsToThis.begin() ; it != ptrsToThis.end() ; ++it)
  FOREACH_PTR(it)
  {
     (**it).ptr = nullptr;
  }
}

// see header
NullingTarget::NullingTarget(NullingTarget && other) :
  ptrsToThis(other.ptrsToThis)
{
  // Is other.ptrsToThis emptied?

  //for (ptr_iterator it = ptrsToThis.begin() ; it != ptrsToThis.end() ; ++it)
  FOREACH_PTR(it)
  {
     (**it).assignPtr(this);
  }
}

#undef FOREACH_PTR

// see header
NullingTarget & NullingTarget::operator=(NullingTarget && other)
{
  while (!other.ptrsToThis.empty())
  {
    GameObjectPtr * ptr = other.ptrsToThis.back();
    ptr->assignPtr(this);
    other.ptrsToThis.pop_back();
  }
  return *this;
}
