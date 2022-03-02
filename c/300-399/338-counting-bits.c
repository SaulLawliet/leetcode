/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * Follow up:
 *  - It is very easy to come up with a solution with a runtime of O(n log n). Can you do it in linear time O(n) and possibly in a single pass?
 *
 * 如果是 O(n) 的时间复杂度, 那么思考方向应该类似于动态规划的做法
 * PS: 尝试引入变量, 来减少循环中的计算, 但效果不明显, 可能原因是: 相同的代码每次执行的时候可能会有不同的运行时间
 */

#include "c/data-structures/array.h"
#include "c/test.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *countBits(int n, int *returnSize) {
  *returnSize = n + 1;
  int *returnArray = malloc(sizeof(int) * *returnSize);
  returnArray[0] = 0;
  if (n >= 1) returnArray[1] = 1;
  int pow = 4;
  for (int i = 2; i < *returnSize; i++) {
    if (i < pow) {
      returnArray[i] = 1 + returnArray[i - pow / 2];
    } else {
      returnArray[i] = 1;
      pow <<= 1;
    }
  }
  return returnArray;
}

void test(const char *expect, int n) {
  int returnSize;
  int *returnArray = countBits(n, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(returnArray, returnSize, ARRAY_INT));
}

int main(void) {
  test("[0,1,1]", 2);
  test("[0,1,1,2,1,2]", 5);

  return testOutput();
}
