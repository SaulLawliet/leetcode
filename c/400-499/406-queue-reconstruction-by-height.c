/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 两种解法思路都是一样的，排序后，通过 k 计算出最终下标
 *
 * v1: 24 ms (beats 60%)
 *   排序后（第1个值升序，第2个值降序），以数数的方式依次插入每个值
 *      [4,4] [5,2] [5,0] [6,1] [7,1] [7,0]
 *   0:   0     1     2     3   [4,4]   5
 *   1:   0     1   [5,2]   3     x     4
 *   2: [5,0]   1     x     2     x     3
 *   3:   x     0     x   [6,1]   x     2
 *   4:   x     0     x     x     x   [7,1]
 *   5:   x   [7,0]   x     x     x     x
 *
 * v2: 16 ms (beats 100%)
 *   排序后（第1个值降序，第2个值升序），以移动的方式依次插入每个值
 *      [7,0] [7,1],[6,1],[5,0],[5,2],[4,4]
 *   0: [7,0]
 *   1: [7,0] [7,1]
 *   2: [7,0] [6,1] [7,1]
 *   3: [5,0] [7,0] [6,1] [7,1]
 *   4: [5,0] [7,0] [5,2] [6,1] [7,1]
 *   5: [5,0] [7,0] [5,2] [6,1] [4,4] [7,1]
 */

#include <stdlib.h> /* qsort(), malloc() */
#include <string.h> /* memset(), memcpy() */
#include "c/data-structures/array.h"
#include "c/test.h"

int compare_v1(const void *a, const void *b) {
  int *arg1 = *(int **)a;
  int *arg2 = *(int **)b;

  int cmp = arg1[0] - arg2[0];
  return cmp != 0 ? cmp : arg2[1] - arg1[1];
}

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int **reconstructQueue_v1(int **people, int peopleRowSize, int peopleColSize, int *returnSize) {
  qsort(people, peopleRowSize, sizeof(int*), compare_v1);

  int memSize = sizeof(int *) * peopleRowSize;
  int **rtn = memset(malloc(memSize), 0, memSize);
  for (int i = 0; i < peopleRowSize; ++i) {
    int flag = people[i][1];
    for (int j = 0; j < peopleRowSize; ++j) {
      if (rtn[j] != NULL) continue;
      if (flag-- == 0) {
        rtn[j] = malloc(sizeof(int)* peopleColSize);
        memcpy(rtn[j], people[i], sizeof(int)* peopleColSize);
        break;
      }
    }
  }
  *returnSize = peopleRowSize;
  return rtn;
}

int compare_v2(const void *a, const void *b) {
  int *arg1 = *(int **)a;
  int *arg2 = *(int **)b;

  int cmp = arg2[0] - arg1[0];
  return cmp != 0 ? cmp : arg1[1] - arg2[1];
}

/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int **reconstructQueue_v2(int **people, int peopleRowSize, int peopleColSize, int *returnSize) {
  qsort(people, peopleRowSize, sizeof(int *), compare_v2);

  int **rtn = malloc(sizeof(int *) * peopleRowSize);
  *returnSize = 0;
  for (int i = 0; i < peopleRowSize; ++i) {
    int flag = people[i][1];
    for (int j = (*returnSize)++; j > flag; j--) rtn[j] = rtn[j - 1];
    rtn[flag] = malloc(sizeof(int) * peopleColSize);
    memcpy(rtn[flag], people[i], sizeof(int) * peopleColSize);
  }
  return rtn;
}

void test(const char *expect, const char *str) {
  arrayEntry *e = arrayParse2D(str, ARRAY_INT);
  int returnSize;
  int **rtn = reconstructQueue_v1(arrayValue(e), arrayRow(e), arrayCol(e), &returnSize);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString2DSameCol(rtn, returnSize, arrayCol(e), ARRAY_INT));

  rtn = reconstructQueue_v2(arrayValue(e), arrayRow(e), arrayCol(e), &returnSize);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString2DSameCol(rtn, returnSize, arrayCol(e), ARRAY_INT));

  arrayFree(e);
}

int main(void) {
  test("[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]",
       "[[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]");

  testOutput();
}
