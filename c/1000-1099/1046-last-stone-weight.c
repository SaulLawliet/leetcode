/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 排序后按照规则不断循环即可.
 */

#include <stdlib.h> /* qsort() */
#include "c/data-structures/array.h"
#include "c/test.h"
#include "c/tools/compare.h"

int lastStoneWeight(int *stones, int stonesSize) {
  qsort(stones, stonesSize, sizeof(int), compare_ints);

  for (stonesSize -= 2; stonesSize >= 0; stonesSize -= 2) {
    int x = stones[stonesSize], y = stones[stonesSize + 1];
    if (x != y) {
      stones[stonesSize++] = y - x;
      qsort(stones, stonesSize + 1, sizeof(int), compare_ints);
    }
  }
  return stonesSize == -1 ? stones[0] : 0;
}

void test(int expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);
  EXPECT_EQ_INT(expect, lastStoneWeight(arrayValue(e), arraySize(e)));
  arrayFree(e);
}

int main(void) {
  test(1, "[2,7,4,1,8,1]");

  test(2, "[1,3]");

  return testOutput();
}
