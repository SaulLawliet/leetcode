/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 暴力计算, 两层循环
 */

#include <stdlib.h>  /* malloc(), free() */
#include "../test.h"
#include "../data-structures/array.h"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int *nums, int numsSize, int target) {
  int i, j;
  for (i = 0; i != numsSize - 1; ++i) {
    for (j = i + 1; j != numsSize; ++j) {
      if (nums[i] + nums[j] == target) {
        int *r = malloc(sizeof(int) * 2);
        r[0] = i;
        r[1] = j;
        return r;
      }
    }
  }
  return NULL;
}

void test(const char *str, int target) {
  arrayEntry *e = arrayParse(str, ARRAY_INT);
  int *nums = arrayValue(e);
  int *answer = twoSum(nums, arraySize(e), target);

  EXPECT_EQ_INT(target, nums[answer[0]] + nums[answer[1]]);

  free(answer);
  arrayFree(e);
}

/*
  Given nums = [2, 7, 11, 15], target = 9,

  Because nums[0] + nums[1] = 2 + 7 = 9,
  return [0, 1].
 */
int main(void) {
  test("[2, 7, 11, 15]", 9);

  return testOutput();
}
