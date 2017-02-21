#ifndef MARC_HPP
#define MARC_HPP

/* MaRC - MApping Refrence Counter
 * Pernounced: "Mark"
 *
 * MaRC is a kind of smart pointer.
 *
 * The reference counter part is similar to most reference counters. The
 * number of MaRCs that reference an object is counted and if that count goes
 * to zero then the object is unloaded.
 *
 * However you don't provide the MaRC with an object to point to. Instead
 * you give it a seperate key value which is mapped to the value used. If the
 * key refers to an existing object, then a the MaRC will point to it
 * instead of creating a new value.
 *
 * The simplest case is to define a DataT that has a constructor DataT(KeyT).
 * You can leave out the final mapping argument and take care of any work
 * for loading and unloading in the constructor and deconstructor. If you
 * require more control you can define your own function to create MaRCData
 * objects with.
 *
 * The loaded data is mutable, however if you intend to change it keep in mind
 * that it will be unloaded and re-loaded with no regard for the old value if
 * the reference count goes to zero.
 *
 * TODO: Very much not finished. Don't use this just yet.
 *     * MaRC::ReadOnly: Forbids write operations (const data)?
 *       In the case of immutable data, it would have the same interface.
 *       I think some helpers from <type_traits> would do it.
 *   typedef ... ThisType;
 *   typedef std::conditional<
 *       std::is_const<ThisType>, ThisType, ThisType const>::type ReadOnly
 *       Should MaRC DataT ever be mutable?
 *
 *     * Should there be a way to force unique templates?
 *     * Get it passing all the tests. There are still a few that don't.
 */

#include <map>



template<typename KeyT, typename DataT>
struct MaRCData;

template<typename KeyT, typename DataT>
MaRCData<KeyT, DataT> * constructMap (KeyT key);

template<typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT) = constructMap<KeyT, DataT> >
class MaRC
{
private:
  static std::map<KeyT, MaRCData<KeyT, DataT> *> loadedData;

  MaRCData<KeyT, DataT> * data;

  void unbindData();

protected:
public:
  MaRC (KeyT key);
  /* Create a new MaRC from the key.
   * Params: The key that give the data according to mapping.
   * Effect: If the data is not loaded, it will be with mapping.
   */

  virtual ~MaRC ();

  MaRC (MaRC<KeyT, DataT, mapping> const &);
  MaRC (MaRC<KeyT, DataT, mapping> &&);
  MaRC<KeyT, DataT, mapping> &
      operator== (MaRC<KeyT, DataT, mapping> const &);
  MaRC<KeyT, DataT, mapping> &
      operator== (MaRC<KeyT, DataT, mapping> &&);
  DataT & operator* () const;
  DataT * operator-> () const;



  // For "I have no idea what is wrong" problems only.
#if DEBUG
  static std::map<KeyT, MaRCData<KeyT, DataT> *> & cheat ()
  {
    return loadedData;
  }
#endif//DEBUG
};

#include "marc.tpp"

#endif//MARC_HPP
