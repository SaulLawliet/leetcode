/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 题目规定了时间复杂度为 O(log n) ，所以一定是二分法查找
 * 注意 mid 为奇数或偶数时，会有差异
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int singleNonDuplicate(int *nums, int numsSize) {
  int start = 0,
      end = numsSize - 1;
  while (start < end) {
    int mid = (start + end) / 2;
    if (mid % 2 == 0)
      mid--;
    if (nums[mid] == nums[mid + 1])
      end = mid - 1;
    else
      start = mid + 1;
  }
  return nums[start];
}

void test(int expect, const char *str) {
  arrayEntry *e = arrayParse1D(str, ARRAY_INT);

  EXPECT_EQ_INT(expect, singleNonDuplicate(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(2, "[1,1,2,3,3,4,4,8,8]");
  test(10, "[3,3,7,7,10,11,11]");

  return testOutput();
}
