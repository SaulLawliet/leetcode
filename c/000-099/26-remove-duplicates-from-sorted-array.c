/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include <stdbool.h>
#include "../test.h"
#include "../data-structures/array.h"

int removeDuplicates(int* nums, int numsSize) {
  if (numsSize == 0) return 0;
  int i = 0, j = 1;
  for (; j < numsSize; j++)
    if (nums[j] != nums[i]) nums[++i] = nums[j];
  return i + 1;
}

void test(const char* expect, const char* actual) {
  size_t expectNumsSize, actualNumsSize;
  int* expectNums = arrayNewByStr(expect, &expectNumsSize);
  int* actualNums = arrayNewByStr(actual, &actualNumsSize);

  EXPECT_EQ_INT((int)expectNumsSize, removeDuplicates(actualNums, actualNumsSize));
  EXPECT_EQ_STRING_AND_FREE(arrayToString(expectNums, expectNumsSize),
                            arrayToString(actualNums, expectNumsSize));

  free(expectNums);
  free(actualNums);
}

int main(void) {
  test("[1, 2]", "[1, 1, 2]");

  return testOutput();
}
