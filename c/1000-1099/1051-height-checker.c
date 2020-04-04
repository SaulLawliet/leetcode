/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 看了好几遍也没看懂题目的意思, 直到看了第一条提示,
 * 竟然要跟有序的数组对比, 不同数字的个数...
 */

#include <stdlib.h> /* malloc(), free(), qsort() */
#include <string.h> /* memcpy() */
#include "c/data-structures/array.h"
#include "c/test.h"
#include "c/tools/compare.h"

int heightChecker(int *heights, int heightsSize) {
  int *p = malloc(sizeof(int) * heightsSize);
  memcpy(p, heights, sizeof(int) * heightsSize);
  qsort(p, heightsSize, sizeof(int), compare_ints);

  int move = 0;
  for (int i = 0; i < heightsSize; i++) {
    if (heights[i] != p[i]) {
      ++move;
    }
  }
  free(p);
  return move;
}

void test(int expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);

  EXPECT_EQ_INT(expect, heightChecker(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(3, "[1,1,4,2,1,3]");

  return testOutput();
}
