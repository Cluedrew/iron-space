#ifndef DATA_LIBRARY_HPP
#define DATA_LIBRARY_HPP

/* A base for a store of data. It prepares data and stores it according to a
 * key value. This will be kept as long as references to the data exist.
 *
 * KeyT: Look-Up type, ?should be orderable.
 * DataT: Stored type, it must be possible to generate one from KeyT.
 *
 * TODO: Not finished, document use as well as filling in the implementation.
 *     * Consider adding a third ID template argument. I tested it (on a small
 *       scale) and the static varable is different for each template. But
 *       that means we can only have one instance for each set of types. A
 *       third unused argument would avoid collitions.
 *     * Move prepareData to a different template class which is specialized
 *       to implement the loading.
 */

#include <map>



template<typename KeyT, typename DataT>
class DataLibrary;

template<typename KeyT, typename DataT>
class DataLibraryLoader
{
public:
  typedef typename DataLibrary<KeyT, DataT>::AnnotatedData AnnotatedData;
  static AnnotatedData * loadData (KeyT key);
};

template<typename KeyT, typename DataT>
class DataLibrary
{
private:
public:
  // Wrapper around the internal data, with reference counter.
  struct AnnotatedData
  {
    KeyT key;
    unsigned int useCount;
    DataT coreData;
  };

public:
  // class ConstDataPointer ???
  // The difference would be the constness you get when you dereference the
  // object. Sort of like pointers. [Const]DataPointer?

  // Reference to internal data type.
  class DataPointer
  {
  private:
    AnnotatedData * data;

  protected:
  public:
    DataPointer (AnnotatedData *);
    DataPointer (DataPointer const &);
    DataPointer (DataPointer &&);
    virtual ~DataPointer ();

    DataPointer & operator== (DataPointer const &);
    DataPointer & operator== (DataPointer &&);
    DataT & operator* () const;
    DataT * operator-> () const;
  };

  /* I think this might be too much. At least for now.
  class ConstDataPointer
  {
  private:
    AnnotatedData const * data;

  protected:
  public:
    ConstDataPointer (AnnotatedData const *);
    ConstDataPointer (ConstDataPointer const &);
    ConstDataPointer (ConstDataPointer &&);
    ConstDataPointer (DataPointer const &);
    ConstDataPointer (DataPointer &&);
    virtual ~ConstDataPointer ();

    ConstDataPointer operator== (ConstDataPointer const &);
    ConstDataPointer operator== (ConstDataPointer &&);
    DataT const & operator* () const;
    DataT const * operator-> () const;
  };*/

private:
  static std::map<KeyT, AnnotatedData *> loadedData;

protected:
  // If we use a sub-template instead:
  typedef DataLibraryLoader<KeyT, DataT> Loader;

  //static virtual AnnotatedData * loadData(KeyT) =0;
  /* Function to overload. It must be defined to create a dynamic
   * AnnotatedData object from a KeyT.
   * Params: Key value to generate the data from.
   * Effect: Prepare the data.
   * Return: Pointer to the new AnnotatedData. key and useCount fields are
   *   overwritten.
   */

public:
  static DataPointer get(KeyT);
  /* Get a DataPointer for the key, preparing it if nessary.
   * Params: Key value.
   * Effect: Prepare the data if it is not already.
   * Return: A DataPointer to the data.
   */
};



#include "data-library.tpp"

#endif//DATA_LIBRARY_HPP
