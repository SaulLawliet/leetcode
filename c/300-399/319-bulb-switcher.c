/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 感觉是个数学问题，但还是先用了朴素方法解，结果超时
 * 后来找了下规律，发现结果是 sqrt(n)
 */

#include <math.h>  /* sqrt() */
#include "../test.h"
#include "../data-structures/array.h"

int bulbSwitch(int n) {
  return (int)sqrt(n);
}

void test(int expect, int n) {
  EXPECT_EQ_INT(expect, bulbSwitch(n));
}

int main(void) {
  test(1, 3);
  test(316, 99999);

  return testOutput();
}
