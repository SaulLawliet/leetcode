/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 排序后, 问题就简单多了.
 */

#include <stdlib.h> /* qsort() */
#include "c/data-structures/array.h"
#include "c/test.h"
#include "c/tools/compare.h"

int countElements(int *arr, int arrSize) {
  if (arrSize == 0) return 0;

  qsort(arr, arrSize, sizeof(int), compare_ints);

  int count = 0;
  int lastCount = 1;
  for (int i = 1; i < arrSize; i++) {
    if (arr[i] == arr[i - 1]) {
      ++lastCount;
      continue;
    }
    if (arr[i] == arr[i - 1] + 1) {
      count += lastCount;
    }
    lastCount = 1;
  }

  return count;
}

void test(int expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);

  EXPECT_EQ_INT(expect, countElements(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(2, "[1,2,3]");
  test(0, "[1,1,3,3,5,5,7,7]");
  test(3, "[1,3,2,3,5,0]");
  test(2, "[1,1,2,2]");

  return testOutput();
}
