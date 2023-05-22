/*
 * Copyright (C) 2023, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 最开始想用字符串分割来弄, 但 c 处理起来比较麻烦, 还是朴素方法好写一点.
 * 第一次提交的时候, 没有考虑 int 会越界, 后改用 int64_t 就可以了.
 */

#include "c/test.h"

int compareVersion(char *version1, char *version2) {
  int64_t i1, i2;
  while (*version1 || *version2) {
    i1 = 0;
    while (*version1 && *version1 != '.') {
      i1 = i1 * 10 + *version1 - '0';
      version1++;
    }
    if (*version1 == '.') version1++;

    i2 = 0;
    while (*version2 && *version2 != '.') {
      i2 = i2 * 10 + *version2 - '0';
      version2++;
    }
    if (*version2 == '.') version2++;

    if (i1 != i2) return i1 < i2 ? -1 : 1;
  }

  return 0;
}

void test(int expect, char *version1, char *version2) {
  EXPECT_EQ_INT(expect, compareVersion(version1, version2));
}

int main(void) {
  test(0, "1.01", "1.001");
  test(0, "1.0", "1.0.0");
  test(-1, "0.1", "1.1");

  return testOutput();
}
