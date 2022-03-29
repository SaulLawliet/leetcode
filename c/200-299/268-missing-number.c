/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * https://leetcode.com/problems/missing-number/
 * Q: 一个长度为n的数字, 元素是[0, n], 每个数字仅出现一次, 找到那个缺失的数字
 * 
 * 简单的加减运算就能找到缺失的数字
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int missingNumber(int *nums, int numsSize) {
  int n = 0;
  for (int i = 0; i < numsSize; i++) {
    n += i + 1 - nums[i];
  }
  return n;
}

void test(int except, const char *nums) {
  arrayEntry *e = arrayParse1D(nums, ARRAY_INT);

  EXPECT_EQ_INT(except, missingNumber(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(2, "[3,0,1]");
  test(2, "[0,1]");
  test(8, "[9,6,4,2,3,5,7,0,1]");

  return testOutput();
}
