/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 明显动态规划, 按照判断元音字母的下一个是什么的思路找下去, 没有结果
 * 于是反过来在思考一番, 则有有规律可寻, 具体见下方注释
 *
 * 第一次提交时int越界, 在网站自定义了几个值对比, 发现我的答案明显大于标准答案很多.
 * 仔细身体才发现 "10^9 + 7"
 * 审题不仔细...
 *
 * AC 后发现耗时 12ms, 看到最佳是 4ms, 于是想着优化了一番
 * 1. 从 2层循环 换成 1层循环, => 8ms
 * 2. 实在想不出结果, 看了4ms的答案, 把数据类型从 long 换成 unsigned int => 4ms
 */

#include "c/test.h"

int MOD = 1e9 + 7; /* Since the answer may be too large, return it modulo 10^9 + 7. */
int countVowelPermutation(int n) {
  if (n <= 0) return 0;
  if (n == 1) return 5;

  unsigned int dp[2][5] = {{1, 1, 1, 1, 1}};
  unsigned int *p, *p1 = dp[0], *p2 = dp[1];

  for (int i = 1; i < n; i++) {
    /* 0, 1, 2, 3, 4 */
    /* a, e, i, o, u */

    /* a = e + i + u */
    p2[0] = (p1[1] + p1[2] + p1[4]) % MOD;
    /* e = a + i */
    p2[1] = (p1[0] + p1[2]) % MOD;
    /* i = e + o */
    p2[2] = (p1[1] + p1[3]) % MOD;
    /* o = i */
    p2[3] = p1[2];
    /* u = i + o */
    p2[4] = (p1[2] + p1[3]) % MOD;

    /* 交换 p1, p2 */
    p = p1; p1 = p2; p2 = p;
  }

  return (p1[0] + p1[1] + p1[2] + p1[3] + p1[4]) % MOD;
}

void test(int expect, int n) {
  EXPECT_EQ_INT(expect, countVowelPermutation(n));
}

int main(void) {
  test(5, 1);
  test(10, 2);
  test(68, 5);

  test(18208803, 144);

  return testOutput();
}
