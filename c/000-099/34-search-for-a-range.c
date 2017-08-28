/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 题目要求时间复杂度是 O(log n), 所以二分查找
 */

#include <stdlib.h>  /* malloc() */
#include <stdbool.h>
#include "../test.h"
#include "../data-structures/array.h"

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
  *returnSize = 2;
  int x = -1, y = -1;
  int a = 0, b = numsSize - 1, i;
  while (a <= b) {
    i = (a + b) / 2;
    if (nums[i] < target) a = i + 1;
    else if (nums[i] > target) b = i - 1;
    else {
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

void test(const char* expect, const char* s, int target) {
  size_t numsSize;
  int* nums = arrayNewByStr(s, &numsSize);

  int returnSize;
  int* actual = searchRange(nums, numsSize, target, &returnSize);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString(actual, returnSize));

  if (numsSize > 0) free(nums);
  if (returnSize > 0) free(actual);
}

/*
  Given [5, 7, 7, 8, 8, 10] and target value 8,
  return [3, 4].
 */
int main(void) {
  test("[3, 4]", "[5, 7, 7, 8, 8, 10]", 8);
  test("[-1, -1]", "[]", 0);

  return testOutput();
}