/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 异或后计算1的个数
 */

#include "c/test.h"

int hammingDistance(int x, int y) {
  int rtn = 0;
  x ^= y;
  while (x) {
    rtn += x & 1;
    x >>= 1;
  }
  return rtn;
}

void test(int expect, int x, int y) {
  EXPECT_EQ_INT(expect, hammingDistance(x, y));
}

int main(void) {
  test(2, 1, 4);

  return testOutput();
}
