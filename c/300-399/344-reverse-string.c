/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 这是基本操作
 */

#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen(), memcpy() */
#include "c/test.h"

void swap(char *a, char *b) {
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

char *reverseString(char *s) {
  char *p1 = s,
       *p2 = s + strlen(s) - 1;
  while (p1 < p2)
    swap(p1++, p2--);
  return s;
}

void test(const char *expect, const char *str) {
  int len = strlen(str);
  char *s = malloc(sizeof(char) * (len + 1));
  memcpy(s, str, len + 1);
  s[len] = '\0';

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, reverseString(s));
}

int main(void) {
  test("olleh", "hello");

  return testOutput();
}
