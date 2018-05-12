/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 需要考虑 int 的边界.
 */

#include "c/test.h"

int reverse(int x) {
  int rt = 0, tmp;
  while (x) {
    tmp = rt * 10 + x % 10;
    if ((tmp / 10) != rt) return 0;
    rt = tmp;
    x /= 10;
  }
  return rt;
}

void test(int expect, int x) {
  EXPECT_EQ_INT(expect, reverse(x));
}

/*
  Example1: x = 123, return 321
  Example2: x = -123, return -321
 */
int main(void) {
  test(321, 123);
  test(-321, -123);

  return testOutput();
}
