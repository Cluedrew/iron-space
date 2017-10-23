#ifndef CALL_LIST_HPP
#define CALL_LIST_HPP

/* Define a list of function calls.
 *
 * It was going to use (well does) FatFunction directly, but I think it
 * doesn't take much more work to implement it over all callables (say,
 * regular function pointers). So that might change soon.
 */



// The actual loop over them thing would be special cased for when they
// don't return anything.
template<typename ReturnT, typename... Args>
class GroupCall
{
  using AllReturnT = _Some_Container_<ReturnT>;
  using FunctionT = FatFunction<ReturnT, Args...>;

  static AllReturnT callAll(_Some_Container_<FunctionT> funcs, Args... args)
  {
    AllReturnT ret;
    for (FunctionT func : funcs)
      ret.insert(func(args...));
    return ret;
  }
}
// I don't think this is how this parial template specialization would work.
template<void, typename... Args>
class GroupCall<void, Args...>
{
  using AllReturnT = void;
  using FunctionT = FatFunction<void, Args...>;

  static AllReturnT callAll(_Some_Container_<FunctionT> funcs, Args... args)
  {
    for (FunctionT func : funcs) func(args...);
  }
}

template<typename ReturnT, typename... Args>
class CallList
{
public:
  using ThisGroupCall = GroupCall<ReturnT, Args...>;
  using AllReturnT = ThisGroupCall::AllReturnT;
  using FunctionT = ThisGroupCall::FunctionT;

private:
  _Some_Container_<ThisGroupCall::FunctionT> calls;
public:

  AllReturnT callAll(Args... args)
  // Does not forward arguments, it can't as it makes mutible calls with them.
  {
    return ThisGroupCall::callAll(calls, args...);
  }

  void insert(FunctionT call)
  {
    calls.insert(call);
  }

  void remove(FunctionT call)
  {
    calls.remove(call);
  }
}

#endif//CALL_LIST_HPP
