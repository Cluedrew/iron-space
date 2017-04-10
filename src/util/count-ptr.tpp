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
CountPtr<T>::CountPtr (T * pointer) :
  ptr(pointer)
{
  if (ptr)
    ++ptr->referenceCount_;
}

template<typename T>
CountPtr<T>::CountPtr (CountPtr<T> const & other) :
  ptr(other.ptr)
{
  if (ptr)
    ++ptr->referenceCount_;
}

template<typename T>
CountPtr<T>::CountPtr (CountPtr<T> && other) :
  ptr(other.ptr)
{
  other.ptr = nullptr;
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
CountPtr<T> & CountPtr<T>::operator= (T * pointer)
{
  if (ptr == pointer)
    return *this;

  if (ptr)
    if (0 == (--ptr->referenceCount_))
      delete ptr;
  ptr = pointer;
  if (ptr)
    ++ptr->referenceCount_;

  return *this;
}

template<typename T>
CountPtr<T> & CountPtr<T>::operator= (CountPtr<T> const & other)
{
  return (*this = other.ptr);
}

template<typename T>
CountPtr<T> & CountPtr<T>::operator= (CountPtr<T> && other)
{
  return (*this = other.ptr);
}


// CountRef:

template<typename T>
CountRef<T>::CountRef (T & ref) :
  ref(ref)
{
  ++ref.referenceCount_;
}

template<typename T>
CountRef<T>::CountRef (CountRef<T> const & other) :
  ref(other.ref)
{
  ++ref.referenceCount_;
}

template<typename T>
CountRef<T>::CountRef (CountRef<T> && other) :
  ref(other.ref)
{
  ++ref.referenceCount_;
}

template<typename T>
CountRef<T>::~CountRef ()
{
  if (0 == (--ref.referenceCount_))
    delete &ref;
}

template<typename T>
CountRef<T>::operator T & () const
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
