/*
 * Copyright (C) 2023, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 直观感觉这道题不应该算中等难度, 解题的过程中有两个问题
 * 1. hash越界
 *    解决方法: 对10000007取模
 * 2. hash一致但数组不相等
 *    解决方法: hash一致的情况也继续对比数组是否相等
 */

#include "c/data-structures/array.h"
#include "c/test.h"

int equalPairs(int **grid, int gridSize, int *gridColSize) {
  int *rowHash = malloc(sizeof(int) * gridSize);
  int *colHash = malloc(sizeof(int) * gridSize);

  for (int i = 0; i < gridSize; i++) {
    rowHash[i] = 1;
    colHash[i] = 1;
  }

  for (int i = 0; i < gridSize; i++) {
    for (int j = 0; j < gridSize; j++) {
      rowHash[i] = (rowHash[i] * 31 + grid[i][j]) % 10000007;
      colHash[i] = (colHash[i] * 31 + grid[j][i]) % 10000007;
    }
  }

  int rt = 0;
  for (int i = 0; i < gridSize; i++) {
    for (int j = 0; j < gridSize; j++) {
      if (rowHash[i] == colHash[j]) {
        // hash 一致, 也要对比每一项
        for (int k = 0; k < gridSize; k++) {
          if (grid[i][k] != grid[k][j]) break;
          if (k == gridSize - 1) rt++;
        }
      }
    }
  }

  free(colHash);
  free(rowHash);

  return rt;
}

void test(int except, char *grid) {
  arrayEntry *e = arrayParse2D(grid, ARRAY_INT);
  EXPECT_EQ_INT(except, equalPairs(arrayValue(e), arrayRow(e), arrayCols(e)));
  arrayFree(e);
}

int main(void) {
  test(1, "[[3,2,1],[1,7,6],[2,7,7]]");
  test(3, "[[3,1,2,2],[1,4,4,5],[2,4,2,2],[2,4,2,2]]");
  test(0, "[[2,1],[3,32]]");

  return testOutput();
}
