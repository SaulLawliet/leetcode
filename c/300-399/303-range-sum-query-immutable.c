/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 最开始用最朴素的解法, 提交后发现严重超时.
 * 后续修改成缓存一下当前的数组的和, 取值的时候相减即是答案.
 */

#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* strcmp() */
#include "c/data-structures/array.h"
#include "c/test.h"

typedef struct {
  int *sum;
} NumArray;

NumArray *numArrayCreate(int *nums, int numsSize) {
  if (numsSize == 0) return NULL;

  NumArray *obj = malloc(sizeof(NumArray));
  obj->sum = malloc(sizeof(int) * (numsSize + 1)); /* 增加一个位置, 方便后续计算 */
  obj->sum[0] = 0;
  for (int i = 0; i < numsSize; i++) {
    obj->sum[i+1] = nums[i] + obj->sum[i];
  }

  return obj;
}

int numArraySumRange(NumArray *obj, int i, int j) {
  if (obj == NULL) return 0;
  return obj->sum[j+1] - obj->sum[i];
}

void numArrayFree(NumArray *obj) {
  if (obj != NULL) {
    free(obj->sum);
    free(obj);
  }
}

/**
 * Your NumArray struct will be instantiated and called as such:
 * NumArray* obj = numArrayCreate(nums, numsSize);
 * int param_1 = numArraySumRange(obj, i, j);
 * numArrayFree(obj);
*/

void test(char *expectStr, char *commandStr, char *argStr) {
  arrayEntry *expectEntry = arrayParse1D(expectStr, ARRAY_STRING);
  arrayEntry *commandEntry = arrayParse1D(commandStr, ARRAY_STRING);
  arrayEntry *argEntry = arrayParse1D(argStr, ARRAY_STRING);

  NumArray *obj;

  for (int i = 0; i < arraySize(commandEntry); i++) {
    char *command = ((char **)arrayValue(commandEntry))[i];
    char *args = ((char **)arrayValue(argEntry))[i];

    if (strcmp(command, "NumArray") == 0) {
      arrayEntry *e = arrayParse2D(args, ARRAY_INT);
      obj = numArrayCreate(((int **)arrayValue(e))[0], arrayCols(e)[0]);
      arrayFree(e);
    } else if (strcmp(command, "sumRange") == 0) {
      int expect = atoi(((char **)arrayValue(expectEntry))[i]);
      arrayEntry *e = arrayParse1D(args, ARRAY_INT);
      EXPECT_EQ_INT(expect, numArraySumRange(obj, ((int *)arrayValue(e))[0], ((int *)arrayValue(e))[1]));
      arrayFree(e);
    }
  }

  numArrayFree(obj);

  arrayFree(argEntry);
  arrayFree(commandEntry);
  arrayFree(expectEntry);
}

int main(void) {
  test("[null,1,-1,-3]",
       "[NumArray,sumRange,sumRange,sumRange]",
       "[[[-2,0,3,-5,2,-1]],[0,2],[2,5],[0,5]]");

  return testOutput();
}
