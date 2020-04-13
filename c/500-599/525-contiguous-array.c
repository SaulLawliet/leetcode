/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 把0看作-1, 累加数组内的值, 然后以累加值为Key, 数组下标为Value, 保存起来.
 * 每次遇到已存在的Key时, 通过下标更新一下最大长度.
 */

#include <stdlib.h> /* malloc(), free() */
#include "c/data-structures/array.h"
#include "c/test.h"

int findMaxLength(int *nums, int numsSize) {
  int n = 2 * numsSize + 1;
  int *indexes = malloc(sizeof(int) * n);
  for (int i = 0; i < n; i++)
    indexes[i] = -2;
  indexes[numsSize] = -1;

  int max = 0, sum = 0;
  for (int i = 0; i < numsSize; i++) {
    sum += nums[i] == 0 ? -1 : 1;
    int *p = &indexes[sum+numsSize];
    if (*p == -2)
      *p = i;
    else if (i - *p > max)
      max = i - *p;
  }
  free(indexes);
  return max;
}

void test(int expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);
  EXPECT_EQ_INT(expect, findMaxLength(arrayValue(e), arraySize(e)));
  arrayFree(e);
}

int main(void) {
  test(2, "[0,1]");
  test(2, "[0,1,0]");

  test(6, "[0,0,1,0,0,0,1,1]");

  return testOutput();
}
