/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 */

#include "../test.h"
#include "../data-structures/array.h"

int removeElement(int* nums, int numsSize, int val) {
  int i = 0, j = 0;
  for (; j < numsSize; j++)
    if (nums[j] != val) nums[i++] = nums[j];
  return i;
}

void test(const char* expect, const char* actual, int val) {
  int expectNumsSize, actualNumsSize;
  int* expectNums = arrayNewByStr(expect, &expectNumsSize);
  int* actualNums = arrayNewByStr(actual, &actualNumsSize);

  EXPECT_EQ_INT((int)expectNumsSize, removeElement(actualNums, actualNumsSize, val));
  EXPECT_EQ_STRING_AND_FREE(arrayToString(expectNums, expectNumsSize),
                            arrayToString(actualNums, expectNumsSize));

  free(expectNums);
  free(actualNums);
}

int main(void) {
  test("[2, 2]", "[3, 2, 2, 3]", 3);

  return testOutput();
}
