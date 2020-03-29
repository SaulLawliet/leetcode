/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 只需要注意, 所有的数字都是9的情况
 */

#include <stdbool.h>
#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* memset() */
#include "c/data-structures/array.h"
#include "c/test.h"

int *plusOne(int *digits, int digitsSize, int *returnSize) {
  bool allNine = true;
  for (int i = 0; i < digitsSize; i++) {
    if (digits[i] != 9) {
      allNine = false;
      break;
    }
  }
  *returnSize = digitsSize + (allNine ? 1 : 0);
  int *nums = malloc(sizeof(int) * *returnSize);

  if (allNine) {
    memset(nums, 0, sizeof(int) * *returnSize);
    nums[0] = 1;
  } else {
    bool plus = true;
    for (int i = digitsSize - 1; i >= 0; i--) {
      nums[i] = digits[i] + (plus ? 1 : 0);
      plus = nums[i] > 9;
      if (plus) nums[i] = 0;
    }
  }
  return nums;
}

void test(const char *expect, const char *digits) {
  arrayEntry *e = arrayParse1D(digits, ARRAY_INT);

  int returnSize = 0;
  int *nums = plusOne(arrayValue(e), arraySize(e), &returnSize);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString1D(nums, returnSize, ARRAY_INT));

  arrayFree(e);
}

int main(void) {
  test("[1,2,4]", "[1,2,3]");
  test("[4,3,2,2]", "[4,3,2,1]");

  return testOutput();
}
