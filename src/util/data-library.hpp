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
  // Stored data.
  struct DataPack
  {
    KeyT key;
    unsigned int useCount;
    DataT coreData;
  };

public:
  // Reference to internal data type.
  class DataReference
  {
  private:
    DataPack & data

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
  std::map<std::string, DataPack *> loadedData;

protected:
  DataPack * prepareData(KeyT) =0;
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
}:

#endif//DATA_LIBRARY_HPP
