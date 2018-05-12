/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 找到一个为 '1' 的位置，然后按4个方向开始感染
 */

#include "c/data-structures/array.h"
#include "c/test.h"

void infect(char **grid, int gridRowSize, int gridColSize, int x, int y) {
  if (grid[x][y] == '1') {
    grid[x][y] = '0';
    if (x > 0)
      infect(grid, gridRowSize, gridColSize, x-1, y);
    if (x < gridRowSize - 1)
      infect(grid, gridRowSize, gridColSize, x+1, y);
    if (y > 0)
      infect(grid, gridRowSize, gridColSize, x, y-1);
    if (y < gridColSize - 1)
      infect(grid, gridRowSize, gridColSize, x, y+1);
  }
}

int numIslands(char **grid, int gridRowSize, int gridColSize) {
  int rtn = 0;
  for (int i = 0; i < gridRowSize; ++i) {
    for (int j = 0; j < gridColSize; ++j) {
      if (grid[i][j] == '1') {
        ++rtn;
        infect(grid, gridRowSize, gridColSize, i, j);
      }
    }
  }
  return rtn;
}

void test(int expect, const char *str) {
  arrayEntry *e = arrayParse(str, ARRAY_CHAR);

  EXPECT_EQ_INT(expect, numIslands(arrayValue(e), arrayRow(e), arrayCol(e)));

  arrayFree(e);
}

int main(void) {
  test(1,
       "["
       "[1,1,1,1,0],"
       "[1,1,0,1,0],"
       "[1,1,0,0,0],"
       "[0,0,0,0,0]"
       "]");

  test(3,
       "["
       "[1,1,0,0,0],"
       "[1,1,0,0,0],"
       "[0,0,1,0,0],"
       "[0,0,0,1,1]"
       "]");

  return testOutput();
}
