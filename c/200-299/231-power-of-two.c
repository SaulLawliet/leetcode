/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 是2的几次方数的特点是首位是'1', 其他全是'0', 所以用 x & x-1 的技巧就能判断出
 */

#include <stdbool.h>
#include "c/test.h"

bool isPowerOfTwo(int n) {
  return n > 0 && !(n & n - 1);
}

void test(bool expect, int n) {
  EXPECT_EQ_INT(expect, isPowerOfTwo(n));
}

int main(void) {
  test(true, 1);
  test(true, 16);
  test(false, 218);

  return testOutput();
}
