/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * https://leetcode.com/articles/longest-palindromic-substring/#approach-4-expand-around-center-accepted
 */

#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen(), strncpy() */
#include "c/test.h"

int expandAroundCenter(char *s, int l, size_t r) {
  while (l >=0 && r < strlen(s) && s[l] == s[r]) {
    l--;
    r++;
  }
  return r - l - 1;  /* r - l + 1 - 2 */
}

#define MAX(a, b) (((a) > (b)) ? (a) : (b))
char *longestPalindrome(char *s) {
  int begin = 0, end = 0;
  size_t i;

  for (i = 0; i != strlen(s); ++i) {
    int len1 = expandAroundCenter(s, i, i);
    int len2 = expandAroundCenter(s, i, i + 1);
    int len = MAX(len1, len2);
    if (len > end - begin) {
      begin = i - (len - 1) / 2;
      end = i + len / 2;
    }
  }
  int size = end - begin + 1;
  char *rt = malloc(sizeof(char) * (size + 1));
  rt[size] = '\0';
  return strncpy(rt, &s[begin], size);
}

void test(const char *expect, char *s) {
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, longestPalindrome(s));
}

/*
  Input: "babad"
  Output: "bab"
  Note: "aba" is also a valid answer.

  Input: "cbbd"
  Output: "bb"
 */
int main() {
  test("aba", "babad");
  test("bb", "cbbd");

  return testOutput();
}
