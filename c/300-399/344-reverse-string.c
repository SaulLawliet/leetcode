/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * https://leetcode.com/problems/reverse-string/
 * 翻转字符串, 原地修改, 不占用空间
 * 
 * 非常基本操作
 */

#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen(), memcpy() */
#include "c/test.h"

void swap(char *a, char *b) {
  char tmp = *a;
  *a = *b;
  *b = tmp;
}

void reverseString(char* s, int sSize) {
  int p = 0, q = sSize - 1;
  while (p < q) {
    swap(&s[p++], &s[q--]);
  }
}

void test(const char *expect, const char *str) {
  int len = strlen(str);
  char *s = malloc(sizeof(char) * (len + 1));
  memcpy(s, str, len + 1);
  s[len] = '\0';
  
  reverseString(s, len);

  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, s);
}

int main(void) {
  test("olleh", "hello");

  return testOutput();
}
