#ifndef MARC_TPP
#define MARC_TPP

/* The implementation of the MaRC class.
 */

#include <utility>



/* I was going to have a template class, as before, but then I realized that
 * a template function would also be fine (if specialation works there).
 * Of course if we go there maybe a function pointer would work better,
 * which means craming in another argument but it should be worth it.
 */

#define DEFINE_MARC(name, ...) \
typedef MaRC<#name, __VA_ARGS__> name
/* The actual template arguments would become (approx):
 * template<char * id, typename KeyT, typename DataT,
 *          AnnotatedData<KeyT, DataT> (*mapping)(KeyT)>
 * The __VA_ARGS__ thing is to let KeyT and DataT contain commas and to make
 * the function pointer optional.
 */


template<typename KeyT, typename DataT, char * id>
MaRC<KeyT, DataT, id>::AnnotatedData * loadMaRCData (KeyT key)
{
  MaRC<KeyT, DataT, id>::AnnotatedData * newData = new AnnotatedData{
    .key = key, .useCount = 0, .coreData = DataT(key)
  };
  return newData;
}

template<typename KeyT, typename DataT, char * id>
struct MaRC_Loader
{
  static MaRC<KeyT, DataT, id>::AnnotatedData * loadData (KeyT key)
  {
    MaRC<KeyT, DataT, id>::AnnotatedData * newData = new AnnotatedData{
      .key = key, .useCount = 0, .coreData = DataT(key)
    };
    return newData;
  }
};



// The TEMPLATE and TWRAP macros will go here, if I use them.
//#define TEMPLATE_ARGS template<typename KeyT, typename DataT, char * id>



template<typename KeyT, typename DataT, char * id>
MaRC<KeyT, DataT, id>::MaRC (KeyT key) :
  data(nullptr)
{
  if (0 != loadedData.count(key))
  {
    data = (loadedData[key]);
    return;
  }

  AnnotatedData * newData = MaRC_Loader<KeyT, DataT, id>::loadData(key);
  //assert(newData);
  newData->key = key;
  newData->useCount = 1;
  DataLibrary<KeyT, DataT>::loadedData.insert(std::make_pair(key, newData));
  data = newData;
};

template<typename KeyT, typename DataT, char * id>
MaRC<KeyT, DataT, id>::MaRC (MaRC const & other) :
  data(other.data)
{
  ++data->useCount;
}

template<typename KeyT, typename DataT, char * id>
MaRC<KeyT, DataT, id>::MaRC (MaRC && other) :
  data(other.data)
{
  ++data->useCount;
}

template<typename KeyT, typename DataT, char * id>
MaRC<KeyT, DataT, id>::~MaRC ()
{
  unbindData();
}

// I could macro this to force it inline.
template<typename KeyT, typename DataT, char * id>
void MaRC<KeyT, DataT, id>::unbindData ()
{
  --data->useCount;
  if (0 == data->useCount)
  {
    loadedData.erase(data->key);
    delete data;
  }
}

template<typename KeyT, typename DataT, char * id>
MaRC<KeyT, DataT, id>::operator== (MaRC<KeyT, DataT, id> const & other)
{
  if (data == other.data)
     return *this;

  unbindData();

  data = other.data;
  ++data->useCount;
  return *this;
}

template<typename KeyT, typename DataT, char * id>
MaRC<KeyT, DataT, id>::operator== (MaRC<KeyT, DataT, id> && other)
{
  if (data == other.data)
     return *this;

  unbindData();

  data = other.data;
  ++data->useCount;
  return *this;
}

template<typename KeyT, typename DataT, char * id>
DataT * MaRC<KeyT, DataT, id>::operator* () const
{
  return data->coreData;
}

template<typename KeyT, typename DataT, char * id>
DataT * MaRC<KeyT, DataT, id>::operator-> () const
{
  return &data->coreData;
}



// MACROS for creating new MaRC instances.
#define DECLARE_MARC(name, Ktype, Dtype) \
typedef MaRC<Ktype, Dtype, #name> name;

#define DEFINE_MARC(name, Ktype, Dtype) \
std::map<KeyT, MaRC<Ktype, Dtype, #name>::AnnotatedData *> \
MaRC<Ktype, Dtype, #name>::loadedData;

#define DEFINE_MARC_WITH_LOADER(name, Ktype, Dtype, loader) \
DEFINE_MARC(name, Ktype, Dtype)

#define DEFINE_MARC_LOADER(name, KeyType, DataType, keyName)

#endif//MARC_TPP
