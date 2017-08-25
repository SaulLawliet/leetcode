/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 全排列的递归解法, 依次交换数据
 */

#include <stdlib.h>  /* malloc() */
#include <string.h>  /* memcpy() */
#include "../test.h"
#include "../data-structures/array.h"

int factorial(int n) {
  if (n <= 1) return 1;
  return n * factorial(n - 1);
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void permutations(int** rt, int* rtSize, int* nums, int start, int length) {
  if (start == length - 1) {
    memcpy(rt[(*rtSize)++] = malloc(sizeof(int) * length), nums, sizeof(int) * length);
  } else {
    for (int i = start; i != length; i++) {
      swap(&nums[start], &nums[i]);
      permutations(rt, rtSize, nums, start+1, length);
      swap(&nums[start], &nums[i]);
    }
  }
}

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int** permute(int* nums, int numsSize, int* returnSize) {
  int** rt = malloc(sizeof(int *) * factorial(numsSize));
  *returnSize = 0;

  permutations(rt, returnSize, nums, 0, numsSize);
  return rt;
}

void test(const char* s, int expectSize, const char* expect) {
  size_t numsSize;
  int* nums = arrayNewByStr(s, &numsSize);

  int returnSize;
  int** rt = permute(nums, numsSize, &returnSize);

  EXPECT_EQ_INT(expectSize, returnSize);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, array2DToString(rt, returnSize, numsSize));

  array2DFree((void**)rt, returnSize);
  free(nums);
}

int main(void) {
  test("[1, 2, 3]", 6, "[[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 2, 1], [3, 1, 2]]");

  return testOutput();
}
