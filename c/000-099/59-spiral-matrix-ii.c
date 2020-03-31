/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 区别于 54-spiral-matrix 是画4条边, 这个是画圈.
 */

#include <stdlib.h> /* malloc() */
#include "c/data-structures/array.h"
#include "c/test.h"

int **generateMatrix(int n, int *returnSize, int **returnColumnSizes) {
  *returnSize = n;
  if (n == 0) {
    *returnColumnSizes = NULL;
    return NULL;
  }

  *returnColumnSizes = malloc(sizeof(int) * n);
  int **matrix = malloc(sizeof(int *) * n);
  for (int i = 0; i < n; ++i) {
    (*returnColumnSizes)[i] = n;
    matrix[i] = malloc(sizeof(int) * n);
  }

  for (int loop = 0, cur = 0; loop < (n + 1) / 2; ++loop) {
    int ceil = n - loop - 1;
    if (ceil == loop) {
      matrix[loop][loop] = ++cur;
      break;
    }
    for (int i = loop; i < ceil; ++i) matrix[loop][i] = ++cur;
    for (int i = loop; i < ceil; ++i) matrix[i][ceil] = ++cur;
    for (int i = ceil; i > loop; --i) matrix[ceil][i] = ++cur;
    for (int i = ceil; i > loop; --i) matrix[i][loop] = ++cur;
  }

  return matrix;
}

void test(const char *expect, int n) {
  int returnSize;
  int *returnColumnSizes;
  int **matrix = generateMatrix(n, &returnSize, &returnColumnSizes);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString2D(matrix, returnSize, returnColumnSizes, ARRAY_INT));
}

int main(void) {
  test("[[1,2,3],[8,9,4],[7,6,5]]", 3);

  test("[]", 0);
  test("[[1]]", 1);
  test("[[1,2,3,4],[12,13,14,5],[11,16,15,6],[10,9,8,7]]", 4);

  return testOutput();
}
