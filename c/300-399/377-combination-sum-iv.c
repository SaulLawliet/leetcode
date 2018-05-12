/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * v1: 第一次尝试用递归, 结果超时, 于是在递归的基础上, 缓存中间变量
 * v2: 动态规划 (打印递归结果, 就很容易看出如何写)
 */

#include <stdlib.h> /* malloc(), free() */
#include <string.h> /* memset() */
#include "c/data-structures/array.h"
#include "c/test.h"

int loop(int *nums, int numsSize, int target, int *tmp) {
  if (tmp[target] != -1)
    return tmp[target];

  int rtn = 0;
  for (int i = 0; i < numsSize; ++i)
    if (target >= nums[i])
      rtn += loop(nums, numsSize, target - nums[i], tmp);
  tmp[target] = rtn;
  return rtn;
}

int combinationSum4_v1(int *nums, int numsSize, int target) {
  int *tmp = malloc(sizeof(int) * (target + 1));
  tmp[0] = 1;
  for (int i = 1; i <= target; ++i)
    tmp[i] = -1;
  int rtn = loop(nums, numsSize, target, tmp);
  free(tmp);
  return rtn;
}

int combinationSum4_v2(int *nums, int numsSize, int target) {
  int *tmp = malloc(sizeof(int) * (target + 1));
  memset(tmp, 0, sizeof(int) * (target + 1));
  tmp[0] = 1;
  for (int i = 1; i <= target; ++i)
    for (int j = 0; j < numsSize; ++j)
      if (i >= nums[j])
        tmp[i] += tmp[i - nums[j]];
  int rtn = tmp[target];
  free(tmp);
  return rtn;
}

void test(int expect, const char *str, int target) {
  arrayEntry *e = arrayParse(str, ARRAY_INT);

  EXPECT_EQ_INT(expect, combinationSum4_v1(arrayValue(e), arraySize(e), target));
  EXPECT_EQ_INT(expect, combinationSum4_v2(arrayValue(e), arraySize(e), target));

  arrayFree(e);
}

int main(void) {
  test(7, "[1, 2, 3]", 4);
  test(181997601, "[1, 2, 3]", 32);

  testOutput();
}
