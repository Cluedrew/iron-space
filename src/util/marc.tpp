#ifndef MARC_TPP
#define MARC_TPP

/* The implementation of the MaRC template class and some of its related
 * helpers. See header for details.
 */

//#include <cassert>
#include <utility>



//#define DEFINE_MARC(name, ...) typedef MaRC<#name, __VA_ARGS__> name
/* The __VA_ARGS__ thing is to let KeyT and DataT contain commas and to make
 * the function pointer optional. It is not a huge macro, but I think it
 * might help.
 */



template<typename KeyT, typename DataT>
struct MaRCData
{
  KeyT const key;
  unsigned int useCount;
  DataT coreData;

  template<typename... Args>
  MaRCData (KeyT key, Args&&... args) :
    key(key), useCount(0), coreData(std::forward<Args>(args)...)
  {}
};

template<typename KeyT, typename DataT>
MaRCData<KeyT, DataT> * constructMap (KeyT key)
{
  return new MaRCData<KeyT, DataT>(key, key);
}



// see header
template<char ...id, typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
MaRC<id, KeyT, DataT, mapping>::MaRC (KeyT key) :
  data(nullptr)
{
  if (0 != loadedData.count(key))
  {
    data = (loadedData[key]);
    ++data->useCount;
    return;
  }

  MaRCData<KeyT, DataT> * newData = mapping(key);

  // Perhaps I should wrap these in #if DEBUG
  //assert(nullptr != newData);
  //assert(0 == newData->useCount);
  //assert(key == newData->key);

  loadedData.insert(std::make_pair(key, newData));
  data = newData;
};



template<char ...id, typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
MaRC<id, KeyT, DataT, mapping>::MaRC (
    MaRC<id, KeyT, DataT, mapping> const & other) :
  data(other.data)
{
  ++data->useCount;
}

template<char ...id, typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
MaRC<id, KeyT, DataT, mapping>::MaRC (
    MaRC<id, KeyT, DataT, mapping> && other) :
  data(other.data)
{
  ++data->useCount;
}

template<char ...id, typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
MaRC<id, KeyT, DataT, mapping>::~MaRC ()
{
  unbindData();
}

// I could macro this to force it inline.
template<char ...id, typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
void MaRC<id, KeyT, DataT, mapping>::unbindData ()
{
  --data->useCount;
  if (0 == data->useCount)
  {
    loadedData.erase(data->key);
    delete data;
  }
}

template<char ...id, typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
MaRC<id, KeyT, DataT, mapping> &
MaRC<id, KeyT, DataT, mapping>::operator== (
    MaRC<id, KeyT, DataT, mapping> const & other)
{
  if (data != other.data)
  {
    unbindData();
    data = other.data;
    ++data->useCount;
  }
  return *this;
}

template<char ...id, typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
MaRC<id, KeyT, DataT, mapping> &
MaRC<id, KeyT, DataT, mapping>::operator== (
    MaRC<id, KeyT, DataT, mapping> && other)
{
  if (data != other.data)
  {
    unbindData();
    data = other.data;
    ++data->useCount;
  }
  return *this;
}

template<char ...id, typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
DataT & MaRC<id, KeyT, DataT, mapping>::operator* () const
{
  return data->coreData;
}

template<char ...id, typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
DataT * MaRC<id, KeyT, DataT, mapping>::operator-> () const
{
  return &data->coreData;
}

#endif//MARC_TPP
