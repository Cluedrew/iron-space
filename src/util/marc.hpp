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
 * TODO: Very much not finished. Don't use this just yet.
 *     * MaRC::ReadOnly: Forbids write operations (const data)?
 */

#include <map>



template<typename KeyT, typename DataT>
struct MaRCData;

template<typename KeyT, typename DataT>
MaRCData<KeyT, DataT> * constructMap (KeyT key);

template<char ...id, typename KeyT, typename DataT,
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

  MaRC (MaRC<id, KeyT, DataT, mapping> const &);
  MaRC (MaRC<id, KeyT, DataT, mapping> &&);
  MaRC<id, KeyT, DataT, mapping> &
      operator== (MaRC<id, KeyT, DataT, mapping> const &);
  MaRC<id, KeyT, DataT, mapping> &
      operator== (MaRC<id, KeyT, DataT, mapping> &&);
  DataT & operator* () const;
  DataT * operator-> () const;
};

template<char * id, typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
std::map<KeyT, MaRCData<KeyT, DataT> *>
MaRC<id, KeyT, DataT, mapping>::loadedData;

#include "marc.tpp"

#endif//MARC_HPP
