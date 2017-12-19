/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include <stdlib.h> /* malloc(), free() */

#include "c/data-structures/array.h"
#include "c/test.h"

#define MAX_SIZE 100

void dfs(int *nums, int numsSize, int start, int k, int n, int ***rtn, int **columnSizes, int *returnSize) {
  if (numsSize >= k) {
    if (n == 0) {
      (*columnSizes)[*returnSize] = k;
      memcpy(((*rtn)[*returnSize] = malloc(sizeof(int *) * k)), nums, sizeof(int) * k);
      (*returnSize)++;
    }
    return;
  }

  for (int i = start; i < 10; ++i) {
    if (n - i < 0)
      return;
    nums[numsSize] = i;
    dfs(nums, numsSize + 1, i + 1, k, n - i, rtn, columnSizes, returnSize);
  }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **combinationSum3(int k, int n, int **columnSizes, int *returnSize) {
  *returnSize = 0;
  int **rtn = malloc(sizeof(int *) * MAX_SIZE);
  *columnSizes = malloc(sizeof(int) * MAX_SIZE);
  int *nums = malloc(sizeof(int) * k);
  dfs(nums, 0, 1, k, n, &rtn, columnSizes, returnSize);
  free(nums);
  return rtn;
}

void test(const char *expect, int k, int n) {
  int *columnSizes;
  int returnSize;
  int **a = combinationSum3(k, n, &columnSizes, &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString2D(a, returnSize, columnSizes, ARRAY_INT));
}

int main(void) {
  test("[[1,2,4]]", 3, 7);
  test("[[1,2,6],[1,3,5],[2,3,4]]", 3, 9);
  test("[]", 2, 18);

  testOutput();
}
