#ifndef MARC_TPP
#define MARC_TPP

/* The implementation of the MaRC template class and some of its related
 * helpers. See header for details.
 */

#include <cassert>
#include <utility>



//#define DEFINE_MARC(name, ...) typedef MaRC<__VA_ARGS__> name
/* The __VA_ARGS__ thing is to let KeyT and DataT contain commas and to make
 * the function pointer optional. It is not a huge macro, but I think it
 * might help.
 */



template<typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
std::map<KeyT, MaRCData<KeyT, DataT> *>
MaRC<KeyT, DataT, mapping>::loadedData;



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
template<typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
MaRC<KeyT, DataT, mapping>::MaRC (KeyT key) :
  data(nullptr)
{
  if (0 != loadedData.count(key))
  {
    data = (loadedData[key]);
    ++data->useCount;
    return;
  }

  MaRCData<KeyT, DataT> * newData = mapping(key);

#if DEBUG
  assert(nullptr != newData);
  assert(0 == newData->useCount);
  assert(key == newData->key);
#endif

  loadedData.insert(std::make_pair(key, newData));
  data = newData;
  ++data->useCount;
};



template<typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
MaRC<KeyT, DataT, mapping>::MaRC (
    MaRC<KeyT, DataT, mapping> const & other) :
  data(other.data)
{
  ++data->useCount;
}

template<typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
MaRC<KeyT, DataT, mapping>::MaRC (
    MaRC<KeyT, DataT, mapping> && other) :
  data(other.data)
{
  ++data->useCount;
}

template<typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
MaRC<KeyT, DataT, mapping>::~MaRC ()
{
  unbindData();
}

template<typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
void MaRC<KeyT, DataT, mapping>::unbindData ()
{
  --data->useCount;
  if (0 == data->useCount)
  {
#if DEBUG
    assert(1 == loadedData.erase(data->key));
#else
    loadedData.erase(data->key);
#endif
    delete data;
  }
}

template<typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
MaRC<KeyT, DataT, mapping> &
MaRC<KeyT, DataT, mapping>::operator== (
    MaRC<KeyT, DataT, mapping> const & other)
{
  if (data != other.data)
  {
    unbindData();
    data = other.data;
    ++data->useCount;
  }
  return *this;
}

template<typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
MaRC<KeyT, DataT, mapping> &
MaRC<KeyT, DataT, mapping>::operator== (
    MaRC<KeyT, DataT, mapping> && other)
{
  if (data != other.data)
  {
    unbindData();
    data = other.data;
    ++data->useCount;
  }
  return *this;
}

template<typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
DataT & MaRC<KeyT, DataT, mapping>::operator* () const
{
  return data->coreData;
}

template<typename KeyT, typename DataT,
    MaRCData<KeyT, DataT> * (*mapping)(KeyT)>
DataT * MaRC<KeyT, DataT, mapping>::operator-> () const
{
  return &data->coreData;
}

#endif//MARC_TPP
