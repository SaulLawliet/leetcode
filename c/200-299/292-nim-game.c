/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 从1开始模拟你的行为, 你会发现代码出乎意料的简单.
 */

#include <stdbool.h>
#include "c/test.h"

bool canWinNim(int n) {
  return n % 4 > 0;
}

void test(bool expect, int n) {
  EXPECT_EQ_INT(expect, canWinNim(n));
}

int main(void) {
  test(false, 4);

  return testOutput();
}
