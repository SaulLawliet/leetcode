/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 如果是'0','1'间隔的数, 在右移1位后, 再与原来的数进行异或(XOR)运算, 得到的将是一个全是'1'的数
 * 检测全是1的数就很容易了, 直接 (x & x+1) == 0
 */

#include <limits.h>
#include <stdbool.h>
#include "c/test.h"

bool hasAlternatingBits(int n) {
  n ^= n >> 1;
  return n == INT_MAX || !(n & (n + 1));
}

void test(bool expect, int n) {
  EXPECT_EQ_INT(expect, hasAlternatingBits(n));
}

int main(void) {
  test(true, 5);
  test(false, 7);
  test(false, 11);
  test(true, 10);

  test(true, 1431655765); /* Leecode 会有 溢出的检测 */

  return testOutput();
}
