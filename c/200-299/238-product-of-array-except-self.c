/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 题目已经给了很多提示: 禁止用除法、时间复杂度O(n)、空间复杂度O(1)、前缀/后缀.
 *
 * 把提示组合起来, 就是从前遍历一遍算一下乘积, 存到新的数组中.
 * 再从后向前遍历一下, 计算乘积继续保存到数组中.
 */

#include <stdlib.h> /* malloc() */
#include "c/data-structures/array.h"
#include "c/test.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *productExceptSelf(int *nums, int numsSize, int *returnSize) {
  *returnSize = numsSize;
  if (numsSize == 0) {
    return NULL;
  }

  int *rtn = malloc(sizeof(int) * numsSize);
  rtn[0] = 1;
  for (int i = 1; i < numsSize; i++) {
    rtn[i] = rtn[i-1] * nums[i-1];
  }

  int r = 1;
  for (int i = numsSize-1; i > 0; i--) {
    r *= nums[i];
    rtn[i-1] *= r;
  }

  return rtn;
}

void test(const char *expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);
  int returnSize;
  int *rtn = productExceptSelf(arrayValue(e), arraySize(e), &returnSize);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(rtn, returnSize, ARRAY_INT));
  arrayFree(e);
}

int main(void) {
  test("[24,12,8,6]", "[1,2,3,4]");

  return testOutput();
}
