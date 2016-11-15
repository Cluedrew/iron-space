#ifndef DATA_LIBRARY_TPP
#define DATA_LIBRARY_TPP

/* Template file for the DataLibrary, this handles all the boilerplate code
 * for saving, storing and referencing data after it has been loaded.
 */

#include <utility>



// I am considering using macros to cut down on the template boiler code:
// The design is still under flux. MACROS may not be great but the template
// definitions here are so complex they are even worse for readablity.
#define TEMPLATE_ARGS template<typename KeyT, typename DataT>
#define TEMPLATE_PREFIX DataLibrary<KeyT, DataT>

// Wrap the declaration of a template member with the args and prefix.
#define TWRAP(type) TEMPLATE_ARGS type TEMPLATE_PREFIX
// Put a type in the scope of the template.
#define TTYPE() typename TEMPLATE_PREFIX
// Same as TWRAP, but type argument is put in the scope of the template.
#define TWRAP_TYPE(type) TWRAP(TTYPE()::type)

template<typename KeyT, typename DataT>
std::map<KeyT, typename DataLibrary<KeyT, DataT>::AnnotatedData *>
DataLibrary<KeyT, DataT>::loadedData;
// The comma messes things up.
//TWRAP(std::map<KeyT, TTYPE()::AnnotatedData *>)::loadedData;



// see header
TWRAP_TYPE(DataPointer)::get (KeyT key)
{
  if (0 != loadedData.count(key))
    return DataPointer(loadedData[key]);

  AnnotatedData * newData = DataLibraryLoader<KeyT, DataT>::loadData(key);
  //assert(newData);
  newData->key = key;
  newData->useCount = 0;
  DataLibrary<KeyT, DataT>::loadedData.insert(std::make_pair(key, newData));
  return DataPointer(newData);
}



// DataPointer Constructors & Deconstrctor:
TWRAP()::DataPointer::DataPointer (AnnotatedData * data) :
  data(data)
{
  //assert(data);
  ++data->useCount;
}

TWRAP()::DataPointer::DataPointer (DataPointer const & other) :
  data(other.data)
{
  ++data->useCount;
}

TWRAP()::DataPointer::DataPointer (DataPointer && other) :
  data(other.data)
{
  ++data->useCount;
}

TWRAP()::DataPointer::~DataPointer ()
{
  --data->useCount;
  if (0 == data->useCount)
  {
    DataLibrary<KeyT, DataT>::loadedData.erase(data->key);
    delete data;
  }
}



// DataPointer Operators:
TWRAP_TYPE(DataPointer &)::DataPointer::operator==
    (TTYPE()::DataPointer const & other)
{
  if (data == other.data)
    return *this;

  --data->useCount;
  if (0 == data->useCount)
  {
    DataLibrary<KeyT, DataT>::loadedData.erase(data->key);
    delete data;
  }
  data = other.data;
  ++data->useCount;
  return *this;
}

TWRAP_TYPE(DataPointer &)::DataPointer::operator==
    (TTYPE()::DataPointer && other)
{
  if (data == other.data)
    return *this;

  --data->useCount;
  if (0 == data->useCount)
  {
    DataLibrary<KeyT, DataT>::loadedData.erase(data->key);
    delete data;
  }
  data = other.data;
  ++data->useCount;
  return *this;
}

TWRAP(DataT &)::DataPointer::operator* () const
{
  return data->coreData;
}

TWRAP(DataT *)::DataPointer::operator-> () const
{
  return &data->coreData;
}



#undef TWRAP_TYPE
#undef TTYPE
#undef TWRAP

#undef TEMPLATE_PREFIX
#undef TEMPLATE_ARGS

#endif//DATA_LIBRARY_TPP
