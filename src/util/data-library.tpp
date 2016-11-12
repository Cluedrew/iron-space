#ifndef DATA_LIBRARY_TPP
#define DATA_LIBRARY_TPP

/* Template file for the DataLibrary, this handles all the boilerplate code
 * for saving, storing and referencing data after it has been loaded.
 */



// I am considering using macros to cut down on the template boiler code:
// The design is still under flux. MACROS may not be great but the template
// definitions here are so complex they are even worse for readablity.
#define TEMPLATE_ARGS template<typename KeyT, typename DataT>
#define TEMPLATE_PREFIX DataLibrary<KeyT, DataT>

// Wrap the declaration of the template in the args and class prefix.
#define TWRAP(type) TEMPLATE_ARGS type TEMPLATE_PREFIX
// Same as above, but rettype is put in the scope of the class.
#define TWRAP_RET(innertype) TWRAP(TEMPLATE_PREFIX::innertype)
//efine TRETURN/TWRAP_INNER
// ...
#define TWRAP_REF(rettype) TWRAP(rettype)::DataReference
// ...
#undef TWRAP_REF
// ...
#undef TWRAP_RET
#undef TWRAP

template<typename KeyT, typename DataT>
std::map<std::string, AnnotatedData *> DataLibrary<KeyT, DataT>::loadedData;



template<typename KeyT, typename DataT>
DataLibrary<KeyT, DataT>::DataReference
DataLibrary<KeyT, DataT>::get (KeyT key)
{
  if (0 != loadedData.count(key))
    return DataReference(loadedData[key]);

  AnnotatedData * newData = prepareData(key);
  //assert(newData);
  newData->useCount = 0;
  loadedData.insert(key, newData);
  return DataReference(newData);
}



// DataReference Constructors & Deconstrctor:
template<typename KeyT, typename DataT>
DataLibrary<KeyT, DataT>::DataReference::DataReference (AnnotatedData * data) :
  data(data)
{
  //assert(data);
  ++data->useCount;
}

template<typename KeyT, typename DataT>
DataLibrary<KeyT, DataT>::DataReference::DataReference
    (DataReference const & other) :
  data(other.data)
{
  ++data->useCount;
}

template<typename KeyT, typename DataT>
DataLibrary<KeyT, DataT>::DataReference::DataReference
    (DataReference && other) :
  data(other.data)
{
  ++data->useCount;
}

template<typename KeyT, typename DataT>
DataLibrary<KeyT, DataT>::DataReference::~DataReference ()
{
  --data->useCount;
  if (0 == data->useCount)
  {
    DataLibrary<KeyT, DataT>::loadedData.erase(data->key);
    delete data;
  }
}



// DataReference Operators:
template<typename KeyT, typename DataT>
DataLibrary<KeyT, DataT>::DataT &
DataLibrary<KeyT, DataT>::DataReference::operator* ()
{
  return data->coreData;
}



#undef DATALIB_PREFIX
#undef TEMPLATE_ARGS

#endif//DATA_LIBRARY_TPP
