#ifndef DATA_LIBRARY_HPP
#define DATA_LIBRARY_HPP

/* A base for a store of data. It prepares data and stores it according to a
 * key value. This will be kept as long as references to the data exist.
 *
 * KeyT: Look-Up type, ?should be orderable.
 * DataT: Stored type, it must be possible to generate one from KeyT.
 *
 * TODO: Not finished, document use as well as filling in the implementation.
 */

#include <map>



template<typename KeyT, typename DataT>
class DataLibrary
{
private:
  // Wrapper around the internal data, with reference counter.
  struct AnnotatedData
  {
    KeyT key;
    unsigned int useCount;
    DataT coreData;
  };

public:
  // class ConstDataReference ???
  // The difference would be the constness you get when you dereference the
  // object. Sort of like pointers. [Const]DataPointer?

  // Reference to internal data type.
  class DataReference
  {
  private:
    AnnotatedData & data

  protected:
  public:
    DataReference (AnnotatedData *);
    DataReference (DataReference const &);
    DataReference (DataReference &&);
    virtual ~DataReference ();

    DataReference operator== (DataReference const &) = delete;
    DataReference operator== (DataReference &&) = delete;
    DataT & operator* ();
    DataT const & operator* () const;
    DataT * operator-> ();
    DataT const * operator-> () const;
  };

private:
  std::map<std::string, AnnotatedData *> loadedData;

protected:
  AnnotatedData * prepareData(KeyT) =0;
  /* Function to overload. It must be defined to create a DataPack
   * from a KeyT
   * Params: Key value to generate the data from.
   * Effect: Prepare the data.
   * Return: Pointer to the new DataPack.
   */

public:
  DataReference get(KeyT);
  /* Get a DataReference for the key, preparing it if nessary.
   * Params: Key value.
   * Effect: Prepare the data if it is not already.
   * Return: A DataReference to the data.
   */
};

#ifndef DATA_LIBRARY_TPP
#define DATA_LIBRARY_TPP

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

template<typename KeyT, typename DataT>
DataLibrary<KeyT, DataT>::DataReference::DataReference (AnnotatedData * data) :
  data(*data)
{
  ++data->useCount;
}

template<typename KeyT, typename DataT>
DataLibrary<KeyT, DataT>::DataReference::~DataReference ()
{
  --data->useCount;
  if (0 == data->useCount)
  {
    /* How do we remove it from the collection?
     * (If we can template a static (which comes out different for each
     * instance) than we could reference that directly.
     */
     delete data;
  }
}

//TEMPLATE_ARGS template<typename KeyT, typename DataT>
//DATALIB_PREFIX DataLibrary<KeyT, DataT>

//TWRAP_BASE(rettype) TEMPLATE_ARGS rettype DATALIB_PREFIX
//TWRAP_XTOR() TWRAP_BASE()
//TWRAP(rettype) TWRAP_BASE(DATALIB_PREFIX::rettype)

#endif//DATA_LIBRARY_TPP

#endif//DATA_LIBRARY_HPP
