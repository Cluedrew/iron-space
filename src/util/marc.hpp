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
 */

#include <map>



template<typename KeyT, typename DataT, char * id>
class MaRC
{
private:
  struct AnnotatedData
  {
    KeyT key;
    unsigned int useCount;
    DataT coreData;
  };

  static std::map<KeyT, AnnotatedData *> loadedData;
  friend class MaRC_Loader<KeyT, DataT, id>;

  AnnotatedData * data;

  void unbindData;

protected:
public:
  MaRC (KeyT key);

  virtual ~MaRC ();

  MaRC (MaRC const &);
  MaRC (MaRC &&);
  MaRC & operator== (MaRC const &);
  MaRC & operator== (MaRC &&);
  MaRC & operator*  () const;
  MaRC * operator-> () const;
};

#endif//MARC_HPP
