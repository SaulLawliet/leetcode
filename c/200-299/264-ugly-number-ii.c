/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 考虑一下规则, 下一个 uglyNumber 一定是之前某一个 uglyNumber 乘2, 乘3, 乘5 得到的.
 * 剩下就是动态规划的问题了.
 */

#include "c/test.h"

int min(int a, int b, int c) {
  int tmp = a <= b ? a : b;
  return tmp <= c ? tmp : c;
}

int nthUglyNumber(int n) {
  if (n == 0) return 0;
  int dp[n];
  dp[0] = 1; /* 初始值为0 */
  int p2 = 0, p3 = 0, p5 = 0;
  for (int i = 1; i < n; i++) {
    dp[i] = min(dp[p2] * 2, dp[p3] * 3, dp[p5] * 5);
    if (dp[p2] * 2 == dp[i]) p2++;
    if (dp[p3] * 3 == dp[i]) p3++;
    if (dp[p5] * 5 == dp[i]) p5++;
  }
  return dp[n - 1];
}

void test(int expect, int n) {
  EXPECT_EQ_INT(expect, nthUglyNumber(n));
}

int main(void) {
  test(12, 10);

  test(15, 11);

  return testOutput();
}
