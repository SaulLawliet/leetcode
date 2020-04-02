/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 异或后计算1的个数
 */

#include "c/test.h"

int hammingDistance(int x, int y) {
  int count = 0;
  for (x ^= y; x; x >>= 1) {
    count += x & 1;
  }
  return count;
}

void test(int expect, int x, int y) {
  EXPECT_EQ_INT(expect, hammingDistance(x, y));
}

int main(void) {
  test(2, 1, 4);

  return testOutput();
}
