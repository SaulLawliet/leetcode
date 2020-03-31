/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 先向右, 开始按照螺旋划线.
 * 注意每画两个方向后, 数量+1.
 */

#include <stdlib.h> /* malloc() */
#include "c/data-structures/array.h"
#include "c/test.h"

int **spiralMatrixIII(int R, int C, int r0, int c0, int *returnSize, int **returnColumnSizes) {
  *returnSize = R * C;
  if (*returnSize == 0) {
    *returnColumnSizes = NULL;
    return NULL;
  }
  int **matrix = malloc(sizeof(int*) * *returnSize);
  *returnColumnSizes = malloc(sizeof(int) * *returnSize);
  for (int i = 0; i < *returnSize; ++i) {
    (*returnColumnSizes)[i] = 2;
    matrix[i] = malloc(sizeof(int) * 2);
  }

  int cur = 0, loop = 0, dir;
  matrix[cur][0] = r0;
  matrix[cur++][1] = c0;
  while (cur < *returnSize) {
    dir = loop % 4; /* 0: right, 1: down, 2: left, 3: up */
    for (int i = 0; i < loop / 2 + 1; ++i) { /* 每两次升级画线的长度 */
      switch (dir) {
        case 0: ++c0; break;
        case 1: ++r0; break;
        case 2: --c0; break;
        case 3: --r0; break;
      }

      if (r0 >= 0 && r0 < R && c0 >= 0 && c0 < C) { /* 合法的值才放入 */
        matrix[cur][0] = r0;
        matrix[cur++][1] = c0;
      }
    }
    ++loop;
  }

  return matrix;
}

void test(const char *expect, int R, int C, int r0, int c0) {
  int returnSize;
  int *returnColumnSizes;
  int **matrix = spiralMatrixIII(R, C, r0, c0, &returnSize, &returnColumnSizes);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString2D(matrix, returnSize, returnColumnSizes, ARRAY_INT));
}

int main(void) {
  test("[[0,0],[0,1],[0,2],[0,3]]", 1, 4, 0, 0);
  test("[[1,4],[1,5],[2,5],[2,4],[2,3],[1,3],[0,3],[0,4],[0,5],[3,5],[3,4],[3,3],[3,2],[2,2],[1,2],[0,2],[4,5],[4,4],[4,3],[4,2],[4,1],[3,1],[2,1],[1,1],[0,1],[4,0],[3,0],[2,0],[1,0],[0,0]]", 5, 6, 1, 4);

  return testOutput();
}
