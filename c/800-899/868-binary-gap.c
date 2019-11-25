/*
 * Copyright (C) 2019, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 位运算, 可以省空间, 记录下标, 计算最大距离即可
 */

#include <stdbool.h>
#include "c/test.h"

int binaryGap(int N) {
  int rt = 0, k = 0, index;
  bool find = false;
  while (N) {
    k++;
    if (N & 1) {
      if (find) {
        if (k - index > rt) rt = k - index;
      } else {
        find = true;
      }
      index = k;
    }
    N >>= 1;
  }

  return rt;
}

void test(int expect, int N) {
  EXPECT_EQ_INT(expect, binaryGap(N));
}

int main(void) {
  test(2, 22);
  test(2, 5);
  test(1, 6);
  test(0, 8);

  return testOutput();
}
