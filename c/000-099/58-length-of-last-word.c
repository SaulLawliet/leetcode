/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 很简单的问题, 但第一次提交时, 没有考虑结尾有空格的情况.
 */

#include "c/test.h"

int lengthOfLastWord(char *s) {
  int length = 0;
  char *p = s;
  while (*p) {
    if (*p++ == ' ') {
      while (*p == ' ') p++;
      if (*p) length = 0;
    } else {
      length++;
    }
  }
  return length;
}


void test(int expect, char *s) {
  EXPECT_EQ_INT(expect, lengthOfLastWord(s));
}

int main(void) {
  test(5, "Hello World");

  test(1, "a ");

  return testOutput();
}
