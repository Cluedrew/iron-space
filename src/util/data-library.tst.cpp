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
#if 1
class IntIdLibrary : public DataLibrary<int, int>
{ AnnotatedData * loadData (int key) {return nullptr;} };

template<>
struct DataLibraryLoader<int, int>
{
  typedef typename IntIdLibrary::AnnotatedData AnnotatedData;

  static AnnotatedData * loadData (int key)
  {
    AnnotatedData * data = new AnnotatedData;
    data->coreData = key;
    return data;
  }
};



#else
// =============== Test of internal loadData solution. [X static virtual X]
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

/* The DataLibraryLoader solution seems to work, where the internal one does
 * not. So I guess I will be using that one. But I would like to clean up its
 * use quite a bit if possible.
 */

typedef DataLibrary<char, int> LoadCounterLibrary;

template<>
struct DataLibraryLoader<char, int>
{
  typedef typename LoadCounterLibrary::AnnotatedData AnnotatedData;

  static int loadCount;

  static AnnotatedData * loadData (char key)
  {
    AnnotatedData * data = new AnnotatedData;
    data->coreData = loadCount++;
    return data;
  }
};

int DataLibraryLoader<char, int>::loadCount = 0;



TEST_CASE("Tests for the DataLibrary Template Class", "[util]")
{
  // TODO: Demonstration Tests come first, then cover any corner cases.
  // Right now this is just forcing the hpp & tpp files to be read.
  SECTION("Simple <int, int> test")
  {
    IntIdLibrary::DataPointer number = IntIdLibrary::get(3);
    REQUIRE( *number == 3 );
  }

  SECTION("Check timing of loads.")
  {
    LoadCounterLibrary::DataPointer zed = LoadCounterLibrary::get('z');
    REQUIRE( *zed == 0 );

    LoadCounterLibrary::DataPointer zee = LoadCounterLibrary::get('z');
    REQUIRE( *zee == 0 );

    {
      LoadCounterLibrary::DataPointer uu = LoadCounterLibrary::get('u');
      REQUIRE( *uu == 1 );
    }
    {
      LoadCounterLibrary::DataPointer uu = LoadCounterLibrary::get('u');
      REQUIRE( *uu == 2 );
    }
  }
}
