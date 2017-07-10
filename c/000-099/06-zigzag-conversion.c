/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * v1: Math method
 *     观察规律, 会发现, 每一组的开头是 2n-2. 所以
 *     第1行: 0      0      0
 *     第2行: +1 -1  +1 -1  +1 ...
 *     第3行: +2 -2  +2 -2  +2 ...
 *     第n行: +n-1   +n-1   +n-1
 * v2: Normal Method
 *     朴素方法, 先画从上到下的竖线, 再画从下到上的斜线
 */

#include <string.h>  /* strlen() */
#include <stdlib.h>  /* malloc(), memset() */
#include <stdbool.h>
#include "../test.h"

char* convert_v1(char* s, int numRows) {
  if (numRows == 1) return s;

  int len = strlen(s);
  char *rt = malloc(sizeof(char) * (len + 1));
  char *p = rt;

  int step = numRows * 2 - 2;
  int i, j, tmp;
  for (j = 0; j != numRows; ++j) {
    for (i = 0, tmp = 0; ; tmp = ++i * step) {
      if (i != 0 && j != 0 && j != numRows - 1 && tmp - j < len)
        *p++ = s[tmp - j];
      if (tmp + j >= len)
        break;
      *p++ = s[tmp + j];
    }
  }

  *p = '\0';
  return rt;
}


const char DEFAULT = 0;
char* convert_v2(char* s, int numRows) {
  if (numRows <= 1) return s;

  int i, j;
  char **d = malloc(sizeof(char*) * numRows);

  int len = strlen(s);  /* 长度有待优化 */
  for (i = 0; i != numRows; ++i) {
    d[i] = malloc(sizeof(char) * len);
    memset(d[i], DEFAULT, sizeof(char) * len);
  }

  char *p = s;
  bool down = true;  /* true: DOWN, false: UP */
  i = 0, j = 0;
  while (*p) {
    if (down) {
      if (i == numRows - 1) {
        down = false;
      } else {
        d[i++][j] = *p++;
      }
    } else {
      if (i == 0) {
        down = true;
      } else {
        d[i--][j++] = *p++;
      }
    }
  }

  char *rt = malloc(sizeof(char) * len + 1);
  p = rt;

  for (i = 0; i != numRows; ++i) {
    for (j = 0; j != len; ++j) {
      if (d[i][j] != DEFAULT) {
        *p++ = d[i][j];
      }
    }
    free(d[i]);
  }
  free(d);

  *p = '\0';
  return rt;
}

void test(const char* expect, char* s, int numRows) {
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, convert_v1(s, numRows));
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, convert_v2(s, numRows));
}

int main(void) {
  test("PAHNAPLSIIGYIR", "PAYPALISHIRING", 3);

  return testOutput();
}
