/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 跟 No.303 的解题思路一样, 无非就是增加了一个维度, 用计算面积的思路来求和即可.
 */

#include <stdlib.h> /* malloc(), free(), atoi() */
#include <string.h> /* strcmp() */
#include "c/test.h"
#include "c/data-structures/array.h"

typedef struct {
  int **sum;
  int row;
} NumMatrix;

NumMatrix *numMatrixCreate(int **matrix, int matrixSize, int *matrixColSize) {
  if (matrixSize == 0) {
    return NULL;
  }
  int matrixCol = matrixColSize[0];

  NumMatrix *obj = malloc(sizeof(NumMatrix));
  obj->row = matrixSize + 1;
  obj->sum = malloc(sizeof(int *) * obj->row);
  for (int i = 0; i <= matrixSize; i++) {
    obj->sum[i] = malloc(sizeof(int) * (matrixCol + 1));
  }

  for (int i = 0; i <= matrixSize; i++) obj->sum[i][0] = 0;
  for (int i = 0; i <= matrixCol; i++) obj->sum[0][i] = 0;

  for (int i = 1; i <= matrixSize; i++) {
    for (int j = 1; j <= matrixCol; j++) {
      obj->sum[i][j] = matrix[i - 1][j - 1] + obj->sum[i - 1][j] + obj->sum[i][j - 1] - obj->sum[i - 1][j - 1];
    }
  }

  return obj;
}

int numMatrixSumRegion(NumMatrix *obj, int row1, int col1, int row2, int col2) {
  if (obj == NULL) return 0;
  return obj->sum[row2 + 1][col2 + 1] - obj->sum[row1][col2 + 1] - obj->sum[row2 + 1][col1] + obj->sum[row1][col1];
}

void numMatrixFree(NumMatrix *obj) {
  if (obj != NULL) {
    for (int i = 0; i < obj->row; i++) {
      free(obj->sum[i]);
    }
    free(obj->sum);
    free(obj);
  }
}

/**
 * Your NumMatrix struct will be instantiated and called as such:
 * NumMatrix* obj = numMatrixCreate(matrix, matrixSize, matrixColSize);
 * int param_1 = numMatrixSumRegion(obj, row1, col1, row2, col2);

 * numMatrixFree(obj);
*/

void test(char *expectStr, char *commandStr, char *argStr) {
  arrayEntry *expectEntry = arrayParse1D(expectStr, ARRAY_STRING);
  arrayEntry *commandEntry = arrayParse1D(commandStr, ARRAY_STRING);
  arrayEntry *argEntry = arrayParse1D(argStr, ARRAY_STRING);

  NumMatrix *obj;

  for (int i = 0; i < arraySize(commandEntry); i++) {
    char *command = ((char **)arrayValue(commandEntry))[i];
    char *args = ((char **)arrayValue(argEntry))[i];

    if (strcmp(command, "NumMatrix") == 0) {
      arrayEntry *e = arrayParse1D(args, ARRAY_STRING);
      arrayEntry *e2 = arrayParse2D(((char **)arrayValue(e))[0], ARRAY_INT);
      obj = numMatrixCreate(arrayValue(e2), arrayRow(e2), arrayCols(e2));
      arrayFree(e2);
      arrayFree(e);
    } else if (strcmp(command, "sumRegion") == 0) {
      int expect = atoi(((char **)arrayValue(expectEntry))[i]);
      arrayEntry *e = arrayParse1D(args, ARRAY_INT);
      int *arr = (int *)arrayValue(e);
      EXPECT_EQ_INT(expect, numMatrixSumRegion(obj, arr[0], arr[1], arr[2], arr[3]));
      arrayFree(e);
    }
  }

  numMatrixFree(obj);

  arrayFree(argEntry);
  arrayFree(commandEntry);
  arrayFree(expectEntry);
}

int main(void) {
  test("[null,8,11,12]",
       "[NumMatrix,sumRegion,sumRegion,sumRegion]",
       "[[[[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]],[2,1,4,3],[1,1,2,2],[1,2,2,4]]");

  return testOutput();
}
