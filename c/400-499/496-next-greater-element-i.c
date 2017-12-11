/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "../test.h"
#include "../data-structures/array.h"

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* nextGreaterElement(int* findNums, int findNumsSize, int* nums, int numsSize, int* returnSize) {
  int* rtn = malloc(sizeof(int) * findNumsSize);
  for (int i = 0; i < findNumsSize; ++i) {
    int j = 0;
    while (nums[j] != findNums[i]) j++;

    for (; j < numsSize; ++j) {
      if (nums[j] > findNums[i]) {
        rtn[i] = nums[j];
        break;
      }
    }
    if (j == numsSize) rtn[i] = -1;
  }
  *returnSize = findNumsSize;
  return rtn;
}

void test(const char* str1, const char* str2, const char* expect) {
  int findNumsSize, numsSize, returnSize;
  int *findNums = arrayNewByStr(str1, &findNumsSize),
           *nums = arrayNewByStr(str2, &numsSize),
            *rtn = nextGreaterElement(findNums, findNumsSize, nums, numsSize, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString(rtn, returnSize));
  free(nums);
  free(findNums);
}

int main(void) {
  test("[4,1,2]", "[1,3,4,2]", "[-1,3,-1]");
  test("[2,4]", "[1,2,3,4]", "[3,-1]");
  return testOutput();
}
