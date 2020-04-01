/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 在 46-permutations 的基础上 判断是否已经处理过相同的数字即可,
 * 注意要把数据源排序, 保证重复数据是相邻的
 */

#include <stdbool.h>
#include <stdlib.h> /* malloc(), qsort() */
#include <string.h> /* memcpy() */
#include "c/data-structures/array.h"
#include "c/test.h"
#include "c/tools/compare.h"

int factorial(int n) {
  if (n <= 1) return 1;
  return n * factorial(n - 1);
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

bool contains(int *arr, int arrSize, int value) {
  for (int i = 0; i < arrSize; ++i) {
    if (arr[i] == value) {
      return true;
    }
  }
  return false;
}

void permutations(int **rt, int *rtSize, int *nums, int start, int length) {
  if (start == length - 1) {
    memcpy(rt[(*rtSize)++] = malloc(sizeof(int) * length), nums, sizeof(int) * length);
  } else {
    int arr[length - start + 1], arrIndex = 0;
    for (int i = start; i != length; i++) {
      if (contains(arr, arrIndex, nums[i])) {
        continue;
      }
      arr[arrIndex++] = nums[i];

      swap(&nums[start], &nums[i]);
      permutations(rt, rtSize, nums, start+1, length);
      swap(&nums[start], &nums[i]); /* 没有这一行也是正确的, 有了这一行是为了生成的数据是按照书写顺序 */
    }
  }
}

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int **permuteUnique(int *nums, int numsSize, int *returnSize, int** returnColumnSizes) {
  qsort(nums, numsSize, sizeof(int), compare_ints);

  int **rt = malloc(sizeof(int*) * factorial(numsSize));
  *returnSize = 0;

  permutations(rt, returnSize, nums, 0, numsSize);

  *returnColumnSizes = malloc(sizeof(int) * *returnSize);
  for (int i = 0; i < *returnSize; i++) {
    (*returnColumnSizes)[i] = numsSize;
  }
  return rt;
}

void test(const char* expect, const char* str) {
  arrayEntry *e = arrayParse1D(str, ARRAY_INT);
  int returnSize;
  int *returnColumnSizes;
  int **a = permuteUnique(arrayValue(e), arraySize(e), &returnSize, &returnColumnSizes);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString2D(a, returnSize, returnColumnSizes, ARRAY_INT));

  arrayFree(e);
}

int main(void) {
  test("[[1,1,2],[1,2,1],[2,1,1]]", "[1,1,2]");
  test("[[1,1,2,2],[1,2,1,2],[1,2,2,1],[2,1,1,2],[2,1,2,1],[2,2,1,1]]", "[1,1,2,2]");

  return testOutput();
}
