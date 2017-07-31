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
  /* Pre and post increment operators.
   */

  bool operator== (const ThisT & other) const
  { return data == other.data; }
  bool operator!= (const ThisT & other) const
  { return data != other.data; }

  class Const
  {
  private:
    // struct and public?
    T const ** data;

  protected:
  public:
    Const (T ** data = nullptr) : data(data) {}
    /* Create a new DoublePtr::Const from an primitive double pointer.
     * Params: Value to copy, null if omitted.
     */

    T const & operator*() const { return **data; }
    T const * operator->() const { return *data; }
    // Deference operator mean this acts as a T*.

    DoublePtr<T> & operator++ () { return ++data; }
    DoublePtr<T> operator++ (int) { return data++; }
    /* Pre and post increment operators.
     */
  };
};

#endif//DOUBLE_PTR_HPP
