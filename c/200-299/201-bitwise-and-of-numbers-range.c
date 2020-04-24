/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 朴素方法提交后超时, 那这就是其他的解法了
 * 没有思路...
 * 看了讨论后, 终于理解了
 * 这样想象, 把所有的数字竖着排开, 如果某一位有0, 则从结果来看这一位肯定为0
 * 理论是这样
 * 但从代码的角度来看
 * 就是, 两个数字不断右移, 记录移动的次数, 直到两个数字相等停止
 * 其实就是求两个数最高位相等部分, 然后其他地方填0
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int rangeBitwiseAnd(int m, int n) {
  int count = 0;
  while (m != n) {
    m >>= 1, n >>= 1, count++;
  }
  return m << count;
}

void test(int expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);
  int *nums = (int *)arrayValue(e);
  EXPECT_EQ_INT(expect, rangeBitwiseAnd(nums[0], nums[1]));
  arrayFree(e);
}

int main(void) {
  test(4, "[5,7]");
  test(0, "[0,1]");

  return testOutput();
}
