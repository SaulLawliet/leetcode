/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 排列组合的知识点
 */

#include "c/test.h"

int countNumbersWithUniqueDigits(int n) {
  int count = 1;
  int v = 1;
  for (int i = 1; i <= n; i++) {
    v *= 11 - i - (i == 1 ? 1 : 0);
    count += v;
  }
  return count;
}

void test(int expect, int n) {
  EXPECT_EQ_INT(expect, countNumbersWithUniqueDigits(n));
}

int main(void) {
  test(91, 2);

  return testOutput();
}
