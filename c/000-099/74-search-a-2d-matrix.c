/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 转换一下矩阵下标, 同样是二分查找
 */

#include <stdbool.h>
#include "c/data-structures/array.h"
#include "c/test.h"

bool searchMatrix(int **matrix, int matrixRowSize, int matrixColSize, int target) {
  int a = 0, b = matrixRowSize * matrixColSize - 1;
  while (a <= b) {
    int i = (a + b) / 2;
    int v = matrix[i / matrixColSize][i % matrixColSize];
    if (v > target) {
      b = i - 1;
    } else if (v < target) {
      a = i + 1;
    } else {
      return true;
    }
  }
  return false;
}

void test(bool expect, const char *matrix, int target) {
  arrayEntry *e = arrayParse2D(matrix, ARRAY_INT);

  EXPECT_EQ_INT(expect, searchMatrix(arrayValue(e), arrayRow(e), arrayCol(e), target));

  arrayFree(e);
}

int main(void) {
  test(true,
       "["
       "[1,   3,  5,  7],"
       "[10, 11, 16, 20],"
       "[23, 30, 34, 50]"
       "]",
       3);
  test(false,
       "["
       "[1,   3,  5,  7],"
       "[10, 11, 16, 20],"
       "[23, 30, 34, 50]"
       "]",
       13);

  testOutput();
}
