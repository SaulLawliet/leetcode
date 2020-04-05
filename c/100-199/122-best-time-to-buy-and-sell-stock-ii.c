/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 直觉就是所有相邻两个数的差为正数时的累加.
 * 提交竟然过了.
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int maxProfit(int *prices, int pricesSize) {
  int max = 0;
  for (int i = 1; i < pricesSize; i++) {
    if (prices[i] > prices[i - 1]) {
      max += prices[i] - prices[i - 1];
    }
  }
  return max;
}

void test(int expect, char *s) {
  arrayEntry *e = arrayParse1D(s, ARRAY_INT);
  EXPECT_EQ_INT(expect, maxProfit(arrayValue(e), arraySize(e)));
  arrayFree(e);
}

int main(void) {
  test(7, "[7,1,5,3,6,4]");
  test(4, "[1,2,3,4,5]");
  test(0, "[7,6,4,3,1]");

  return testOutput();
}
