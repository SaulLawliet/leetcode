/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int removeElement(int *nums, int numsSize, int val) {
  int i = 0, j = 0;
  for (; j < numsSize; j++)
    if (nums[j] != val) nums[i++] = nums[j];
  return i;
}

void test(const char* expect, const char* str, int val) {
  arrayEntry *e = arrayParse1D(str, ARRAY_INT);
  arraySetSize(e, removeElement(arrayValue(e), arraySize(e), val));

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString(e));

  arrayFree(e);
}

int main(void) {
  test("[2,2]", "[3,2,2,3]", 3);

  return testOutput();
}
