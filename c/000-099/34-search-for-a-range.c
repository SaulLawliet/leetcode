/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 题目要求时间复杂度是 O(log n), 所以二分查找
 */

#include <stdbool.h>
#include <stdlib.h> /* malloc() */
#include "c/data-structures/array.h"
#include "c/test.h"

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int *nums, int numsSize, int target, int *returnSize) {
  *returnSize = 2;
  int x = -1, y = -1;
  int a = 0, b = numsSize - 1, i;
  while (a <= b) {
    i = (a + b) / 2;
    if (nums[i] < target) {
      a = i + 1;
    } else if (nums[i] > target) {
      b = i - 1;
    } else {
      x = y = i;
      while (x > 0 && nums[x-1] == target) x--;
      while (y < numsSize - 1 && nums[y+1] == target) y++;
      break;
    }
  }
  int *rtn = malloc(sizeof(int) * *returnSize);
  rtn[0] = x;
  rtn[1] = y;
  return rtn;
}

void test(const char *expect, const char *str, int target) {
  arrayEntry *e = arrayParse(str, ARRAY_INT);
  int returnSize;
  int* a = searchRange(arrayValue(e), arraySize(e), target, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(a, returnSize, ARRAY_INT));

  arrayFree(e);
}

/*
  Given [5, 7, 7, 8, 8, 10] and target value 8,
  return [3, 4].
 */
int main(void) {
  test("[3,4]", "[5,7,7,8,8,10]", 8);
  test("[-1,-1]", "[]", 0);

  return testOutput();
}
