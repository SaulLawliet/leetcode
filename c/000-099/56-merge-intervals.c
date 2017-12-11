/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 排序后, 就很好处理了
 */

#include <stdlib.h>  /* qsort(), malloc() */
#include "../test.h"
#include "../data-structures/array.h"

struct Interval {
  int start;
  int end;
};

int compare(const void* a, const void* b) {
  return ((struct Interval*)a)->start - ((struct Interval*)b)->start;
}

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct Interval* merge(struct Interval* intervals, int intervalsSize, int* returnSize) {
  qsort(intervals, intervalsSize, sizeof(struct Interval), compare);

  struct Interval* rt = malloc(sizeof(struct Interval) * intervalsSize);
  *returnSize = 0;
  for (int i = 0; i < intervalsSize; ++i) {
    if (i != 0 && intervals[i].start <= rt[*returnSize-1].end) {
      if (rt[*returnSize-1].end < intervals[i].end)
        rt[*returnSize-1].end = intervals[i].end;
    } else {
      rt[*returnSize].start = intervals[i].start;
      rt[*returnSize].end = intervals[i].end;
      (*returnSize)++;
    }
  }

  return rt;
}

struct Interval* arrayToInterval(int** array, int row) {
  struct Interval* rtn = malloc(sizeof(struct Interval) * row);
  for (int i = 0; i < row; ++i) {
    rtn[i].start = array[i][0];
    rtn[i].end = array[i][1];
  }
  return rtn;
}

int** intervalToArray(struct Interval* intervals, int size) {
  int** rtn = malloc(sizeof(int*) * size);
  for (int i = 0; i < size; ++i) {
    rtn[i] = malloc(sizeof(int) * 2);
    rtn[i][0] = intervals[i].start;
    rtn[i][1] = intervals[i].end;
  }
  return rtn;
}

void test(const char* given, const char* expect) {
  int row, col;
  int** givenArray = array2DNewByStrSameCol(given, &row, &col);
  EXPECT_EQ_INT(2, col);

  struct Interval* intervals = arrayToInterval(givenArray, row);
  int rtnSize;
  struct Interval* rtn = merge(intervals, row, &rtnSize);

  int** rtnArray = intervalToArray(rtn, rtnSize);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, array2DToStringSameCol(rtnArray, rtnSize, col));

  array2DFree((void**)rtnArray, rtnSize);
  array2DFree((void**)givenArray, row);
  free(intervals);
  free(rtn);
}

int main(void) {
  test("[1,3],[2,6],[8,10],[15,18]", "[[1, 6], [8, 10], [15, 18]]");

  return testOutput();
}
