/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 先说几个特殊情况:
 *   1. 0是会文数
 *   2. 负数不是回文数
 *   3. 可以整除10的不是回文数
 * 其他情况下, 把 x 切成两半, 一半反转, 另一半正常,
 * 当两个数相等(1221) 或 较大数除10等于较小数(121), 是回文数. 反之不是
 */

#include <stdbool.h>
#include "c/test.h"

bool isPalindrome(int x) {
  if (x == 0) return true;
  if (x < 0 || x % 10 == 0) return false;
  int tmp = 0;
  while (x > tmp) {
    tmp = tmp * 10 + x % 10;
    x /= 10;
  }
  return x == tmp || x == tmp / 10;
}

void test(bool expect, int x) {
  EXPECT_EQ_INT(expect, isPalindrome(x));
}

int main(void) {
  test(true, 0);
  test(true, 11);
  test(true, 121);
  test(true, 1221);

  test(false, -1);
  test(false, 1211);
  test(false, 10);

  return testOutput();
}
