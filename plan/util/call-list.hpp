#ifndef CALL_LIST_HPP
#define CALL_LIST_HPP

/* Define a list of function calls.
 *
 * It was going to use (well does) FatFunction directly, but I think it
 * doesn't take much more work to implement it over all callables (say,
 * regular function pointers). So that might change soon.
 *
 * Debating about the container type, it a set might be better, except that
 * it makes colisions on the output disappear. The vector solution acts as a
 * multiset of sorts.
 */

template<typename T>
using VectorWrap = std::conditional<std::is_void<T>::type, T, std::vector<T>>;

template<typename ReturnT, typename... Args>
class CallList
{
public:
  using FunctionT = FatFunction<ReturnT, Args...>;

private:
  std::vector<FunctionT> funcs;
public:

  VectorWrap<ReturnT>::type callAll(Args... args);

  void insert(FunctionT func);
  void remove(FunctionT func);
};

#endif//CALL_LIST_HPP

// .tpp file.

template<typename ReturnT, typename... Args>
void CallList<ReturnT, Args...>::insert (FunctionT func)
{
  funcs.push_back(func);
}

template<typename ReturnT, typename... Args>
void CallList<ReturnT, Args...>::remove (FunctionT func)
{
  std::vector<FatFunction<ReturnT, Args...>>::const_iterator it;
  for (it = funcs.cbegin() ; it != funcs.cend() ; ++it)
  {
    if (*it == func)
    {
      funcs.erase(it);
      return;
    }
  }
}

template<typename ReturnT, typename... Args>
VectorWrap<ReturnT>::type CallList<ReturnT, Args...>(Args... args)
{
  return CallListHelper::callAll(funcs, args...);
}

template<typename ReturnT, typename... Args>
class CallListHelper
{
  static std::vector<ReturnT> callAll (
      std::vector<FatFunction<ReturnT, Args...>> const & funcs, Args... args)
  {
    std::vector<ReturnT> ret;
    ret.resurve(funcs.size());
    for (FatFunction<ReturnT, Args...> func : funcs)
      ret.push_back(func(args...));
    return ret;
  }
};

template<typename... Args>
class CallListHelper<void, Args...>
{
  static void callAll (
      std::vector<FatFunction<ReturnT, Args...>> const & funcs, Args... args)
  {
    for (FatFunction<void, Args...> func : funcs) func(args...);
  }
};
