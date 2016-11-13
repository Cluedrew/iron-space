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
// Put a type in the scope of the template. [Not so sure about this name.]
#define TTYPE(type) typename TEMPLATE_PREFIX::type
// Same as above, but type argument the scope of the class as well.
#define TWRAP_TYPE(type) TWRAP(typename TEMPLATE_PREFIX::type)

template<typename KeyT, typename DataT>
std::map<std::string, typename DataLibrary<KeyT, DataT>::AnnotatedData *>
DataLibrary<KeyT, DataT>::loadedData;
// TWRAP(std::map<std::string, TTYPE(AnnotatedData *)>)::loadedData



// see header
TWRAP_TYPE(DataPointer)::get (KeyT key)
{
  if (0 != loadedData.count(key))
    return DataPointer(loadedData[key]);

  AnnotatedData * newData = DataLibraryLoader<KeyT, DataT>::loadData(key);
  //assert(newData);
  newData->key = key;
  newData->useCount = 0;
  loadedData.insert(key, newData);
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
    (TTYPE(DataPointer) const & other)
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
    (TTYPE(DataPointer) && other)
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
#undef TWRAP

#undef TEMPLATE_PREFIX
#undef TEMPLATE_ARGS

#endif//DATA_LIBRARY_TPP

/* If I could make this work...
#define TWRAP(type)                                             \
TEMPLATE_ARGS                                                   \
#if #type[0] != '\0' && #type[0] == ':' && #type[1] == ':'      \
typename TEMPLATE_PREFIX type                                   \
#else                                                           \
type                                                            \
#endif                                                          \
TEMPLATE_PREFIX

Basically, it switches between the two current forms depending on the
  start of type, if it is :: then it adds the TEMPLATE_PREFIX.
Of course the next step would be to create a macro that defines the TWRAP
  macro so we can use it across files easily. Or even define a slightly
  seperate macro each time to avoid naming collitions.
I could even make this pretty, but it all depends on if you can embed
  preprocesser directives in macros and have them happen at that time.
*/
