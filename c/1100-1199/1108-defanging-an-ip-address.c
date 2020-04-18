/*
 * Copyright (C) 2020, Saul Lawliet <october dot sunbathe at gmail dot com>
 * All rights reserved.
 *
 * 基本的字符还替换问题.
 */

#include <stdlib.h> /* malloc() */
#include <string.h> /* strlen() */
#include "c/test.h"

char *defangIPaddr(char *address) {
  char *rtn = malloc(sizeof(char) * (strlen(address) + 3 * 2 + 1));
  char *p1 = address, *p2 = rtn;
  while (*p1 != '\0') {
    if (*p1 == '.') {
      *p2++ = '[';
      *p2++ = '.';
      *p2++ = ']';
    } else {
      *p2++ = *p1;
    }
    p1++;
  }
  *p2 = '\0';
  return rtn;
}

void test(const char *expect, char *address) {
  EXPECT_EQ_STRING_AND_FREE_ACTUAL(expect, defangIPaddr(address));
}

int main(void) {
  test("1[.]1[.]1[.]1", "1.1.1.1");
  test("255[.]100[.]50[.]0", "255.100.50.0");

  return testOutput();
}
