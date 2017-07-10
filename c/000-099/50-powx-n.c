/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 第一次的时候没有考虑 n 为负数的情况
 * 测试数据里有 n == INT_MIN, 所以当 n < 0 时, 需要转换了一下.
 */

#include <math.h>    /* pow() */
#include <limits.h>  /* INT_MIN */
#include "../test.h"

double myPow(double x, int n) {
  if (n == 0) return 1;
  if (n < 0) return 1 / myPow(x, -(n+1)) / x;

  double tmp = myPow(x, n/2);
  return (n % 2 == 0 ? 1 : x) * tmp * tmp;
}

void test(double x, int n) {
  EXPECT_EQ_DOUBLE(pow(x, n), myPow(x, n));
}

int main(void) {
  test(3.0, 2);
  test(-3.0, 2);
  test(INT_MIN, 3);
  test(INT_MAX, 3);

  return testOutput();
}
