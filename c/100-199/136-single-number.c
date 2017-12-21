/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 利用或运算 (a ^ a = 0)
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int singleNumber(int *nums, int numsSize) {
  int rtn = 0;
  for (int i = 0; i < numsSize; i++)
    rtn ^= nums[i];
  return rtn;
}

void test(int expect, const char *str) {
  arrayEntry *e = arrayParse(str, ARRAY_INT);

  EXPECT_EQ_INT(expect, singleNumber(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(100, "[300, 200, 100, 200, 300]");

  testOutput();
}
