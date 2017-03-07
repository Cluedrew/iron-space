#ifndef MARC_HPP
#define MARC_HPP

/* In progress upgrade to get MaRC::ReadOnly working. At this point it is
 * really just a design challenge. I think I can get it to work but the
 * complexity to do so is crazy.
 *
 * For every "MaRC Type" (defined on <KeyT, DataT, mapping>) there are
 * actually two types of MaRCs, one with read access the other with write.
 *
 * Currently, I don't have a use-case for this (other than communication)
 * because it still isn't very secure and changes can come in from other
 * sources. So implementation will wait.
 */

// The type actually used to store data.
template<typename KeyT, typename DataT>
struct MaRCData;

// Typedef to the function time that is used to create new MaRCData. FIX NAME
template<typename KeyT, typename DataT>
using createMaRCData MaRCData<KeyT, DataT> * (*)(KeyT);


// Example Mapping Function
template<typename KeyT, typename DataT>
MaRCData<KeyT, DataT> * constructMap (KeyT key);

template<typename KeyT, typename DataT, createMaRCData mapping>
class MaRCBase0
{
protected:
  std::map<KeyT, MaRCData<KeyT, DataT> *> loadedData;
  /* Shared storage in protected memory.
   * Nothing else, this exists only to wrap up the storage in such a way that
   * it is still protected.
   */
};

template<typename KeyT, typename DataT, typename AccessT,
   createMaRCData mapping>
class MaRCBase1 : public MaRCBase0<KeyT, DataT, mapping>
{
  /* As current implementation, except the return types of the
   * derefence operations are of AccessT. This allows us (by inheritance)
   * to share the same data between wrappers that access it differently.
   */
};

template<typename KeyT, typename DataT,
    createMaRCData mapping = constructMap<KeyT, DataT> >
class MaRC : public MaRCBase1<KeyT, DataT, DataT, mapping>
{
  // Forward the constructors.
  MaRC (KeyT key);

  using ConstDataT = std::conditional<std::is_const<DataT>::value,
      DataT, const DataT>::type;

  class ReadOnly : public MaRCBase1<KeyT, DataT, ConstDataT, mapping>
  {
    // Forward the constructors.

    // Assignment and constructon from the mutable types.
  };
};
/* I think I have to use inheritance both times, because both add something
 * to the definition. MaRC and MaRC::ReadOnly are the only types you should
 * ever use directly (except MaRCData when creating the createMaRCData
 * function).
 */

#endif//MARC_HPP
