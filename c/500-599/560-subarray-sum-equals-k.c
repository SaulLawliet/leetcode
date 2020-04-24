/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 暴力破解, 时间复杂度: O(n^2), 提交后比较耗时.
 *
 * 看了解答方案后, 使用 HashMap 的时间复杂度为: O(n)
 * TODO: 后续引入 HashMap 后再优化
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int subarraySum(int *nums, int numsSize, int k) {
  int count = 0;
  for (int i = 0; i < numsSize; i++) {
    for (int j = i, sum = 0; j < numsSize && sum < k; j++) {
        sum += nums[j];
        if (sum == k) {
          ++count;
        }
    }
  }
  return count;
}

void test(int expect, char *nums, int k) {
  arrayEntry *e = arrayParse1D(nums, ARRAY_INT);
  EXPECT_EQ_INT(expect, subarraySum(arrayValue(e), arraySize(e), k));
  arrayFree(e);
}

int main(void) {
  test(2, "[1,1,1]", 2);

  return testOutput();
}
