/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 先找到' ' 和 '\0' 的位置, 然后开始逆转
 */

#include <string.h> /* strchr(), strlen(s) */

#include "c/test.h"

void swap(char *a, char *b) {
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

char *reverseWords(char *s) {
  char *p1 = s, *p2, *c;
  do {
    c = strchr(p1, ' ');
    p2 = (c ? c - 1 : s + strlen(s) - 1);
    while (p1 < p2)
      swap(p1++, p2--);
    p1 = c + 1;
  } while (c);
  return s;
}

void test(const char *expect, const char *str) {
  int len = strlen(str);
  char *s = malloc(sizeof(char) * (len + 1));
  memcpy(s, str, len + 1);
  s[len] = '\0';

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, reverseWords(s));
}

int main(void) {
  test("s'teL ekat edoCteeL tsetnoc",
       "Let's take LeetCode contest");

  testOutput();
}
