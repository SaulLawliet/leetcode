/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 因为时间的种类在1440, 而题目的数量最大是20000, 所以维护一个bool数组, 最后计算一个最小距离
 */

#include <string.h>  /* memset() */
#include <stdbool.h>
#include "../test.h"
#include "../data-structures/array.h"

int findMinDifference(char **timePoints, int timePointsSize) {
  int size = 24 * 60;
  bool flag[size];
  memset(flag, 0, sizeof(bool) * size);

  for (int i = 0; i < timePointsSize; i++) {
    int index =
      (timePoints[i][0] - '0') * 600 +
      (timePoints[i][1] - '0') * 60 +
      (timePoints[i][3] - '0') * 10 +
      (timePoints[i][4] - '0');
    if (flag[index]) return 0;
    flag[index] = true;
  }

  int rtn = size;
  int first_index = -1;
  int last_index;
  for (int i = 0; i < size; i++) {
    if (flag[i]) {
      if (first_index < 0) {
        first_index = i;
        last_index = i;
      } else {
        int v = i - last_index;
        if (v < rtn) rtn = v;
      }
      last_index = i;
    }
  }
  int v = first_index - last_index + size;
  if (v < rtn) rtn = v;
  return rtn;
}

void test(int expect, const char *str) {
  arrayEntry *e = arrayParse(str, ARRAY_STRING);

  EXPECT_EQ_INT(expect, findMinDifference(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(1, "[23:59, 00:00]");
  test(0, "[00:00, 23:59, 00:00]");

  return testOutput();
}
