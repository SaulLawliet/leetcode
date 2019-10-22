/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include <stdlib.h> /* malloc() */
#include "c/data-structures/array.h"
#include "c/test.h"

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *nextGreaterElement(int *findNums, int findNumsSize, int *nums, int numsSize, int *returnSize) {
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

void test(const char* expect, const char* str1, const char* str2) {
  arrayEntry *e1 = arrayParse1D(str1, ARRAY_INT);
  arrayEntry *e2 = arrayParse1D(str2, ARRAY_INT);
  int returnSize;
  int *a = nextGreaterElement(arrayValue(e1), arraySize(e1), arrayValue(e2), arraySize(e2), &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(a, returnSize, ARRAY_INT));

  arrayFree(e1);
  arrayFree(e2);
}

int main(void) {
  test("[-1,3,-1]", "[4,1,2]", "[1,3,4,2]");
  test("[3,-1]", "[2,4]", "[1,2,3,4]");

  return testOutput();
}
