#include <stdlib.h>  /* free() */
#include "sort.h"
#include "../data-structures/array.h"
#include "../test.h"

typedef enum SORT_TYPE {
  INSERTION, MERGE, QUICK
} SortType;

static void test(SortType type, int* expect, int* actual, int size) {
  switch(type) {
    case INSERTION:
      sortInsertion(actual, size);
      break;
    case MERGE:
      sortMerge(actual, size);
      break;
    case QUICK:
      sortQuick(actual, size);
      break;
  }

  EXPECT_EQ_STRING_AND_FREE(arrayToString(expect, size),
                            arrayToString(actual, size));

  free(actual);
}

int main(void) {
  int size = 6;
  int autual[] = {34, 8, 64, 51, 32, 21};
  int expect[] = {8, 21, 32, 34, 51, 64};

  test(INSERTION, expect, arrayCopy(autual, size), size);
  test(MERGE,     expect, arrayCopy(autual, size), size);
  test(QUICK,     expect, arrayCopy(autual, size), size);

  return testOutput();
}
