/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 递归解法
 */

#include <stdbool.h>
#include "../test.h"

bool matchFirst(char* s, char* p) {
  return (*p == '.' && *s != '\0') || *s == *p;
}

bool isMatch(char* s, char* p) {
  if (*p == '\0') return *s == '\0';

  if (*(p+1) != '*') {
    if (!matchFirst(s, p)) return false;
    return isMatch(s+1, p+1);
  } else {
    do {
      if (isMatch(s, p+2)) return true;  /* 先尝试匹配'_*'之后的部分 */
    } while (matchFirst(s++, p));
    return false;
  }
}

void test(bool expect, char* s, char* p) {
  EXPECT_EQ_INT(expect, isMatch(s, p));
}

int main(void) {
  test(false, "aa", "a");
  test(true,  "aa", "aa");
  test(false, "aaa", "aa");
  test(true, "aa", "a*");
  test(true, "aa", ".*");
  test(true, "ab", ".*");
  test(true, "aab", "c*a*b*");

  return testOutput();
}
