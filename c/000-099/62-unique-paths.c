/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 最简单的 DP 问题, 设置好边界, 其他每个点 = 左边 + 上边
 */

#include "../test.h"

int uniquePaths(int m, int n) {
  //       m    n
  int grid[100][100];  /* 题目已说上限, 就不动态创建了 */
  grid[0][0] = 1;

  int i, j;
  for (i = 1; i < m; i++) grid[i][0] = 1;
  for (i = 1; i < n; i++) grid[0][i] = 1;

  for (i = 1; i < m; i++)
    for (j = 1; j < n; j++)
      grid[i][j] = grid[i-1][j] + grid[i][j-1];

  return grid[m-1][n-1];
}

void test(int expect, int m, int n) {
  EXPECT_EQ_INT(expect, uniquePaths(m, n));
}

int main(void) {
  test(28, 3, 7);

  return testOutput();
}
