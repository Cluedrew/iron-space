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

class ReferenceCounter
/* Instead of hand crafting the features you need every time, you can just
 * inherite from ReferenceCounter.
 */
{
  unsigned int referenceCount_;
  template<typename T>
  friend class CountPtr;
  template<typename T>
  friend class CountRef;

protected:
  ReferenceCounter () :
    referenceCount_(0) {}
  /* Create a new ReferenceCounter object.
   * After the first CountPtr/CountRef selects the pointer
   */

  enum DisableFlagType {Disable};

  ReferenceCounter (DisableFlagType) :
    referenceCount_(1) {}
  /* Create a new ReferenceCounter object that with deallocation disabled.
   * It can (and must) be deallocated manually. Really only useful if you want
   * to allocate it on the stack or as a component of a larger object. Hence
   * having non-pointer access to it.
   */
};

#include "count-ptr.tpp"

#endif//COUNT_PTR_HPP
