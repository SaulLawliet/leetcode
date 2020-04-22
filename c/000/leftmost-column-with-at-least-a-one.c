/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 由于每一行都是有序的, 所以可以从右下角往左上角查找
 */

#include <stdlib.h> /* malloc(), free() */
#include "c/data-structures/array.h"
#include "c/test.h"

struct BinaryMatrix {
  arrayEntry *e;
  int (*get)(struct BinaryMatrix *, int, int);
  int *(*dimensions)(struct BinaryMatrix *);
};

int get(struct BinaryMatrix *matrix, int x, int y) {
  return ((int **)arrayValue(matrix->e))[x][y];
}

int *dimensitons(struct BinaryMatrix *matrix) {
  int *dimensitons = malloc(sizeof(int) * 2);
  dimensitons[0] = arrayRow(matrix->e);
  dimensitons[1] = arrayCol(matrix->e);
  return dimensitons;
}

/**
 * // This is the BinaryMatrix's API interface.
 * // You should not implement it, or speculate about its implementation
 * struct BinaryMatrix {
 *     int (*get)(struct BinaryMatrix*, int, int);
 *     int* (*dimensions)(struct BinaryMatrix*);
 * };
 */
int leftMostColumnWithOne(struct BinaryMatrix *matrix) {
  int *dimensitons = matrix->dimensions(matrix);
  int x = dimensitons[0] - 1, y = dimensitons[1] - 1, y1 = y;
  free(dimensitons);
  while (x >= 0 && y >= 0) {
    matrix->get(matrix, x, y) == 0 ? --x : --y;
  }
  return x == -1 && y == y1 ? -1 : y + 1;
}

void test(int expect, char *s) {
  arrayEntry *e = arrayParse2D(s, ARRAY_INT);
  struct BinaryMatrix matrix = {e, get, dimensitons};
  EXPECT_EQ_INT(expect, leftMostColumnWithOne(&matrix));
  arrayFree(e);
}

int main(void) {
  test(0, "[[0,0],[1,1]]");
  test(1, "[[0,0],[0,1]]");
  test(-1, "[[0,0],[0,0]]");
  test(1, "[[0,0,0,1],[0,0,1,1],[0,1,1,1]]");

  return testOutput();
}
