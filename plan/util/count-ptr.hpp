#ifndef COUNT_PTR_HPP
#define COUNT_PTR_HPP

/* Reference counting pointers and reference objects. Unlike the built in
 * types they require a little bit of help from the target>. T must have a
 * integer field referenceCount_ that starts at 0 and should otherwise be
 * unused. Generally it should be private with the two pointer types as
 * friends of the target.
 *
 * I tried keeping the operators to a minimum, allowing conversion to
 * unwrapped reference followed by the usual operation instead of defining
 * all of them myself. I'm not sure if it will work, especally around move
 * operations.
 */

template<typename T>
class CountPtr
{
  T * ptr;
public:
  CountPtr (T * pointer = nullptr);

  CountPtr (CountPtr<T> && pointer);

  ~CountPtr ();

  operator T * ();

  T * operator= (T * pointer);
};

template<typename T>
class CountRef
{
  T & ref;
public:
  CountRef (T & ref);

  ~CountRef ();

  operator T & () const;
};

#include "count-ptr.tpp"

#endif//COUNT_PTR_HPP
