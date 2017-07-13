#include <stdlib.h>  /* free() */
#include "array.h"
#include "../test.h"

void testArray(int expectSize, const char* expectStr, const char* s) {
  size_t size;
  int *array = arrayNewByStr(s, &size);

  EXPECT_EQ_INT(expectSize, (int)size);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expectStr, arrayToString(array, size));

  free(array);
}

void testArrayRoundTrip(int expectSize, const char* s) {
  testArray(expectSize, s, s);
}

void testArrayCopy(const char* s) {
  size_t size;
  int *array1 = arrayNewByStr(s, &size);
  int *array2 = arrayCopy(array1, size);

  EXPECT_EQ_STRING_AND_FREE(arrayToString(array1, size),
                            arrayToString(array2, size));

  free(array1);
  free(array2);
}

void testArray2D(int expectRow, int expectCol, const char* expectStr, const char* s) {
  size_t row, col;
  int** arrays = array2DNewByStr(s, &row, &col);

  EXPECT_EQ_INT(expectRow, row);
  EXPECT_EQ_INT(expectCol, col);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expectStr, array2DToString(arrays, row, col));

  array2DFree((void**)arrays, row);
}

void testArray2DRoundTrip(int expectRow, int expectCol, const char* s) {
  testArray2D(expectRow, expectCol, s, s);
}

void testSArray(int expectSize, const char* expectStr, const char* s) {
  size_t size;
  char** strs = sarrayNewByStr(s, &size);

  EXPECT_EQ_INT(expectSize, size);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expectStr, sarrayToString(strs, size));

  array2DFree((void**)strs, size);
}

void testSArrayRoundTrip(int expectSize, const char* s) {
  testSArray(expectSize, s, s);

}

int main(void) {
  testArrayRoundTrip(3, "[2147483647, 0, -2147483648]");
  testArrayRoundTrip(7, "[-3, -2, -1, 0, 1, 2, 3]");
  testArray(0, "[]", "");
  testArray(3, "[-1, -2, -3]", "-1-2-----3");
  testArray(3, "[-1, -2, 3]", "-1-2----- 3");
  testArray(1, "[-1]", "[[[[-1]0]1]  5");
  testArray(3, "[2147483647, 0, -2147483648]", "0002147483647 -,*^@$ #, 000000 -2147483648");


  testArrayCopy("[1, 2, 3]");

  testArray2DRoundTrip(0, 0, "[]");
  testArray2DRoundTrip(3, 3, "[[1, 2, 3], [4, 5, 6], [7, 8, 9]]");
  testArray2D(3, 3, "[[1, 2, 3], [4, 5, 6], [7, 8, 9]]", "1 2 3 ] 4 5 6] 7 8 9");
  testArray2D(0, 0, "[]", "[[]]");
  testArray2D(0, 0, "[]", "[[], []]");
  testArray2D(1, 1, "[[1]]", "[[1], [   ]]");


  testSArrayRoundTrip(0, "[]");
  testSArrayRoundTrip(1, "[1]");
  testSArrayRoundTrip(3, "[Hello World., 1234567890, !@#$%^&*()]");
  testSArray(0, "[]", "");
  testSArray(1, "[1]", "1");
  testSArray(5, "[12  3, 345, 567, 111  123123, 1]",
             "[      12  3    , , ,, 345    , 567   ,      111  123123 ,   1]  222");

  return testOutput();
}
