/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 递归解法, 转换成 0-indexed 会更好理解, N 是个无用的参数
 *  0      1
 *  | \    | \
 *  0  1   1  0
 *  =  ^   =  ^
 */

#include "c/test.h"

int cal(int k) {
  if (k == 0) return 0;

  if (k % 2 == 1)
    return 1 ^ cal(k/2);
  else
    return cal(k/2);
}

int kthGrammar(int N, int K) {
  // 将 K 从 1-indexed 转化成 0-indexed
  return cal(--K);
}

void test(int expect, int N, int K) {
  EXPECT_EQ_INT(expect, kthGrammar(N, K));
}

int main(void) {
  test(0, 1, 1);
  test(0, 2, 1);
  test(1, 2, 2);
  test(1, 4, 5);

  return testOutput();
}
