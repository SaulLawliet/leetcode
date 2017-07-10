/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 牛顿法: 循环调用 x = (x + S/x) / 2
 */

#include <stdint.h>  /* int64_t */
#include <stdbool.h>
#include "../test.h"

bool isPerfectSquare(int num) {
  int64_t x = num;  /* x为int时, 会溢出 */
  while (x * x > num)
    x = (x + num/x) / 2;
  return x * x == num;
}

void test(bool expect, int num) {
  EXPECT_EQ_INT(expect, isPerfectSquare(num));
}

/*
  Input: 16
  Returns: True

  Input: 14
  Returns: False
 */
int main(void) {
  test(true, 16);
  test(false, 14);

  return testOutput();
}
