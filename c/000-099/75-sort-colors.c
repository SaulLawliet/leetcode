/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * Q: Could you come up with a one-pass algorithm using only constant space?
 *
 * 分组的思路
 * 遍历一遍数组, 将0放入数组前半部分, 将2放入数组后半部分
 */

#include "c/data-structures/array.h"
#include "c/test.h"

void swap(int *a, int *b) {
  int tmp = *a; *a = *b; *b = tmp;
}

void sortColors(int *nums, int numsSize) {
  int i = 0, p0 = -1, p2 = numsSize;
  while (i < p2) {
    if (nums[i] == 0) {
      swap(&nums[++p0], &nums[i++]);
    } else if (nums[i] == 1) {
      i++;
    } else if (nums[i] == 2) {
      swap(&nums[--p2], &nums[i]);
    }
  }
}

void test(const char *expect, const char *str) {
  arrayEntry *e = arrayParse1D(str, ARRAY_INT);
  sortColors(arrayValue(e), arraySize(e));

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, arrayToString(e));

  arrayFree(e);
}

int main(void) {
  test("[0,0,1,1,2,2]", "[2,0,2,1,1,0]");

  testOutput();
}
