#ifndef MATH_HPP
#define MATH_HPP

/* Defines some simple math functions. This includes some that you could
 *   normally find in cstdlib & cmath, if you already have those headers
 *   use those instead.
 *
 * Unless otherwise given, T should be a numaric type.
 */



template<typename T>
T diff(T lhs, T rhs);
/* Return the unsigned difference between two values.
 * Params: The left & right hand sides.
 * Return: The difference, always a non-negative value.
 */

template<typename T>
T limitValue (T min, T actual, T max);
/* Limit the actual value so it is within the given (open) range.
 * Params: A minimum value, the actual value to be limited and the maximum.
 * Return: The middle of the three values.
 */

template<typename T>
T sqr (T num);
/* Square function.
 * Params: Some number.
 * Return: num * num
 */

#include "math.tpp"

#endif//MATH_HPP
