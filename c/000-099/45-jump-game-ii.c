/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * v1: 先想到的是动态规划, 结果超时.
 *
 * v2: 调整思路后, 发现了这个解法, 标记一个最小步数的最远距离, 依次直到抵达数组的最后. 详见下表
 *
 *        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4  <- 数组下标
 *        7 0 9 6 9 6 1 7 9 0 1 2 9 0 3  <- 数组内容
 * step1. + 1 1 1 1 1 1 1
 * step2.     +           2 2 2 2
 * step3.         +               2 2
 * step4.               +             2  <- 结果
 */

#include <string.h> /* memset() */
#include "c/data-structures/array.h"
#include "c/test.h"

/* Time Limit Exceeded */
int jump_v1(int *nums, int numsSize) {
  int table[numsSize];
  memset(table, 0, sizeof(table));

  for (int i = 0; i < numsSize - 1; i++) {
    for (int j = 1; j <= nums[i]; j++) {
      if (i + j >= numsSize)
        break;
      if (table[i + j] == 0 || table[i + j] > table[i] + 1)
        table[i + j] = table[i] + 1;
    }
  }

  return table[numsSize - 1];
}

int jump_v2(int *nums, int numsSize) {
  int table[numsSize];
  memset(table, 0, sizeof(table));

  int curIndex = 0;
  for (int i = 0; i < numsSize-1; i++) {
    if (curIndex > i + nums[i]) {
      continue;
    }
    int j = curIndex + 1;
    curIndex = i + nums[i];
    while (j <= curIndex) {
      if (j == numsSize - 1) {
        return table[i] + 1;
      }
      table[j++] = table[i] + 1;
    }
  }

  return table[numsSize - 1];
}

void test(int expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);

  EXPECT_EQ_INT(expect, jump_v1(arrayValue(e), arraySize(e)));

  EXPECT_EQ_INT(expect, jump_v2(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(2, "[2,3,1,1,4]");

  test(0, "[0]");
  test(0, "[1]");
  test(1, "[2, 3, 1]");
  test(2, "[7,0,9,6,9,6,1,7,9,0,1,2,9,0,3]");

  return testOutput();
}
