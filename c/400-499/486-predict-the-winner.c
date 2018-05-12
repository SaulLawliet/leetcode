/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * v1: 递归. 很好理解
 * v2: 动态规划. 根据递归的结果, 很容易看出数据数据要如何存储
 *     (感觉动态规划就是将递归的中间变量存储起来)
 */

#include <stdbool.h>
#include "c/data-structures/array.h"
#include "c/test.h"

int max(int a, int b) { return a >= b ? a : b; }

int pick(int *nums, int beg, int end) {
  if (beg == end) return nums[beg];
  return max(nums[beg] - pick(nums, beg+1, end),
             nums[end] - pick(nums, beg, end-1));
}

bool PredictTheWinner_v1(int *nums, int numsSize) {
  return pick(nums, 0, numsSize - 1) >= 0;
}

bool PredictTheWinner_v2(int *nums, int numsSize) {
  int dp[numsSize][numsSize];
  for (int i = 0; i < numsSize; ++i)
    dp[i][i] = nums[i];

  for (int i = 1; i < numsSize; ++i)
    for (int j = i-1; j >= 0; --j)
      dp[i][j] = max(nums[j] - dp[i][j+1], nums[i] - dp[i-1][j]);

  return dp[numsSize-1][0] >= 0;
}

void test(bool expect, const char* str) {
  arrayEntry *e = arrayParse(str, ARRAY_INT);

  EXPECT_EQ_INT(expect, PredictTheWinner_v1(arrayValue(e), arraySize(e)));
  EXPECT_EQ_INT(expect, PredictTheWinner_v2(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(false, "[1, 5, 2]");
  test(true,  "[1, 5, 233, 7]");

  return testOutput();
}
