#ifndef DOUBLE_PTR_HPP
#define DOUBLE_PTR_HPP

/* A double pointer, a pointer to a pointer, wrapped up so that it looks
 * like a single pointer.
 *
 * Being able to combine two pointers or pointer like objects might be nice.
 * template<typename T, typename TP = T*, typename TPP = TP*>
 * See the exparement afterwords.
 */

#include <utility>



template<typename DoubleT,
    typename SingleT = decltype(*std::declval<DoubleT>()),
    typename T = decltype(*std::declval<SingleT>()) >
struct DoublePtr
{
  using ThisT = DoublePtr<DoubleT, SingleT, T>;

  DoubleT data;

  DoublePtr () : data() {}
  DoublePtr (DoubleT data) : data(data) {}
  /* Create a new DoublePtr from an primitive double pointer.
   * Params: Value to copy, null if omitted.
   */

  T & operator*() { return **data; }
  T const & operator*() const { return **data; }
  SingleT & operator->() { return *data; }
  SingleT const & operator->() const { return *data; }
  // Deference operator mean this acts as a T*.

  ThisT & operator++ () { ++data; return *this; }
  ThisT operator++ (int) { ThisT retval = *this; data++; return retval; }
  // Pre and post increment operators.

  bool operator== (const ThisT & other) const
  { return data == other.data; }
  bool operator!= (const ThisT & other) const
  { return data != other.data; }
  // Equality is just passed down to data.
};

#endif//DOUBLE_PTR_HPP
