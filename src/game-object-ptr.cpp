#include "game-object-ptr.hpp"

/* A smart-pointer for GameObjects.
 *
 * The internal operations are here to modularise the common tasks.
 */

#include <iostream>
#include <cstdlib>
#include <utility>
#include "game-object.hpp"



/* The dynamic_cast should never fail as the NullingTarget only reassigns
 * pointing at it, and that is gated by the game object type.
 */
void GameObjectPtr::assignPtr(NullingTarget * to)
{
  GameObject * tmp = dynamic_cast<GameObject*>(to);
  if (nullptr == tmp) {
    std::cerr << "Invalid assignment to GameObjectPtr." << std::endl;
    exit(EXIT_FAILURE);
  } else {
    ptr = tmp;
  }
}



#define FOREACH_PTR(name, objPtr) \
  for (std::vector<GameObjectPtr*>::iterator name = \
       objPtr->ptrsToThis.begin() ; \
       name != objPtr->ptrsToThis.end() ; ++name )

// Internal operations:

/* unregester()
 * Internal function for setting the pointer to point at nothing.
 * If the pointer already points at nothing than nothing is done.
 */
void GameObjectPtr::unregester ()
{
  if (nullptr == ptr)
    return;

  //std::vector<GameObjectPtr>::iterator it;
  //for (it = ptr->ptrsToThis.begin() ; it != ptr->ptrsToThis.end() ; ++it)
  FOREACH_PTR(it, ptr)
  {
    if (this == *it)
    {
      ptr->ptrsToThis.erase(it);
      ptr = nullptr;
      return;
    }
  }

  std::cerr << "ERROR: GameObject does not have a back reference to"
    << " the GameObjectPtr." << std::endl;
  exit(EXIT_FAILURE);
}

/* regesterTo(obj)
 * Internal function for setting the pointer to point at something.
 * If the pointer already points at something it is first unregestered.
 */
void GameObjectPtr::regesterTo (GameObject * obj)
{
  unregester();

  obj->ptrsToThis.push_back(this);
  ptr = obj;
}

/* takeRegester(other)
 * Take the other GameObjectPtr's pointer, nulling it if it isn't already
 * null.
 */
void GameObjectPtr::takeRegester (GameObjectPtr && other)
{
  unregester();

  if (nullptr == other.ptr)
    return;

  FOREACH_PTR(it, other.ptr)
  {
    if (&other == *it)
    {
      *it = this;
      ptr = other.ptr;
      other.ptr = nullptr;
      return;
    }
  }

  std::cerr << "ERROR: GameObject does not have a back reference to"
    << " the GameObjectPtr." << std::endl;
  exit(EXIT_FAILURE);
}

#undef FOREACH_PTR

// Constructors & Deconstructor ==============================================

// see header
GameObjectPtr::GameObjectPtr () :
  ptr(nullptr)
{}

// see header
GameObjectPtr::GameObjectPtr (GameObjectPtr const & other) :
  ptr(nullptr)
{
  regesterTo(other.ptr);
}

// see header
GameObjectPtr::GameObjectPtr (GameObjectPtr && other) :
  ptr(nullptr)
{
  takeRegester(std::move(other));
}


// see header
GameObjectPtr::GameObjectPtr (GameObject & object) :
  ptr()
{
  regesterTo(&object);
}

// see header
GameObjectPtr::~GameObjectPtr ()
{
  unregester();
}



// Dereferencing Operators ===================================================
// see header
GameObject & GameObjectPtr::operator* ()
{
  return *ptr;
}

// see header
GameObject * GameObjectPtr::operator-> ()
{
  return ptr;
}

// Predicate Operators =======================================================
// see header
bool GameObjectPtr::nonNull () const
{
  return nullptr != ptr;
}

// see header
GameObjectPtr::operator bool () const
{
  return nullptr != ptr;
}

// see header
bool GameObjectPtr::isNull () const
{
  return nullptr == ptr;
}



// Assignment Operators
void GameObjectPtr::setNull ()
{
  unregester();
}

void GameObjectPtr::setTo (GameObject & object)
{
  regesterTo(&object);
}

GameObjectPtr & GameObjectPtr::operator= (GameObjectPtr const & other)
{
  regesterTo(other.ptr);
  return *this;
}

GameObjectPtr & GameObjectPtr::operator= (GameObjectPtr && other)
{
  takeRegester(std::move(other));
  return *this;
}

// TODO? Add operator= (GameObject &|* object)?



// Comparison Operators
bool GameObjectPtr::operator== (GameObjectPtr const & other) const
{
  return ptr == other.ptr;
}

bool GameObjectPtr::operator!= (GameObjectPtr const & other) const
{
  return ptr != other.ptr;
}

bool GameObjectPtr::operator> (GameObjectPtr const & other) const
{
  return ptr > other.ptr;
}

bool GameObjectPtr::operator< (GameObjectPtr const & other) const
{
  return ptr < other.ptr;
}

bool GameObjectPtr::operator>= (GameObjectPtr const & other) const
{
  return ptr >= other.ptr;
}

bool GameObjectPtr::operator<= (GameObjectPtr const & other) const
{
  return ptr <= other.ptr;
}
