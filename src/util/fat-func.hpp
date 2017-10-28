#ifndef FAT_FUNC_HPP
#define FAT_FUNC_HPP

/* A function pointer that can also be a method pointer.
 *
 * It is two pointers in size, hence "fat" in reference to pairs of pointers
 * being called fat pointers.
 *
 * TODO:
 * - If possible, create constructors that set the caller and data.
 * - Define (or delete) the copy/move constrctor/assignment operations.
 * - Also look into equality and comparison, although it might not be
 *   prefict because of inlining, finding copies should be enough.
 * - A Return(Arg0, Arg1, ...) syntax could replace Return, Arg0, Arg1, ...
 *   Is that cleaner? How would I even do that?
 * - call -> operator() would be more function like, but would it be clear?
 * - Look into the const methods, see if we can mix in constant pointers to
 *   the object. (Mimiced with good function design, low priority.)
 * - Should the assert in call be a recoverable error (a thrown exception)?
 */

#include <cassert>
#include <utility>



template<typename ReturnT, typename... Args>
class FatFunction
{
  template<ReturnT (*function)(Args...)>
  static inline ReturnT functionCaller(void * /*unused*/, Args&&... args)
  {
    return function(std::forward<Args>(args)...);
  }

  template<class ClassT, ReturnT (ClassT::*method)(Args...)>
  static inline ReturnT methodCaller(void * object, Args&&... args)
  {
    return (static_cast<ClassT *>(object)->*method)
           (std::forward<Args>(args)...);
  }

  // The const would be cast away regardless.
  mutable void * data;
  ReturnT (*caller)(void *, Args&&...);

public:
  FatFunction() :
    data(nullptr), caller(nullptr)
  {}

  template<ReturnT (*function)(Args...)>
  FatFunction() :
    data(nullptr), caller(functionCaller<function>)
  {}

  template<typename ClassT, ReturnT (ClassT::*method)(Args...)>
  FatFunction(ClassT * object) :
    data(object), caller(methodCaller<ClassT, method>)
  {}

  template<ReturnT (*function)(Args...)>
  inline void set(void)
  {
    data = nullptr;
    caller = functionCaller<function>;
  }

  template<typename ClassT, ReturnT (ClassT::*method)(Args...)>
  inline void set(ClassT * object)
  {
    data = object;
    caller = methodCaller<ClassT, method>;
  }

  ReturnT operator() (Args&&... args) const
  {
    assert(nullptr != caller);
    return caller(data, std::forward<Args>(args)...);
  }

  bool operator== (FatFunction<ReturnT, Args...> const & other)
  {
    return data == other.data && caller == other.caller;
  }

  bool operator!= (FatFunction<ReturnT, Args...> const & other)
  {
    return !this->operator==(other);
  }

  FatFunction(FatFunction<ReturnT, Args...> const &) = default;
  FatFunction(FatFunction<ReturnT, Args...> &&) = default;
  FatFunction<ReturnT, Args...> &
      operator=(FatFunction<ReturnT, Args...> const &) = default;
  FatFunction<ReturnT, Args...> &
      operator=(FatFunction<ReturnT, Args...> &&) = default;
};

#endif//FAT_FUNC_HPP
