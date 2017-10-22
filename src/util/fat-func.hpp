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
 * - A Return(Arg0, Arg1, ...) syntax could replace Return, Arg0, Arg1, ...
 *   Is that cleaner? How would I even do that?
 * - call -> operator() would be more function like, but would it be clear?
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

  // Can I also create setting constructors?
  // The big five might all work with the defaults.

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

  ReturnT call(Args&&... args) const
  {
    // Would an exception be a better way of handling this?
    // throw UnsetFatFunctionError?
    assert(nullptr != caller);
    return caller(data, std::forward<Args>(args)...);
  }
};

#endif//FAT_FUNC_HPP
