
/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 动态规划，取3方向
 */

#include "c/data-structures/array.h"
#include "c/test.h"

#define MIN(a, b) ((a) <= (b) ? (a) : (b))
#define MAX(a, b) ((a) >= (b) ? (a) : (b))
int maximalSquare(char **matrix, int matrixSize, int *matrixColSize) {
  int rtn = '0';
  for (int i = 0; i < matrixSize; ++i) {
    for (int j = 0; j < matrixColSize[0]; ++j) {
      if (matrix[i][j] != '0') {
        if (i > 0 && j > 0)
          matrix[i][j] = MIN(MIN(matrix[i-1][j], matrix[i][j-1]), matrix[i-1][j-1]) + 1;
        rtn = MAX(rtn, matrix[i][j]);
      }
    }
  }

  rtn -= '0';
  return rtn * rtn;
}

void test(int expect, const char *str) {
  arrayEntry *e = arrayParse2D(str, ARRAY_CHAR);

  EXPECT_EQ_INT(expect, maximalSquare(arrayValue(e), arrayRow(e), arrayCols(e)));

  arrayFree(e);
}

int main(void) {
  test(4, "[[1, 0, 1, 0, 0], \
            [1, 0, 1, 1, 1], \
            [1, 1, 1, 1, 1], \
            [1, 0, 0, 1, 0]]");
  test(0, "[]");
  test(1, "[[1]]");
  test(4, "[[1,0,1,0],[1,0,1,1],[1,0,1,1],[1,1,1,1]]");

  return testOutput();
}
