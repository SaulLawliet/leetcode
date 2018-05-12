/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 模拟 5 + 3 的计算:
 *   1 0 1
 *   1 1
 *   - - - - - - -
 *   1 1 0      -> a
 *   1 0      -> b
 *   - - - - - - -
 *   1 0 0
 *   1 0 0
 *   - - - - - - -
 *   0
 *   1 0 0 0
 *   - - - - - - -
 *   1 0 0 0
 *   0
 *   - - - - - - -
 *   1 0 0 0
 */

#include "c/test.h"

int getSum(int a, int b) {
  int tmp;
  while (b) {
    tmp = a;
    a = tmp ^ b;
    b = (tmp & b) << 1;
  }
  return a;
}

void test(int a, int b) {
  EXPECT_EQ_INT(a+b, getSum(a, b));
}

int main(void) {
  test(3, 5);

  return testOutput();
}
