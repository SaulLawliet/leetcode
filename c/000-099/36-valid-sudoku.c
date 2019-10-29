/*
 * Copyright (C) 2019, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * v1: 依次遍历每个格子, 先搜索向下, 再搜索向右, 最后搜索当前方阵
 *     (搜索当前方阵时会有重复的搜索, 处理比较麻烦, 先忽略)
 * v2: 使用额外的空间来存储 列/行/方块 的数字出现的次数, 当大于1时, 表示失败
 */

#include <stdbool.h>
#include <string.h> /* memset() */
#include "c/data-structures/array.h"
#include "c/test.h"

int N = 3;
bool isValidSudoku_v1(char **board, int boardSize, int *boardColSize) {
  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardColSize[i]; j++) {
      if (board[i][j] == '.')
        continue;

      // search down
      for (int ii = i + 1; ii < boardSize; ii++) {
        if (board[i][j] == board[ii][j])
          return false;
      }

      // search right
      for (int jj = j + 1; jj < boardColSize[i]; jj++) {
        if (board[i][j] == board[i][jj])
          return false;
      }

      // serach square
      for (int ii = i; ii < (i / N + 1) * N; ii++) {
        for (int jj = j / N * N; jj < (j / N + 1) * N; jj++) {
          if (ii != i && jj != j && board[i][j] == board[ii][jj])
            return false;
        }
      }
    }
  }
  return true;
}

bool isValidSudoku_v2(char **board, int boardSize, int *boardColSize) {
  int row[9][9], col[9][9], sqr[3][3][9];

  memset(row, 0, sizeof(row[0][0]) * 9 * 9);
  memset(col, 0, sizeof(col[0][0]) * 9 * 9);
  memset(sqr, 0, sizeof(sqr[0][0][0]) * 3 * 3 * 9);

  for (int i = 0; i < boardSize; i++) {
    for (int j = 0; j < boardColSize[i]; j++) {
      if (board[i][j] == '.')
        continue;
      int n = board[i][j] - '1';  // 一共9个数

      if (row[i][n]++ != 0 || col[j][n]++ != 0 || sqr[i / 3][j / 3][n]++ != 0) {
        return false;
      }
    }
  }
  return true;
}

void test(bool except, char *board) {
  arrayEntry *e = arrayParse2D(board, ARRAY_CHAR);

  EXPECT_EQ_INT(except, isValidSudoku_v1(arrayValue(e), arrayRow(e), arrayCols(e)));
  EXPECT_EQ_INT(except, isValidSudoku_v2(arrayValue(e), arrayRow(e), arrayCols(e)));

  arrayFree(e);
}

int main(void) {
  test(true,
       "[ \
      [5, 3, ., ., 7, ., ., ., .], \
      [6, ., ., 1, 9, 5, ., ., .], \
      [., 9, 8, ., ., ., ., 6, .], \
      [8, ., ., ., 6, ., ., ., 3], \
      [4, ., ., 8, ., 3, ., ., 1], \
      [7, ., ., ., 2, ., ., ., 6], \
      [., 6, ., ., ., ., 2, 8, .], \
      [., ., ., 4, 1, 9, ., ., 5], \
      [., ., ., ., 8, ., ., 7, 9] \
      ]");

  test(false,
       "[ \
      [8, 3, ., ., 7, ., ., ., .], \
      [6, ., ., 1, 9, 5, ., ., .], \
      [., 9, 8, ., ., ., ., 6, .], \
      [8, ., ., ., 6, ., ., ., 3], \
      [4, ., ., 8, ., 3, ., ., 1], \
      [7, ., ., ., 2, ., ., ., 6], \
      [., 6, ., ., ., ., 2, 8, .], \
      [., ., ., 4, 1, 9, ., ., 5], \
      [., ., ., ., 8, ., ., 7, 9] \
      ]");

  testOutput();
}
