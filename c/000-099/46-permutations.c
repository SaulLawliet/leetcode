/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 全排列的递归解法, 依次交换数据
 */

#include <stdlib.h> /* malloc() */
#include <string.h> /* memcpy() */
#include "c/data-structures/array.h"
#include "c/test.h"

int factorial(int n) {
  if (n <= 1) return 1;
  return n * factorial(n - 1);
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void permutations(int **rt, int *rtSize, int *nums, int start, int length) {
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
int **permute(int *nums, int numsSize, int *returnSize) {
  int **rt = malloc(sizeof(int*) * factorial(numsSize));
  *returnSize = 0;

  permutations(rt, returnSize, nums, 0, numsSize);
  return rt;
}

void test(const char* expect, const char* str) {
  arrayEntry *e = arrayParse1D(str, ARRAY_INT);
  int returnSize;
  int **a = permute(arrayValue(e), arraySize(e), &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString2DSameCol(a, returnSize, arraySize(e), ARRAY_INT));

  arrayFree(e);
}

int main(void) {
  test("[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,2,1],[3,1,2]]", "[1,2,3]");

  return testOutput();
}
