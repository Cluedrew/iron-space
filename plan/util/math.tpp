#ifndef MATH_TPP
#define MATH_TPP

// Implementation of math functions.



// see header
template<typename T>
T diff(T lhs, T rhs)
{
  return (lhs < rhs) ? rhs - lhs : lhs - rhs;
}

// see header
template<typename T>
T limitValue (T min, T actual, T max)
{
  if (actual < min)
    return min;
  else if (max < actual)
    return max;
  else
    return actual;
}

// see header
template<typename T>
T sqr (T num)
{
  return num * num;
}

#endif//MATH_TPP
