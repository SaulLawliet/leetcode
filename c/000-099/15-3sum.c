/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 先将数组排序, 在求解时会方便一些, 这样更容易跳过重复的数据
 */

#include <stdlib.h> /* qsort(), malloc() */
#include "c/data-structures/array.h"
#include "c/test.h"
#include "c/tools/compare.h"

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int **threeSum(int *nums, int numsSize, int* returnSize) {
  if (numsSize < 3) {
    *returnSize = 0;
    return NULL;
  }

  qsort(nums, numsSize, sizeof(int), compare_ints);

  /* 组合 Cn3 => n! / ((n-3)! * 3!) */
  int **rt = malloc(sizeof(int *) *
                    (numsSize * (numsSize-1) * (numsSize-2)) / 6);

  int top = 0, i;
  for (i = 0; i <= numsSize - 3; i++) {
    if (nums[i] > 0) break;
    if (i > 0 && nums[i] == nums[i-1]) continue;  /* 跳过重复 */
    int j = i + 1,
        k = numsSize - 1;
    while (j < k) {
      int sum = nums[i] + nums[j] + nums[k];
      if (sum == 0) {
        rt[top] = malloc(sizeof(int) * 3);
        rt[top][0] = nums[i];
        rt[top][1] = nums[j];
        rt[top][2] = nums[k];
        top++, j++, k--;
        while (j < k && nums[j] == nums[j-1]) j++;  /* 跳过重复 */
        while (j < k && nums[k] == nums[k+1]) k--;  /* 跳过重复 */
      } else if (sum > 0) {
        k--;
      } else {
        j++;
      }
    }
  }

  *returnSize = top;
  return rt;
}

void test(const char *expect, const char *str) {
  arrayEntry *e = arrayParse1D(str, ARRAY_INT);
  int returnSize;
  int **a = threeSum(arrayValue(e), arraySize(e), &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString2DSameCol(a, returnSize, 3, ARRAY_INT));

  arrayFree(e);
}

/*
  For example, given array S = [-1, 0, 1, 2, -1, -4],

  A solution set is:
  [
    [-1, 0, 1],
    [-1, -1, 2]
  ]
*/
int main() {
  test("[[-1,-1,2],[-1,0,1]]", "[-1, 0, 1, 2, -1, -4]");

  return testOutput();
}
