/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 中等难度的题? 其实很简单
 * 维护一个sum变量, 再循环计算一次即可
 */

#include <stdbool.h>
#include "c/data-structures/array.h"
#include "c/test.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *sumEvenAfterQueries(int *nums, int numsSize, int **queries, int queriesSize, int *queriesColSize, int *returnSize) {
  *returnSize = 0;
  int *returnArray = malloc(sizeof(int) * queriesSize);

  int sum = 0;
  for (int i = 0; i < numsSize; i++) {
    if (nums[i] % 2 == 0)
      sum += nums[i];
  }

  int v1, v2;
  bool even1, even2;
  for (int i = 0; i < queriesSize; i++) {
    v1 = nums[queries[i][1]];
    v2 = queries[i][0];
    even1 = v1 % 2 == 0;
    even2 = v2 % 2 == 0;

    if (even1) {
      if (even2) {
        sum += v2;  // 偶, 偶: sum + 第二个数
      } else {
        sum -= v1;  // 偶, 奇: sum - 第一个数
      }
    } else {
      if (!even2) {
        sum += v1 + v2;  // 奇, 奇: sum + 第一个数 + 第二个数
      }
    }

    nums[queries[i][1]] += v2;
    returnArray[(*returnSize)++] = sum;
  }

  return returnArray;
}

void test(const char *expect, const char *nums, const char *queries) {
  arrayEntry *e1 = arrayParse1D(nums, ARRAY_INT);
  arrayEntry *e2 = arrayParse2D(queries, ARRAY_INT);

  int returnSize;
  int *returnArray = sumEvenAfterQueries(arrayValue(e1), arraySize(e1), arrayValue(e2),
                                         arrayRow(e2), arrayCols(e2), &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(returnArray, returnSize, ARRAY_INT));

  arrayFree(e2);
  arrayFree(e1);
}

int main(void) {
  test("[8,6,2,4]", "[1,2,3,4]", "[[1,0],[-3,1],[-4,0],[2,3]]");

  return testOutput();
}
