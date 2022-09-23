/*
 * Copyright (C) 2022, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * f(1) = 1
 * f(2) = (f(1) << bitLen(2)) + 2
 * f(3) = (f(2) << bitLen(3)) + 3
 * ...
 * f(n) = (f(n-1) << bitLen(n)) + n
 */

#include <math.h>
#include <stdint.h>
#include "c/test.h"

int concatenatedBinary(int n) {
  int64_t res = 1;
  int count = 1;
  for (int i = 2; i <= n; i++) {
    if ((i & (i - 1)) == 0) count++;  /** 参考别人的写法, 用在这里很巧妙 */
    res = ((res << count) | i) % 1000000007;
  }
  return res;
}

void test(int expect, int n) {
  EXPECT_EQ_INT(expect, concatenatedBinary(n));
}

int main(void) {
  test(1, 1);
  test(27, 3);
  test(505379714, 12);

  return testOutput();
}
