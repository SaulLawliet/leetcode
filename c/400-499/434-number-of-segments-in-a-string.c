/*
 * Copyright (C) 2019, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 注意, 计数时需要判断多个空格的情况
 */

#include <stdbool.h>
#include "c/test.h"

int countSegments(char *s) {
  int rt = 0;
  bool space = true;

  while (*s != '\0') {
    if (space) {
      while (*s == ' ') { s++; }
      space = false;
    } else {
      while (*s != ' ' && *s != '\0') { s++; }
      space = true;
      rt++;
    }
  }
  return rt;
}

void test(int expect, char *s) {
  EXPECT_EQ_INT(expect, countSegments(s));
}

int main(void) {
  test(5, "Hello, my name is John  ");
  test(0, "");
  test(0, "                ");

  return testOutput();
}
