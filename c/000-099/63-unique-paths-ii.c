/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 相比较'62', 这里增加了障碍物, 只要设置障碍物的点为0, 其他规则照旧
 */

#include "../test.h"
#include "../data-structures/array.h"

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridRowSize, int obstacleGridColSize) {
  //       m    n
  int grid[100][100];  /* 题目已说上限, 就不动态创建了 */
  if (obstacleGrid[0][0] == 1) return 0;
  grid[0][0] = 1;

  int i, j;
  for (i = 1; i < obstacleGridRowSize; i++)
    grid[i][0] = obstacleGrid[i][0] == 0 ? grid[i-1][0] : 0;

  for (i = 1; i < obstacleGridColSize; i++)
    grid[0][i] = obstacleGrid[0][i] == 0 ? grid[0][i-1] : 0;

  for (i = 1; i < obstacleGridRowSize; i++)
    for (j = 1; j < obstacleGridColSize; j++)
      grid[i][j] = obstacleGrid[i][j] == 0 ? grid[i-1][j] + grid[i][j-1] : 0;

  return grid[obstacleGridRowSize-1][obstacleGridColSize-1];
}

void test(int expect, const char* s) {
  size_t obstacleGridRowSize, obstacleGridColSize;
  int** obstacleGrid = array2DNewByStr(s, &obstacleGridRowSize, &obstacleGridColSize);
  EXPECT_EQ_INT(expect, uniquePathsWithObstacles(obstacleGrid, obstacleGridRowSize, obstacleGridColSize));

  array2DFree(obstacleGrid, obstacleGridRowSize);
}

int main(void) {
  test(2, "[[0, 0, 0], [0, 1, 0], [0, 0, 0]]");

  return testOutput();
}
