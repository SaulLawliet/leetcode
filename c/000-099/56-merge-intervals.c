/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 排序后, 就很好处理了
 */

#include <stdlib.h>  /* qsort(), malloc() */
#include "../test.h"

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

void test() {
  // TODO: test
}

int main(void) {
  return testOutput();
}
