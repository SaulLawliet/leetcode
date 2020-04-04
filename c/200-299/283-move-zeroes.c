/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 冒泡排序的思路来解即可.
 */

#include "c/data-structures/array.h"
#include "c/test.h"

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void moveZeroes(int *nums, int numsSize) {
  for (int i = 0, j = 0; i < numsSize; i++) {
    if (nums[i] != 0) {
      swap(&nums[i], &nums[j++]);
    }
  }
}

void test(const char *expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);
  moveZeroes(arrayValue(e), arraySize(e));

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString(e));

  arrayFree(e);
}

int main(void) {
  test("[1,3,12,0,0]", "[0,1,0,3,12]");

  return testOutput();
}
