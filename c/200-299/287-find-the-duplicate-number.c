/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * https://leetcode.com/problems/find-the-duplicate-number/
 * Q: 在一个长度为n+1的数组中, 里面是元素是 [1, n], 只有一个数字是重复的, 找到它
 *    (不允许修改数字的元素; 使用常量空间; 1 <= n <= 100000)
 *
 * 第一次读题, 以为是一个数字出现2次, 其他数字都出现了1次, 这不用数学运算就能计算出来么, 然后就被 [2,2,2,2,2] 的测试用例教育了.
 * 不允许修改数字元素+使用常量空间, 就排除了排序法、利用数组空间标记法、位存储法...
 *
 * 看了解题思路, 只有这个解符合规定: https://en.wikipedia.org/wiki/Cycle_detection#Floyd's_tortoise_and_hare
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int findDuplicate(int *nums, int numsSize) {
  // 乌龟走一步, 兔子走两步, 直到相遇
  int tortoise = nums[0], hare = nums[0];
  do {
    tortoise = nums[tortoise];
    hare = nums[nums[hare]];
  } while (tortoise != hare);

  // 相遇后, 乌龟去起点, 双方每次走一步, 相遇的地方就是环状起点
  tortoise = nums[0];

  while (tortoise != hare) {
    tortoise = nums[tortoise];
    hare = nums[hare];
  }

  return hare;
}

void test(int expect, const char *nums) {
  arrayEntry *e = arrayParse1D(nums, ARRAY_INT);

  EXPECT_EQ_INT(expect, findDuplicate(arrayValue(e), arraySize(e)));

  arrayFree(e);
}

int main(void) {
  test(2, "[1,3,4,2,2]");
  test(3, "[3,1,3,4,2]");

  // 以下是提交错误时的测试用例
  test(2, "[2,2,2,2,2]");
  test(9, "[2,5,9,6,9,3,8,9,7,1]");

  return testOutput();
}
