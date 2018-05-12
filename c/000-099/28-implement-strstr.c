/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 暴力解决.
 */

#include <string.h> /* strlen(), strstr() */
#include "c/test.h"

int strStr(char *haystack, char *needle) {
  int len1 = strlen(haystack),
      len2 = strlen(needle);
  if (len2 > len1) return -1;

  int i, j, k;
  for (i = 0; i < len1 - len2 + 1; i++) {
    for (k = i, j = 0; haystack[k] == needle[j] && j < len2; k++, j++) {}
    if (j == len2) return i;
  }
  return -1;
}

void test(char *haystack, char *needle) {
  int expect = -1;
  char* pos = strstr(haystack, needle);
  if (pos) expect = pos - haystack;

  EXPECT_EQ_INT(expect, strStr(haystack, needle));
}

int main(void) {
  test("Hello World.", "World");
  test("Hello World.", "Word");

  return testOutput();
}
