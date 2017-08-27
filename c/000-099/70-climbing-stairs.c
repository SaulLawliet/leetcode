/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 实际答案就是斐波那契数列
 * 一开始用递归解, 但超时了
 * 后改为非递归
 */

#include "../test.h"

int climbStairs(int n) {
  int a = 1, b = 1;
  for (int i = 1; i < n; i++) {
    a = a + b;
    b = a - b;
  }
  return a;
}

void test(int expect, int n) {
  EXPECT_EQ_INT(expect, climbStairs(n));
}

int main(void) {
  test(1, 1);
  test(2, 2);
  test(89, 10);

  return testOutput();
}
