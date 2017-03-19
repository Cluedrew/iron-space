#ifndef COUNT_PTR_TPP
#define COUNT_PTR_TPP

/* Reference counting pointers and reference objects. Unlike the built in
 * types they require a little bit of help from the target, T must have a
 * integer field referenceCount_ that starts at 0 and should otherwise be
 * unused.
 */

#include "count-ptr.hpp"

// CountPtr:

template<typename T>
CountPtr<T>::CountPtr (T * pointer = nullptr) :
  ptr(pointer)
{
  ++ptr->referenceCount_;
}

template<typename T>
CountPtr<T>::CountPtr (CountPtr<T> && pointer) :
  ptr(pointer.ptr)
{
  pointer.ptr = nullptr;
}

template<typename T>
CountPtr<T>::~CountPtr ()
{
  if (ptr)
    if (0 == (--ptr->referenceCount_))
      delete ptr;
}

template<typename T>
CountPtr<T>::operator T * ()
{
  return ptr;
}

template<typename T>
T * CountPtr<T>::operator= (T * pointer)
{
  if (ptr)
    if (0 == (--ptr->referenceCount_))
      delete ptr;
  ptr = pointer;
  ++ptr->referenceCount_;
}

// CountRef:

template<typename T>
class CountRef<T>::CountRef (T & ref) :
  ref(ref)
{
  ++ref.referenceCount_;
}

template<typename T>
class CountRef<T>::~CountRef ()
{
  if (0 == (--ref.referenceCount_))
    delete &ref;
}

template<typename T>
class CountRef<T>::operator T & () const
{
  return ref;
}

#if 0
template<typename T>
unsigned int getReferenceCount(CountPtr<T> const & ptr)
{
  return ptr.ptr->referenceCount_;
}

template<typename T>
unsigned int getReferenceCount(CountRef<T> const & ref)
{
  return ref.ref.referenceCount_;
}
/* Get the current number of references on the referenced object.
 * Params: The reference or pointer.
 * Return:
 *
 * This has a slightly obtuse name on purpose to avoid name overlap. Which
 * is also why they aren't members. Although I'm not even sure if they would
 * be useful.
 * CountPtr: friend unsigned int getReferenceCount(CountPtr<T> const &);
 * CountRef: friend unsigned int getReferenceCount(CountRef<T> const &);
 */
#endif//0

#endif//COUNT_PTR_HPP
