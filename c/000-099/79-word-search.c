/*
 * Copyright (C) 2018, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 基本的深度优先搜索解法
 * 讨论区学到的小技巧: a ^ x ^ x = a
 */

#include <stdbool.h>
#include "c/data-structures/array.h"
#include "c/test.h"

bool search(char **board, int boardRowSize, int boardColSize, int i, int j, char *word) {
  if (*word == '\0') return true;
  if (i < 0 || i >= boardRowSize || j < 0 || j >= boardColSize) return false;
  if (board[i][j] != *word) return false;
  board[i][j] ^= 0xFF;
  bool exist =
      search(board, boardRowSize, boardColSize, i + 1, j, word + 1) ||
      search(board, boardRowSize, boardColSize, i - 1, j, word + 1) ||
      search(board, boardRowSize, boardColSize, i, j + 1, word + 1) ||
      search(board, boardRowSize, boardColSize, i, j - 1, word + 1);
  board[i][j] ^= 0xFF;
  return exist;
}

bool exist(char **board, int boardRowSize, int boardColSize, char *word) {
  for (int i = 0; i < boardRowSize; ++i)
    for (int j = 0; j < boardColSize; ++j)
      if (search(board, boardRowSize, boardColSize, i, j, word))
        return true;

  return false;
}

void test(const char *board, bool expect, char *word) {
  arrayEntry *e = arrayParse2D(board, ARRAY_CHAR);

  EXPECT_EQ_INT(expect, exist(arrayValue(e), arrayRow(e), arrayCol(e), word));

  arrayFree(e);
}

int main(void) {
  const char *board =
      "["
      "[A,B,C,E],"
      "[S,F,C,S],"
      "[A,D,E,E]"
      "]";
  test(board, true, "ABCCED");
  test(board, true, "SEE");
  test(board, false, "ABCB");

  return testOutput();
}
