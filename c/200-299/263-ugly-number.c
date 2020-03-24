/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 注意需要单独判断 num=0 的情况.
 */

#include <stdbool.h>
#include "c/test.h"

bool isUgly(int num) {
  if (num == 0) return false;
  while (num % 2 == 0) num /= 2;
  while (num % 3 == 0) num /= 3;
  while (num % 5 == 0) num /= 5;

  return num == 1;
}


void test(bool expect, int num) {
  EXPECT_EQ_INT(expect, isUgly(num));
}

int main(void) {
  test(true, 6);
  test(true, 8);
  test(false, 14);

  return testOutput();
}
