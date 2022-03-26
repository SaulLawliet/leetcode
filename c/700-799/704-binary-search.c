/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 好久没写二分查找了, 虽然道理都懂, 但写起来却需要借助测试用例
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int search(int *nums, int numsSize, int target) {
  int p = 0, q = numsSize;
  while (p < q) {
    int m = (q + p) / 2;
    if (target == nums[m]) {
      return m;
    } else if (target < nums[m]) {
      q = m;
    } else {
      p = m + 1;
    }
  }
  return -1;
}

void test(int except, char *nums, int target) {
  arrayEntry *e = arrayParse1D(nums, ARRAY_INT);

  EXPECT_EQ_INT(except, search(arrayValue(e), arraySize(e), target));

  arrayFree(e);
}

int main(void) {
  test(4, "[-1,0,3,5,9,12]", 9);
  test(-1, "[-1,0,3,5,9,12]", 2);

  test(0, "[5]", 5);

  return testOutput();
}
