/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 简单的问题, 描述的这么复杂, 实际就是偏移字符串
 * 需要考虑的是超出字符串的部分需要取余
 */

#include <string.h> /* strlen() */
#include "c/data-structures/array.h"
#include "c/test.h"

char *stringShift(char *s, int **shift, int shiftSize, int *shiftColSize) {
  int len = strlen(s);
  char *rtn = malloc(sizeof(char) * (len + 1));
  rtn[len] = '\0';

  int move = 0;
  for (int i = 0; i < shiftSize; i++)
    move += (shift[i][0] > 0 ? 1 : -1) * shift[i][1];

  /* 当 move 为负数时, 需要处理一下 */
  move %= len;
  if (move < 0) move += len;

  for (int i = 0; i < len; i++)
    rtn[(i + move) % len] = s[i];

  return rtn;
}

void test(const char *expect, char *s, char *shift) {
  arrayEntry *e = arrayParse2D(shift, ARRAY_INT);
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, stringShift(s, arrayValue(e), arrayRow(e), arrayCols(e)));
  arrayFree(e);
}

int main(void) {
  test("cab", "abc", "[[0,1],[1,2]]");
  test("efgabcd", "abcdefg", "[[1,1],[1,1],[0,2],[1,3]]");

  test("hcjwpdh", "wpdhhcj", "[[0,7],[1,7],[1,0],[1,3],[0,3],[0,6],[1,2]]");
  test("qpifxqgwki", "xqgwkiqpif", "[[1,4],[0,7],[0,8],[0,7],[0,6],[1,3],[0,1],[1,7],[0,5],[0,6]]");

  return testOutput();
}
