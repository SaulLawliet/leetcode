/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 设置好边界, 画圈即可.
 * 结束循环的条件, 通过数组长度判断比较简单.
 */

#include <stdlib.h> /* malloc() */
#include <string.h>
#include "c/data-structures/array.h"
#include "c/test.h"

int *spiralOrder(int **matrix, int matrixSize, int *matrixColSize, int *returnSize) {
  if (matrixSize == 0) {
    *returnSize = 0;
    return NULL;
  }

  *returnSize = matrixSize * matrixColSize[0];
  int *arr = malloc(sizeof(int) * *returnSize);
  int size = 0;
  int r1 = 0, r2 = matrixSize - 1, c1 = 0, c2 = matrixColSize[0] - 1;

  while (1) {
    // left -> right
    for (int i = c1; i <= c2; i++) {
      arr[size++] = matrix[r1][i];
    }
    if (size == *returnSize) break;
    r1++;

    // up -> down
    for (int i = r1; i <= r2; i++) {
      arr[size++] = matrix[i][c2];
    }
    if (size == *returnSize) break;
    c2--;

    // right -> left
    for (int i = c2; i >= c1; i--) {
      arr[size++] = matrix[r2][i];
    }
    if (size == *returnSize) break;
    r2--;

    // down -> up
    for (int i = r2; i >= r1; i--) {
      arr[size++] = matrix[i][c1];
    }
    if (size == *returnSize) break;
    c1++;
  }

  return arr;
}

void test(const char *expect, char *s) {
  arrayEntry *e = arrayParse2D(s, ARRAY_INT);

  int returnSize;
  int *arr = spiralOrder(arrayValue(e), arrayRow(e), arrayCols(e), &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(arr, returnSize, ARRAY_INT));

  arrayFree(e);
}

int main(void) {
  test("[1,2,3,6,9,8,7,4,5]", "[[1,2,3],[4,5,6],[7,8,9]]");
  test("[1,2,3,4,8,12,11,10,9,5,6,7]", "[[1,2,3,4],[5,6,7,8],[9,10,11,12]]");

  return testOutput();
}
