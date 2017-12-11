/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 先初始化一个空的子集, 然后将每个元素依次放入之前的每个子集的后面
 */

#include <math.h>    /* pow() */
#include <stdlib.h>  /* NULL, malloc() */
#include <string.h>  /* memcpy() */
#include "../test.h"
#include "../data-structures/array.h"

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int** columnSizes, int* returnSize) {
  *returnSize = pow(2, numsSize);
  int** rtn = malloc(sizeof(int*) * *returnSize);
  *columnSizes = malloc(sizeof(int) * *returnSize);

  int rtnSize = 1;
  rtn[0] = NULL;
  (*columnSizes)[0] = 0;

  for (int i = 0; i < numsSize; ++i) {
    for (int j = 0; j < rtnSize; ++j) {
      int newIndex = rtnSize + j;
      rtn[newIndex] = malloc(sizeof(int) * ((*columnSizes)[newIndex] = (*columnSizes)[j] + 1));
      memcpy(rtn[newIndex], rtn[j], sizeof(int) * (*columnSizes)[j]);
      rtn[newIndex][(*columnSizes)[j]] = nums[i];
    }
    rtnSize *= 2;
  }

  return rtn;
}

void test(const char* str, const char* expect) {
  int numsSize;
  int* nums = arrayNewByStr(str, &numsSize);

  int returnSize;
  int* columnSizes;
  int** rtn = subsets(nums, numsSize, &columnSizes, &returnSize);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, array2DToString(rtn, returnSize, columnSizes));

  array2DFree((void**)rtn, returnSize);
  free(columnSizes);
  free(nums);
}

int main(void) {
  test("[1, 2, 3]",
       "[[], [1], [2], [1, 2], [3], [1, 3], [2, 3], [1, 2, 3]]");

  return testOutput();
}
