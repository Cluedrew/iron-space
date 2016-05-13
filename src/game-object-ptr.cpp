#include "game-object-ptr.hpp"

/* A smart-pointer for GameObjects.
 *
 * The internal operations are here to modularise the common tasks.
 */



// Internal operations:

/* unregester()
 * Internal function for setting the pointer to point at nothing.
 * If the pointer already points at nothing than nothing is done.
 */
void GameObjectPtr::unregester ();

/* regesterTo(obj)
 * Internal function for setting the pointer to point at something.
 * If the pointer already points at something it is first unregestered.
 */
void GameObjectPtr::regesterTo (GameObject * obj);

/* regesterSwitch(other
 */
void GameObjectPtr::regesterSwitch (GameObjectPtr && other);

// First level,

// unregesterSafe()
// copyOther()
// replaceOther()

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
  regesterSwitch(other);
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
  if (ptr)
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
  if (ptr)
    unregester();
}

void GameObjectPtr::setTo (GameObject & object)
{
  if (ptr)
    unregester();
}

GameObjectPtr & GameObjectPtr::operator= (GameObjectPtr const & other)
{
  if (ptr)
    unregester();
  regesterTo(other.ptr);
}

GameObjectPtr & GameObjectPtr::operator= (GameObjectPtr && other)
{
  if (ptr)
    unregester();
  regesterSwitch(other);
}

// Comparison Operators
bool GameObjectPtr::operator== (GameObjectPtr const & other) const
{ return ptr == other.ptr; }

bool GameObjectPtr::operator!= (GameObjectPtr const & other) const
{ return ptr != other.ptr; }

bool GameObjectPtr::operator> (GameObjectPtr const & other) const
{ return ptr > other.ptr; }

bool GameObjectPtr::operator< (GameObjectPtr const & other) const
{ return ptr < other.ptr; }

bool GameObjectPtr::operator>= (GameObjectPtr const & other) const
{ return ptr >= other.ptr; }

bool GameObjectPtr::operator<= (GameObjectPtr const & other) const
{ return ptr <= other.ptr; }
