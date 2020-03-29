/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 利用原数组的空间, 下标从1开始, 往里填数.
 * 最后找到第一个不正确的值.
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int firstMissingPositive(int *nums, int numsSize) {
  if (numsSize == 0) return 1;

  int i = 0;
  while (i < numsSize) {
    /*  负数             超出范围                正确值               重复的正确值 */
    if (nums[i] <= 0 || nums[i] >= numsSize || nums[i] == i + 1 || nums[i] == nums[nums[i] - 1]) {
      i++;
    } else {
      int tmp = nums[nums[i] - 1];
      nums[nums[i] - 1] = nums[i];
      nums[i] = tmp;
    }
  }

  i = 0;
  while (i < numsSize && nums[i] == i + 1) i++;

  return i + 1;
}

void test(int expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);

  EXPECT_EQ_INT(expect, firstMissingPositive(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(3, "[1,2,0]");
  test(2, "[3,4,-1,1]");
  test(1, "[7,8,9,11,12]");

  test(1, "[]");
  test(2, "[1]");
  test(2, "[1,1]");

  return testOutput();
}
