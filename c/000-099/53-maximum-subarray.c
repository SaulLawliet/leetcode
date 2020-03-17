/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 题目要求时间复杂度O(n), 所以一定是一层循环.
 * 按照动态规划的思路, 手写一下计算过程, 代码就很好写啦.
 *
 * -2, 1, -3, 4, -1, 2, 1, -5, 4
 * -2
 *     1
 *        -2
 *            4
 *                3
 *                   5
 *                      6         <- 最大
 *                          1
 *                             5
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int maxSubArray(int *nums, int numsSize) {
  int max = nums[0], cur = nums[0];
  for (int i = 1; i < numsSize; i++) {
    cur = nums[i] + cur > nums[i] ? cur + nums[i] : nums[i];
    if (cur > max) max = cur;
  }
  return max;
}

void test(int expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);

  EXPECT_EQ_INT(expect, maxSubArray(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(6, "[-2,1,-3,4,-1,2,1,-5,4]");

  return testOutput();
}
