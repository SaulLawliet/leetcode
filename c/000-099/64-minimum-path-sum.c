/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 简单的 DP 问题.
 * ps: 通过提交得知, 如果只有方法内用到的变量, 不需要动态创建, 会耗时.
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int minPathSum(int **grid, int gridSize, int *gridColSize) {
  int row = gridSize, col = *gridColSize, i, j;
  int dp[row][col];

  /* 初始化边界 */
  dp[0][0] = grid[0][0];
  for (i = 1; i < row; ++i)
    dp[i][0] = grid[i][0] + dp[i - 1][0];
  for (j = 1; j < col; ++j)
    dp[0][j] = grid[0][j] + dp[0][j - 1];

  for (i = 1; i < row; ++i)
    for (j = 1; j < col; ++j)
      dp[i][j] = grid[i][j] + (dp[i - 1][j] <= dp[i][j - 1] ? dp[i - 1][j] : dp[i][j - 1]);

  return dp[row - 1][col - 1];
}

void test(int expect, const char *s) {
  arrayEntry *e = arrayParse2D(s, ARRAY_INT);

  EXPECT_EQ_INT(expect, minPathSum(arrayValue(e), arrayRow(e), arrayCols(e)));

  arrayFree(e);
}

int main(void) {
  test(7,
       "["
       "[1,3,1],"
       "[1,5,1],"
       "[4,2,1]"
       "]");

  return testOutput();
}
