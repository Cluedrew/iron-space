#include "data-library.hpp"
#include <catch.hpp>

/* Testing for the DataLibrary template class. This is only for the shared
 * storing code. The loading of data into the library should be tested where
 * it is implemented.
 *
 * I also included demonstration tests to show how this is supposed to work
 * as it is a bit more complex.
 */


// ============== Test of DataLibraryLoader solution. [It compiled.]
#if 0
class IntIdLibrary : public DataLibrary<int, int>
{ AnnotatedData * loadData (int key) {return nullptr;} };

template<>
class DataLibraryLoader<int, int>
{
  typedef typename IntIdLibrary::AnnotatedData AnnotatedData;

  AnnotatedData * loadData (int key)
  {
    AnnotatedData * data = new AnnotatedData;
    data->coreData = key;
    return data;
  }
};



#else
// =============== Test of internal loadData solution. [It Compiled.]
class IntIdLibrary : public DataLibrary<int, int>
{
  AnnotatedData * loadData (int key)
  {
    AnnotatedData * data = new AnnotatedData;
    data->coreData = key;
    return data;
  }
};
#endif

/* So they both work. Is there any advantages to the DataLibraryLoader
 * method? Currently it just adds to the boiler plate.
 */



TEST_CASE("Tests for the DataLibrary Template Class", "[util]")
{
  // TODO: Demonstration Tests come first, then cover any corner cases.
  // Right now this is just forcing the hpp & tpp files to be read.
}
