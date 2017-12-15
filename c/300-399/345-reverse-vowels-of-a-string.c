/*
 * Copyright (C) 2017, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 两个指针, 往中间查找
 */

#include <stdbool.h>
#include "../test.h"

void swap(char *a, char *b) {
  char tmp = *a; *a = *b; *b = tmp;
}

char *reverseVowels(char *s) {
  const char *vowels = "aeiouAEIOU";

  char *rtn = malloc(sizeof(char) * (strlen(s) + 1));
  strcpy(rtn, s);
  char *p1 = rtn,
       *p2 = rtn+strlen(s)- 1;

  while (p1 < p2) {
    if (!strchr(vowels, *p1)) {
      p1++; continue;
    }
    if (!strchr(vowels, *p2)) {
      p2--; continue;
    }
    swap(p1++, p2--);
  }

  return rtn;
}

void test(const char *expect, char *s) {
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, reverseVowels(s));
}

int main(void) {
  test("holle", "hello");
  test("leotcede", "leetcode");
  test(".", ".");
  test("Aa", "aA");

  return testOutput();
}
