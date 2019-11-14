/*
 * Copyright (C) 2019, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 最短的路线有多种走法, 为了统一, 我们这里默认是先上下后左右
 * 注意: 有个例外是移动到'z'时, 先左后下
 */

#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */
#include "c/test.h"

char *alphabetBoardPath(char *target) {
  // 最长的步数是 'z' -> 'e', 共9步, 加上'!', 一共10个
  size_t len = strlen(target);
  char *path = malloc(sizeof(char) * (10 * len + 1));
  char *p = path;
  int x1 = 0, y1 = 0, x2, y2, v;
  for (size_t i = 0; i < len; i++) {
    v = target[i] - 'a';
    x2 = v / 5, y2 = v % 5;

    if (target[i] == 'z') {
      // 先左后下
      while (y2 < y1) { y1--; *p++ = 'L'; }
      while (x2 > x1) { x1++; *p++ = 'D'; }
    } else {
      // 先上下后左右
      while (x2 > x1) { x1++; *p++ = 'D'; }
      while (x2 < x1) { x1--; *p++ = 'U'; }
      while (y2 > y1) { y1++; *p++ = 'R'; }
      while (y2 < y1) { y1--; *p++ = 'L'; }
    }

    *p++ = '!';
  }
  *p++ = '\0';
  return path;
}

void test(const char *expect, char *target) {
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, alphabetBoardPath(target));
}

int main(void) {
  test("DDR!UURRR!!DDD!", "leet");
  test("RR!DDRR!UUL!R!", "code");

  testOutput();
}
