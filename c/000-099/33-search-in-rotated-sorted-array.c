/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 很好理解的写法, 以为性能可能不是最好的, 但耗时是第一梯队的.
 */

#include <stdbool.h>
#include "../test.h"
#include "../data-structures/array.h"

void swap(int* a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int search(int* nums, int numsSize, int target) {
  int index = -1;
  for (int i = 0; i != numsSize; i++) {
    if (index == -1 && nums[i] == target) {
      index = i;
    }
    if (index != -1) {
      for (int j = i; j != i - index; j--) {
        swap(&nums[j], &nums[j-1]);
      }
    }
  }
  return index;
}

void test(const char* before, const char* after, int target, int result) {
  int numsSize;
  int* nums = arrayNewByStr(before, &numsSize);

  EXPECT_EQ_INT(result, search(nums, numsSize, target));
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(after, arrayToString(nums, numsSize));

  free(nums);
}

int main(void) {
  test("[0, 1, 2, 4, 5, 6, 7]", "[4, 5, 6, 7, 0, 1, 2]", 4, 3);

  return testOutput();
}
