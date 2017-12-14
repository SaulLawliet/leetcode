/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 画圆
 */

#include "../test.h"
#include "../data-structures/array.h"

void rotate(int **matrix, int matrixRowSize, int matrixColSize) {
  int tmp;
  for (int i = 0; i < matrixRowSize / 2; ++i ) {
    for (int j = i; j < matrixRowSize-1-i; ++j) {
      tmp = matrix[i][j];
      matrix[i][j] = matrix[matrixRowSize-1-j][i];
      matrix[matrixRowSize-1-j][i] = matrix[matrixRowSize-1-i][matrixRowSize-1-j];
      matrix[matrixRowSize-1-i][matrixRowSize-1-j] = matrix[j][matrixRowSize-1-i];
      matrix[j][matrixRowSize-1-i] = tmp;
    }
  }
}

void test(const char *expect, const char *str) {
  arrayEntry *e = arrayParse(str, ARRAY_INT);
  rotate(arrayValue(e), arrayRow(e), arrayCol(e));

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString(e));

  arrayFree(e);
}

int main(void) {
  test("[[7,4,1],[8,5,2],[9,6,3]]",
       "[[1,2,3],[4,5,6],[7,8,9]]");
  test("[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]]",
       "[[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]");

  return testOutput();
}
