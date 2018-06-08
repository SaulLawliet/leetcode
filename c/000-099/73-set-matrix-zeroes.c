/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 将相关数据存到第一行, 第一列中
 */

#include <stdbool.h>
#include "c/data-structures/array.h"
#include "c/test.h"

void setZeroes(int **matrix, int matrixRowSize, int matrixColSize) {
  bool firstRow = false, firstCol = false;
  for (int i = 0; i < matrixRowSize; ++i)
    for (int j = 0; j < matrixColSize; ++j)
      if (matrix[i][j] == 0) {
        if (i == 0) firstRow = true;
        if (j == 0) firstCol = true;
        matrix[0][j] = 0;
        matrix[i][0] = 0;
      }

  for (int i = 1; i < matrixRowSize; ++i)
    for (int j = 1; j < matrixColSize; ++j)
      if (matrix[i][0] == 0 || matrix[0][j] == 0)
        matrix[i][j] = 0;

  if (firstRow) {
    for (int j = 0; j < matrixColSize; ++j)
      matrix[0][j] = 0;
  }

  if (firstCol) {
    for (int i = 0; i < matrixRowSize; ++i)
      matrix[i][0] = 0;
  }
}

void test(const char *expect, const char *str) {
  arrayEntry *e = arrayParse2D(str, ARRAY_INT);
  setZeroes(arrayValue(e), arrayRow(e), arrayCol(e));

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString(e));

  arrayFree(e);
}

int main(void) {
  test("[[0,0,0],[0,0,0],[0,8,0]]", "[[0,2,3],[4,5,0],[7,8,9]]");

  testOutput();
}
