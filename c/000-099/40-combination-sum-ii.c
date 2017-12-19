/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 在 39 的基础上改动即可
 */

#include <stdlib.h> /* malloc(), free(), sort() */
#include <string.h> /* memcpy() */

#include "c/data-structures/array.h"
#include "c/test.h"

#define MAX_ROW_SIZE 1000
#define MAX_COL_SIZE 100

void dfs(int ***rtn, int **columnSizes, int *returnSize,
         int *candidateds, int candidatesSize, int target, int *nums, int numsSize, int order) {
  if (target == 0) {
    (*columnSizes)[*returnSize] = numsSize;
    memcpy(((*rtn)[*returnSize] = malloc(sizeof(int *) * numsSize)), nums, sizeof(int) * numsSize);
    (*returnSize)++;
    return;
  }
  for (int i = order; i < candidatesSize; ++i) {
    if (candidateds[i] > target) return;
    if (i > order && candidateds[i] == candidateds[i - 1]) continue;
    nums[numsSize] = candidateds[i];
    dfs(rtn, columnSizes, returnSize,
        candidateds, candidatesSize, target - candidateds[i], nums, numsSize + 1, i + 1);
  }
}

int compare_ints(const void *a, const void *b) {
  int arg1 = *(const int *)a;
  int arg2 = *(const int *)b;
  if (arg1 < arg2) return -1;
  if (arg1 > arg2) return 1;
  return 0;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **combinationSum2(int *candidates, int candidatesSize, int target, int **columnSizes, int *returnSize) {
  qsort(candidates, candidatesSize, sizeof(int), compare_ints);
  *returnSize = 0;
  int **rtn = malloc(sizeof(int *) * MAX_ROW_SIZE);
  *columnSizes = malloc(sizeof(int) * MAX_ROW_SIZE);
  int *nums = malloc(sizeof(int) * MAX_COL_SIZE);
  dfs(&rtn, columnSizes, returnSize,
      candidates, candidatesSize, target, nums, 0, 0);
  free(nums);
  return rtn;
}

void test(const char *expect, const char *str, int target) {
  arrayEntry *e = arrayParse(str, ARRAY_INT);
  int *columnSizes;
  int returnSize;
  int **a = combinationSum2(arrayValue(e), arraySize(e), target, &columnSizes, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString2D(a, returnSize, columnSizes, ARRAY_INT));

  arrayFree(e);
}

int main(void) {
  test("[[1,1,6],[1,2,5],[1,7],[2,6]]", "[10,1,2,7,6,1,5]", 8);
  test("[[2,2]]", "[2,2,2]", 4);
  test("[[1,1,1,5],[1,1,3,3],[3,5]]", "[3,1,3,5,1,1]", 8);

  testOutput();
}
