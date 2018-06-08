/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 就是简单的二分查找
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int searchInsert(int *nums, int numsSize, int target) {
  int a = 0, b = numsSize - 1;
  while (a <= b) {
    int i = (a + b) / 2;
    if (nums[i] > target) {
      b = i - 1;
    } else if (nums[i] < target) {
      a = i + 1;
    } else {
      return i;
    }
  }
  return a;
}

void test(int expect, const char *nums, int target) {
  arrayEntry *e = arrayParse1D(nums, ARRAY_INT);

  EXPECT_EQ_INT(expect, searchInsert(arrayValue(e), arraySize(e), target));

  arrayFree(e);
}

int main(void) {
  test(2, "[1,3,5,6]", 5);
  test(1, "[1,3,5,6]", 2);
  test(4, "[1,3,5,6]", 7);
  test(0, "[1,3,5,6]", 0);

  testOutput();
}
