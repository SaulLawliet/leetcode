/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "c/algorithms/sort.h"
#include <stdlib.h> /* malloc() */
#include <string.h> /* memcpy() */
#include "c/data-structures/array.h"
#include "c/test.h"

typedef enum SORT_TYPE {
  INSERTION, MERGE, QUICK
} SortType;

void test(SortType type, int* expect, int* actual, int size) {
  switch (type) {
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

  EXPECT_EQ_STRING_AND_FREE(arrayToString1D(expect, size, ARRAY_INT),
                            arrayToString1D(actual, size, ARRAY_INT));
}

int* copy(int a[], int size) {
  int *rt = malloc(sizeof(int) * size);
  memcpy(rt, a, sizeof(int) * size);
  return rt;
}

int main(void) {
  int size = 6;
  int actual[] = {34, 8, 64, 51, 32, 21};
  int expect[] = {8, 21, 32, 34, 51, 64};

  test(INSERTION, copy(expect, size), copy(actual, size), size);
  test(MERGE, copy(expect, size), copy(actual, size), size);
  test(QUICK, copy(expect, size), copy(actual, size), size);

  return testOutput();
}
