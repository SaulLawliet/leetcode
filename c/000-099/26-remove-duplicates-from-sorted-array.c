/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include <stdbool.h>
#include "c/data-structures/array.h"
#include "c/test.h"

int removeDuplicates(int *nums, int numsSize) {
  if (numsSize == 0) return 0;
  int i = 0, j = 1;
  for (; j < numsSize; j++)
    if (nums[j] != nums[i]) nums[++i] = nums[j];
  return i + 1;
}

void test(const char *expect, const char *str) {
  arrayEntry *e = arrayParse1D(str, ARRAY_INT);
  arraySetSize(e, removeDuplicates(arrayValue(e), arraySize(e)));

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString(e));

  arrayFree(e);
}

int main(void) {
  test("[1,2]", "[1,1,2]");

  return testOutput();
}
