/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 在 344 的基础上, 加上 k 的判断, 注意 k 和 len 的大小
 */

#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen(), memcpy() */
#include "c/test.h"

void swap(char *a, char *b) {
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

#define MIN(a, b) ((a) <= (b) ? (a) : (b))
char *reverseStr(char *s, int k) {
  int len = strlen(s);
  char *p1, *p2;
  for (int i = 0; i < len; i += 2 * k) {
    p1 = s + i;
    p2 = s + MIN(i + k - 1, len - 1);
    while (p1 < p2)
      swap(p1++, p2--);
  }
  return s;
}

void test(const char *expect, const char *str, int k) {
  int len = strlen(str);
  char *s = malloc(sizeof(char) * (len + 1));
  memcpy(s, str, len + 1);
  s[len] = '\0';

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, reverseStr(s, k));
}

int main(void) {
  test("bacdfeg", "abcdefg", 2);

  testOutput();
}
